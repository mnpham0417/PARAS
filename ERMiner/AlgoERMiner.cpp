//
// Created by Minh Pham on 2019-05-04.
//


#include "Sequence.h"
#include "SequenceDatabase.h"
#include "Occurence.h"
#include "LeftRule.h"
#include "RightRule.h"
#include "RightEquivalenceClass.h"
#include "LeftEquivalenceClass.h"
#include "AlgoERMiner.h"

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <string>
#include <algorithm>
#include <math.h>

using namespace std;

AlgoERMiner::AlgoERMiner(int minConfidence, int minsuppRelative, SequenceDatabase sdb) {
    this->minConfidence = minConfidence;
    this->minsuppRelative = minsuppRelative;
    this->database = sdb;
}

/*
* Save a rule I ==> J to the output file
* @param tidsIJ the tids containing the rule
* @param confIJ the confidence
* @param itemsetI the left part of the rule
* @param itemsetJ the right part of the rule
* @throws IOException exception if error writing the file
*/
void AlgoERMiner::saveRule(vector<int> tidsIJ, double confIJ, vector<int> itemsetI, vector<int> itemsetJ){
    //increase the number of rule found
    this->ruleCount++;

    string result = "";

    //write itemset 1 (antecedent)
    for(int i = 0; i < itemsetI.size(); i++){
        result.append(to_string(itemsetI[i]));
        if(i != itemsetI.size()-1){
            result.append(",");
        }
    }

    //write separator
    result.append(" ==> ");

    //write itemset 2 (consequent)
    for(int i = 0; i < itemsetJ.size(); i++){
        result.append(to_string(itemsetJ[i]));
        if(i != itemsetJ.size()-1){
            result.append(",");
        }
    }

    //write support
    result.append(" #SUP ");
    result.append(to_string(tidsIJ.size()));

    //write confidence
    result.append(" #CONF: ");
    result.append(to_string(confIJ));
    this->writer << result << endl;
}

map<int, map<int, Occurence>> AlgoERMiner::calculateFrequencyOfEachItem(SequenceDatabase database) {

    //for each sequence in the database
    for (int k = 0; k < database.size(); k++){
        Sequence sequence = database.getSequences()[k];

        //for each itemset in that sequence
        for(int j = 0; j < sequence.getItemsets().size(); j++){
            vector<int> itemset = sequence.get(j);

            //for each item in that itemset
            for(int itemI : itemset){
                map<int, map<int, Occurence>>::iterator itr1 = this->mapItemCount.find(itemI);

                if(itr1 == this->mapItemCount.end()){ // if this map is null, create a new one

                    map<int, Occurence> occurences;
                    Occurence occurence = Occurence(j,j);
                    occurences.insert(pair<int, Occurence> (k, occurence));
                    this->mapItemCount.insert(pair<int, map<int, Occurence>> (itemI, occurences));
                }else{
                    // then update the occurence by adding j as the
                    // last occurence in sequence k
                    map<int, Occurence>::iterator itr2 = itr1->second.find(k);
                    if(itr2 == itr1->second.end()){ //not found
                        itr1->second.insert(pair<int, Occurence>(k, Occurence(j,j)));
                    }else{ //found
                        itr2->second.lastItemset = j;
                    }
                }
            }
        }
    }
    return this->mapItemCount;
}

void AlgoERMiner::generateMatrix(SequenceDatabase database) {

    //for each sequence
    for(Sequence sequence : this->database.getSequences()){

        map<int, int> alreadyProcessed;

        //for each itemset
        for(vector<int> itemsetj : sequence.getItemsets()){

            //for each item
            for(int itemk : itemsetj){
                //true = contain and false otherwise
                bool isContain = (alreadyProcessed.find(itemk) != alreadyProcessed.end());
                if(isContain || mapItemCount.find(itemk)->second.size() < this->minsuppRelative){
                    continue;
                }
                //for item k we should update the matrix with each item co-occurring
                map<int, int> alreadyProcessedWithRespectToK;
                for(vector<int> itemsetjj : sequence.getItemsets()){

                    for(int itemkk : itemsetjj){

                        //true = contain and false otherwise
                        bool isContain2 = (alreadyProcessedWithRespectToK.find(itemkk) !=
                                alreadyProcessedWithRespectToK.end());

                        if(itemkk == itemk || isContain2
                            || mapItemCount.find(itemkk)->second.size() < this->minsuppRelative){
                            continue;
                        }

                        this->matrix.increaseCountOfPair(itemk, itemkk);
//                        cout << matrix.getMatrix().size() << endl;

                        alreadyProcessedWithRespectToK.insert(pair<int, int> (itemkk,1));
//                        cout << alreadyProcessedWithRespectToK.size();
                    }
                }
//                //end second loop
                alreadyProcessed.insert(make_pair(itemk, 1));
            }
        }
    }
}

