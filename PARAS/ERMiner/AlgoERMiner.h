//
// Created by Minh Pham on 2019-05-04.
//

#ifndef ERMINER_VER2_ALGOERMINER_H
#define ERMINER_VER2_ALGOERMINER_H

#include <map>
#include <iostream>
#include <fstream>

#include "SequenceDatabase.h"
#include "Occurence.h"
#include "SparseMatrix.h"
#include "ExpandLeftStore.h"

using namespace std;

class AlgoERMiner {
private:
    /*** parameters ***/
    /** minimum confidence */
    double minConfidence;

    /** minimum support */
    int minsuppRelative;

    /**  number of rules generated */
    int ruleCount;

    /** total number of candidtaes */
    int totalCandidateCount;

    /** number of pruned candidates */
    int candidatePrunedCount;

    /** the expandleft store */
    ExpandLeftStore store;

    ofstream writer;

    SequenceDatabase database;
    map<int, map<int, Occurence>> mapItemCount;
    SparseMatrix matrix;
public:
    AlgoERMiner(int minConfidence, int minsuppRelative, SequenceDatabase sdb);
    map<int, map<int, Occurence>> calculateFrequencyOfEachItem(SequenceDatabase database);
    void generateMatrix(SequenceDatabase database);
    void runAlgorithm(int relativeMinsup, double minConfidence);
    map<int, map<int, Occurence>> getmapItemCount();
    SparseMatrix getMatrix();
    void saveRule(vector<int> tidsIJ, double confIJ, vector<int> itemsetI, vector<int> itemsetJ);
    void expandLeft(LeftEquivalenceClass eclass);
    void expandRight(RightEquivalenceClass eclass, bool firstTime);
};


#endif //ERMINER_VER2_ALGOERMINER_H
