//
// Created by Minh Pham on 2019-05-04.
//
#include <iostream>
#include <vector>
#include <map>

#include "Occurence.h"
#include "LeftRule.h"

#ifndef ERMINER_VER2_LEFTEQUIVALENCECLASS_H
#define ERMINER_VER2_LEFTEQUIVALENCECLASS_H

using namespace std;

class LeftEquivalenceClass {
public:
    vector<int> itemsetJ;
    vector<int> tidsJ;
    map<int, Occurence> occurencesJ;

    vector<LeftRule> rules;

    LeftEquivalenceClass(){};
    LeftEquivalenceClass(vector<int> itemsetJ, vector<int> tidsJ, map<int, Occurence> occurencesJ);
    void toString();
    bool equals(LeftEquivalenceClass obj);
};


#endif //ERMINER_VER2_LEFTEQUIVALENCECLASS_H