/*
 * Retrieve all keys from the map
 * @param map A map with key = int, value = Occurence
 * @return vector list of keys
 */
vector<int> retrieveKey(map<int, Occurence> m){
    vector<int> result;
    for(map<int,Occurence>::iterator it = m.begin(); it != m.end(); ++it) {
        result.push_back(it->first);
    }
    return result;
}

void calculateIidsetsIJandJI(map<int, Occurence> occurencesI, map<int, Occurence> occurencesJ,
                             vector<int>& tidsIJ, vector<int>& tidsJI){
    for(auto const& entry : occurencesI){

        int tid = entry.first;
//        cout << "tid " << tid << endl;
        map<int, Occurence>::iterator itr = occurencesJ.find(tid);
//
//        //if J appears in that sequence
        if(itr != occurencesJ.end()){

            //get the occurence of J in the same sequence
            Occurence occJ = itr->second;
            Occurence occI = entry.second;

            // if J appeared before I in that sequence,
            // then we put this tid in the tidset of  J-->I
            if(occJ.firstItemset < occI.lastItemset){
                tidsJI.push_back(tid);
            }
//            // if I appeared before J in that sequence,
//            // then we put this tid in the tidset of  I-->J
            if(occI.firstItemset < occJ.lastItemset){
                tidsIJ.push_back(tid);
            }
        }
    }
}

void registerRule11(int intI, int intJ, vector<int> tidsI, vector<int> tidsJ,
                    vector<int> tidsIJ, map<int, Occurence> occurencesI,
                    map<int, Occurence> occurencesJ,
                    map<int, LeftEquivalenceClass>& mapEclassLeft,
                    map<int, RightEquivalenceClass>& mapEclassRight){

    //add  the rule to the left equivalence class
    map<int, LeftEquivalenceClass>::iterator itr1 = mapEclassLeft.find(intJ);
    if(itr1 == mapEclassLeft.end()){
//        cout << "in function " << intJ << endl;
        LeftEquivalenceClass leftClass = LeftEquivalenceClass({intJ}, tidsJ, occurencesJ);
        mapEclassLeft.insert(make_pair(intJ, leftClass));
    }
    LeftRule ruleL = LeftRule({intI}, tidsI, tidsIJ);
    mapEclassLeft.find(intJ)->second.rules.push_back(ruleL);

    //add the rule to the right equivalece class
    map<int, RightEquivalenceClass>::iterator itr2 = mapEclassRight.find(intI);
    if(itr2 == mapEclassRight.end()){
        RightEquivalenceClass rightClass = RightEquivalenceClass({intI},tidsI, occurencesI);
        mapEclassRight.insert(make_pair(intI, rightClass));
    }
    RightRule ruleR = RightRule({intJ}, tidsJ, tidsIJ, occurencesJ);
    mapEclassRight.find(intI)->second.rules.push_back(ruleR);
}

bool compareRuleLeft(LeftRule arg0, LeftRule arg1){
    return arg0.itemsetI[0] >= arg1.itemsetI[0];
}

bool compareRuleRight(RightRule arg0, RightRule arg1){
    return arg0.itemsetJ[0] >= arg1.itemsetJ[0];
}


