//
// Created by Minh Pham on 2019-05-06.
//

#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <string>
#include <algorithm>

#include "ExpandLeftStore.h"

using namespace std;

/**
 * Implementation of java.utils.arrays.hashCode
 * @param v
 * @return the hash code
 */
int hashCode(vector<int> v){
    int result = 1;

    for(int element : v){
        result = 31*result + element;
    }

    return result;
}

void ExpandLeftStore::registerELS(LeftRule leftRule, vector<int> itemsetJ, vector<int> tidsJ,
                                  map<int, Occurence> occurencesI, map<int, Occurence> occurencesJ) {

    int size = itemsetJ.size();
    int hash = hashCode(itemsetJ);

    map<int, vector<LeftEquivalenceClass*>*> *MAP = new std::map<int, vector<LeftEquivalenceClass*>*>();
    std::map<int, std::map<int, vector<LeftEquivalenceClass*>*>*>::iterator itr1 = store.find(size);

    if(itr1 == this->store.end()){
        this->store.insert(pair<int, std::map<int, vector<LeftEquivalenceClass*>*>*>(size, MAP));
    }

    vector<LeftEquivalenceClass*> *list = new vector<LeftEquivalenceClass*>();
    std::map<int, vector<LeftEquivalenceClass*>*>::iterator itr2 = store.find(size)->second->find(hash);

    if(itr2 == store.find(size)->second->end()){
        LeftEquivalenceClass *eclass = new LeftEquivalenceClass(itemsetJ,tidsJ, occurencesJ);
        eclass->rules.push_back(leftRule);
        list->push_back(eclass);
        store.find(size)->second->insert(make_pair(hash, list));
//        cout << store.find(size)->second->find(hash)->second->size() << endl;
    }
    else{
        for(LeftEquivalenceClass *eclass : *(store.find(size)->second->find(hash)->second)){

            if(equal(eclass->itemsetJ.begin(), eclass->itemsetJ.end(), itemsetJ.begin())){
                eclass->rules.push_back(leftRule);
//                cout << "passed" << endl;
                return;
            }
        }

//        //if not found
        LeftEquivalenceClass *eclass = new LeftEquivalenceClass(itemsetJ, tidsJ, occurencesJ);
        eclass->rules.push_back(leftRule);
        store.find(size)->second->find(hash)->second->push_back(eclass);
    }
}

map<int, map<int, vector<LeftEquivalenceClass*>*>*> ExpandLeftStore::getStore() {
    return this->store;
}