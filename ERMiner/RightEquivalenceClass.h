//
// Created by Minh Pham on 2019-05-04.
//
#include <iostream>
#include <vector>
#include <set>
#include <map>

#include "Occurence.h"
#include "RightRule.h"

#ifndef ERMINER_VER2_RIGHTEQUIVALENCECLASS_H
#define ERMINER_VER2_RIGHTEQUIVALENCECLASS_H

using namespace std;

class RightEquivalenceClass {

public:
    vector<int> itemsetI;
    vector<int> tidsI;
    map<int, Occurence> occurencesI;

    vector<RightRule> rules;

    RightEquivalenceClass(vector<int> itemsetI, vector<int> tidsI, map<int, Occurence> occurencesI);
    void toString();
    bool equals(RightEquivalenceClass obj);
};


#endif //ERMINER_VER2_RIGHTEQUIVALENCECLASS_H