void AlgoERMiner::expandLeft(LeftEquivalenceClass eclass){
//    cout << "size " << eclass.rules.size() << endl;
    for(int w = 0; w < eclass.rules.size()-1; w++){ // IMPORTANT : SIZE -1 BECAUSE THE LAST ONE HAS NOTHING LEFT FOR COMPARISON

        LeftRule rule1 = eclass.rules[w];
        int d = rule1.itemsetI[rule1.itemsetI.size()-1];

        LeftEquivalenceClass *rulesForRecursion = new LeftEquivalenceClass(eclass.itemsetJ, eclass.tidsJ,
                eclass.occurencesJ);

        //for each rule J != I
        for(int m=w+1; m < eclass.rules.size(); m++){
            LeftRule rule2 = eclass.rules[m];

            int c = rule2.itemsetI[rule2.itemsetI.size()-1];


            if(this->matrix.getCount(c,d) < minsuppRelative){
                this->candidatePrunedCount++;
                this->totalCandidateCount++;
                cout << "pass" << endl;
                continue;
            }
            totalCandidateCount++;

            //Calculate tids I U {C}

            vector<int> tidsIC;
            map<int, Occurence> mapC = mapItemCount.find(c)->second;

            //depending of the relative size of tids of I and tids of {c} we have two ways to calculate it

            if(rule1.tidsI.size() < mapC.size()){
                //early skip optimization
                int remains = rule1.tidsI.size();

                //for each sequence containing I
                for(int tid: rule1.tidsI){
                    // Get the first and last occurences of C in that sequence
                    // if there is an occurence
                    map<int, Occurence>::iterator itr = mapC.find(tid);
                    if(itr != mapC.end()){
                        //add the tid of the sequence to the tidset of JU{c}
                        tidsIC.push_back(tid);
                    }
                    remains--;
                    //early skip
                    if(tidsIC.size() + remains < minsuppRelative){
                        break;
                    }
                }
            }else{
                int remains = mapC.size();
                //for each sequence containing I
                for(int tid: retrieveKey(mapC)){

                    //get the first and last occurences of C in that sequence
                    //if there is an occurence
                    if(find(rule1.tidsI.begin(), rule1.tidsI.end(), tid) != rule1.tidsI.end()){
                        //add the tid of the sequence to the tidset of JU{c}
                        tidsIC.push_back(tid);
                    }
                    remains--;
                    if(tidsIC.size() + remains < minsuppRelative){
                        break;
                    }
                }
            }

            //calculate tids IC ==> J
            vector<int> tidsIC_J;

            //depending of the relative size of tids of IUJ and tids of {c} we have two ways to calculate it
            if(rule1.tidsIJ.size() < mapC.size()){
                //for each sequence containing I
                for(int tid: rule1.tidsIJ){
                    //get the first and last occurences of C in that sequence
                    map<int, Occurence>::iterator itr = mapC.find(tid);
                    //if there is an occurence
                    if(itr != mapC.end()){
                        Occurence occurenceC = mapC.find(tid)->second;

                        Occurence occurenceJ = eclass.occurencesJ.find(tid)->second;

                        if(occurenceC.firstItemset < occurenceJ.lastItemset){
                            //add the tid of the sequences to the tidset of JU{c}
                            tidsIC_J.push_back(tid);
                        }
                    }
                }
            }else{
                // for each sequence containing I
                for (auto const& entryC : mapC){
                    int tid = entryC.first;
                    if(find(rule1.tidsIJ.begin(), rule1.tidsIJ.end(), tid) != rule1.tidsIJ.end()){
                        //get the first and last occurences of C in that sequence
                        Occurence occurenceC = entryC.second;
//                        cout << "occurenceC" << endl;
//                        cout << "first " << occurenceC.firstItemset << endl;
//                        cout << "last" << occurenceC.lastItemset << endl;
                        //if there is an occurence
                        Occurence occurenceJ = eclass.occurencesJ.find(tid)->second;
//                        cout << "occurenceJ" << endl;
//                        cout << "first " << occurenceJ.firstItemset << endl;
//                        cout << "last " << occurenceJ.lastItemset << endl << endl;
                        if(occurenceC.firstItemset < occurenceJ.lastItemset){
                            //add the tid of the sequence to the tidset of JU{c}
                            tidsIC_J.push_back(tid);

                        }
                    }
                }
            }

            if(tidsIC_J.size() >= minsuppRelative){
                //create rule and calculate its confidence of IU{c} ==> J
                //defined as: sup(IU{c} -->J) / sup(IU{c})
                double confIC_J = ((double) tidsIC_J.size()) / tidsIC.size();

                //try to combine the rules
                vector<int> itemsetIC = rule1.itemsetI;
                itemsetIC.push_back(c);

                LeftRule newRule = LeftRule(itemsetIC, tidsIC, tidsIC_J);

                //if the confidence is high enough, then it is a valid rule
                if(confIC_J >= minConfidence){
                    //save the rule
                    saveRule(tidsIC_J, confIC_J, itemsetIC, eclass.itemsetJ);
                }

                if(true){
                    rulesForRecursion->rules.push_back(newRule);
//                    cout << rulesForRecursion->rules.size() << endl;
                }
            }
        }

        if(rulesForRecursion->rules.size() > 1){
            expandLeft(*rulesForRecursion);
        }
    }
}

void AlgoERMiner::expandRight(RightEquivalenceClass eclass, bool firstTime){
    for(int w = 0; w < eclass.rules.size()-1; w++){ // IMPORTANT : SIZE -1 BECAUSE THE LAST ONE HAS NOTHING LEFT FOR COMPARISON
//        cout << w << endl;
        RightRule rule1 = eclass.rules[w];
        int d = rule1.itemsetJ[rule1.itemsetJ.size()-1];
        RightEquivalenceClass *rulesForRecursion = new RightEquivalenceClass(eclass.itemsetI, eclass.tidsI,
                                                                           eclass.occurencesI);
//        cout << eclass.rules.size() << endl;
        //for each rule J != I


        for(int m = w+1; m < eclass.rules.size(); m++){

            RightRule rule2 = eclass.rules[m];

            int c = rule2.itemsetJ[rule2.itemsetJ.size()-1];

            if(this->matrix.getCount(c,d) < minsuppRelative){
                this->candidatePrunedCount++;
                this->totalCandidateCount++;
                continue;
            }
            totalCandidateCount++;

            //Calculate tids of I ==> JC
            vector<int> tidsI_JC;

            //for each sequence containing I
            map<int, Occurence> mapC = mapItemCount.find(c)->second;

            // depending of the relative size of tids of IUJ and tids of {c} we have two ways to calculate it
            if(rule1.tidsIJ.size() < mapC.size()){

                //early skip optimization
                int remains = rule1.tidsIJ.size();

                for(int tid: rule1.tidsIJ){

                    //get the first and last occurences of C in that sequence
                    map<int, Occurence>::iterator itr = mapC.find(tid);

                    //if there is an occurence
                    if(itr != mapC.end()) {
                        Occurence occurenceC = mapC.find(tid)->second;
                        Occurence occurenceI = eclass.occurencesI.find(tid)->second;

                        if (occurenceC.lastItemset > occurenceI.firstItemset) {
                            // add the tid of the sequence to the tidset of JU{c}
                            tidsI_JC.push_back(tid);

                            }
                        }
                        remains--;

                        if(tidsI_JC.size() + remains < minsuppRelative){
                            break;
                        }
                    }
                }
                else{
//
                    //early skip optimization
                    int remains = mapC.size();

                    for(auto const& entryC : mapC){
                        int tid = entryC.first;
                        //if there is an occurence
                        if(find(rule1.tidsIJ.begin(), rule1.tidsIJ.end(), tid) != rule1.tidsIJ.end()) {
                            Occurence occurenceC = entryC.second;
                            Occurence occurenceI = eclass.occurencesI.find(tid)->second;

                        if(occurenceC.lastItemset > occurenceI.firstItemset){
                            //add the tid of the sequence to the tidset of JU{c}
                            tidsI_JC.push_back(tid);
                            }
                        }
                    }
                    remains--;
                    if(tidsI_JC.size() + remains < minsuppRelative){
                        break;
                    }
                }

                //if the support if I ==> JU{c} is enough
                if(tidsI_JC.size() >= minsuppRelative){

                    //Calculate the occurences of JU{c}
                    vector<int> tidsJC;
                    map<int, Occurence> occurencesJC;

                    //for each sequence containing J
                    if(rule1.tidsJ.size() < mapC.size()){

                        for(int tid: rule1.tidsJ){
                            //Get the first and last occurences of C in that sequence
                            map<int, Occurence>::iterator itr = mapC.find(tid);

                            //if there is an occurence
                            if(itr != mapC.end()){
                                //add the tid of the sequence to the tidset if JU{c}
                                tidsJC.push_back(tid);
                                //calculate the last occurence of JU{c} depending on if
                                //the alst occurence of J is before the last occurence
                                //of c or not.
                                Occurence occurenceC = mapC.find(tid)->second;
                                Occurence occurenceJ = rule1.occurencesJ.find(tid)->second;

                                if(occurenceC.lastItemset < occurenceJ.lastItemset){
                                    occurencesJC.insert(pair<int,Occurence>(tid,occurenceC));
                                }else{
                                    occurencesJC.insert(pair<int,Occurence>(tid,occurenceJ));
                                }
                            }
                        }
                    }
                    else{
                        for(auto entryC : mapC){
                            int tid = entryC.first;

                            //if there is an occurence
                            if(find(rule1.tidsJ.begin(), rule1.tidsJ.end(), tid) != rule1.tidsJ.end()){
                                //add the sequence to the tidet of JU{c}
                                tidsJC.push_back(tid);
                                //calculate the last occurence of JU{c} depending in if
                                //the last occurence of J is before the last occurence
                                //of c or not
                                Occurence occurenceC = entryC.second;
                                Occurence occurenceJ = rule1.occurencesJ.find(tid)->second;
//                                cout << "occurenceC" << endl;
//                                cout << "first " << occurenceC.firstItemset << endl;
//                                cout << "last" << occurenceC.lastItemset << endl;
//                                cout << "occurenceJ" << endl;
//                                cout << "first " << occurenceJ.firstItemset << endl;
//                                cout << "last " << occurenceJ.lastItemset << endl << endl;

                                if(occurenceC.lastItemset < occurenceJ.lastItemset){
                                    occurencesJC.insert(pair<int, Occurence> (tid, occurenceC));
                                }else{
                                    occurencesJC.insert(pair<int, Occurence> (tid, occurenceJ));
                                }
                            }
                        }
                    }

                    //Create rule I ==> J U{c} and calculate its confidence
                    //defined as: sup(I -->J U{c}) /sup(I)
                    double confI_JC = ((double)tidsI_JC.size()) / eclass.tidsI.size();

                    vector<int> itemsetJC = rule1.itemsetJ;
                    itemsetJC.push_back(c);
//
                    //if the confidence is enough
                    if(confI_JC >= minConfidence){
                        //then it is a valid rule so save it
                        saveRule(tidsI_JC, confI_JC, eclass.itemsetI, itemsetJC);
                    }
                    //recursively try to expand the left and right side
                    //of the rule
                    RightRule rightRule = RightRule(itemsetJC, tidsJC, tidsI_JC, occurencesJC);
//
                    if(true){
                        rulesForRecursion->rules.push_back(rightRule);
                    }
//
                    if(true){
                        LeftRule leftRule = LeftRule(eclass.itemsetI, eclass.tidsI, tidsI_JC);
                        this->store.registerELS(leftRule, itemsetJC, tidsJC,
                                eclass.occurencesI, occurencesJC); //register for left expansion
                    }
                }
        }

        if(rulesForRecursion->rules.size() > 1){
            expandRight(*rulesForRecursion, false);
        }
    }
}

void AlgoERMiner::runAlgorithm(int minSupport, double minConfidence) {
    this->minConfidence = minConfidence;
    this->minsuppRelative = (int) ceil(minSupport*database.size());
    this->ruleCount = 0;

    this->writer.open ("output.txt");

    calculateFrequencyOfEachItem(database);

    // =================== CALCULATE MATRIX ==============
    // for each sequence
    generateMatrix(database);

    if(this->minsuppRelative == 0){ // protection
        this->minsuppRelative = 1;
    }

    // We will now generate the equivalence classes of rules of size 1*1
    // We create two maps to store the equivalence classes.
    // The map for left-equivalence classes has a key : item on the right side, value: list of rules
    map<int, LeftEquivalenceClass> mapEclassLeft;

    // The map for right-equivalence classes has a key : item on the left side, value: list of rules
    map<int, RightEquivalenceClass> mapEclassRight;

    // for each entry in the matrix
    // entry  =  key: item I    value: a map where key: item J and value: the support of {i, j}
    for( auto entry1 : this->matrix.getMatrix() )
    {
        int intI = entry1.first;
        map<int, Occurence> occurencesI = this->mapItemCount.find(intI)->second;

        // get the tidset of itemI
        vector<int> tidsI = retrieveKey(occurencesI);
        // for each item J that co-occurs with I
        for(auto entry2 : entry1.second){

            // if I and J are infrequent, we don't continue
            if(entry2.second < this->minsuppRelative){
                continue;
            }

            int intJ = entry2.first;

            map<int, Occurence> occurencesJ = this->mapItemCount.find(intJ)->second;

            // (1) We will now calculate the tids of I -->J  and J-->I.

            // initialize the tids sets
            vector<int> tidsIJ; // tidset of  I -->J
            vector<int> tidsJI; // tidset of J-->I


            // for each occurence of I
            if(occurencesI.size() < occurencesJ.size()){
                calculateIidsetsIJandJI(occurencesI, occurencesJ, tidsIJ, tidsJI);
            }else{
                calculateIidsetsIJandJI(occurencesJ, occurencesI, tidsJI, tidsIJ);
            }

            // (2) check if the two itemsets have enough common tids
            // if not, we don't need to generate a rule for them.

            //create rule IJ
            if(tidsIJ.size() >= minsuppRelative){
                //calculate the confidence of I ==> J
                double confIJ = ((double)tidsIJ.size()) / occurencesI.size();
                //create ite,set of the rule I ==> J
                vector<int> itemsetI;
                vector<int> itemsetJ;
                itemsetI.push_back(intI);
                itemsetJ.push_back(intJ);

                vector<int> tidsJ = retrieveKey(occurencesJ);
                //if the confidence is high enough, save the rule
                if(confIJ >= minConfidence){
                    saveRule(tidsIJ, confIJ, itemsetI, itemsetJ);
                }
                if(true){
//                    cout << intJ << endl;
                    //register the rule in the appropriate equivalence classes
                    registerRule11(intI, intJ, tidsI, tidsJ, tidsIJ, occurencesI, occurencesJ,
                                   mapEclassLeft, mapEclassRight);
                }
            }


            //check if J ==> I has enough common tids
            //if yes, we create the rule J ==> I
            if(tidsJI.size() >= this->minsuppRelative){

                //create itemset of the rule J ==> I
                vector<int> itemsetI = {intI};
                vector<int> itemsetJ = {intJ};

                //calculate the confidence
                double confJI = ((double)tidsJI.size()) / occurencesJ.size();

                vector<int> tidsJ = retrieveKey(occurencesJ);

                //if the confidence is high enough, save the rule
                if(confJI >= this->minConfidence){
                    saveRule(tidsJI, confJI, itemsetJ, itemsetI);
                }

                //register the rule in the appropriate equivalence classes
                if(true){
                    registerRule11(intJ, intI, tidsJ, tidsI, tidsJI, occurencesJ, occurencesI,
                                   mapEclassLeft, mapEclassRight);
                }

            }
        }
    }

    //PERFORM EXPAND LEFT FOR EACH LEFT-EQUIVALECE CLASS OF SIZE 1-1
    if(true){
        for (auto entry : mapEclassLeft){

            if(entry.second.rules.size() != 1){
//                sort( entry.second.rules.begin(), entry.second.rules.end(), compareRuleLeft);

                this->expandLeft(entry.second);
            }
        }
    }

    // PERFORM EXPAND RIGHT FOR EACH RIGHT-EQUIVALENCE CLASS OF SIZE 1-1
        for(auto entry1 : mapEclassRight){
            if(entry1.second.rules.size() != 1){
                expandRight(entry1.second, true);
            }
        }

    // PROCESS ALL EQUIVALENCE CLASSES WITH MORE THAN ONE ITEM IN LEF PART FOR EXPAND LEFT AFTER RIGHT...
    for(auto entry2 : store.getStore()){
        for(auto entry3 : *entry2.second){
            for(LeftEquivalenceClass *eclass : *entry3.second){
                if(eclass->rules.size() != 1){
                    expandLeft(*eclass);
                }
            }
        }
    }

}

map<int, map<int, Occurence>> AlgoERMiner::getmapItemCount() {
    return this->mapItemCount;

}

SparseMatrix AlgoERMiner::getMatrix() {
    return this->matrix;
}
