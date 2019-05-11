//
// Created by Minh Pham on 2019-05-04.
//

#include <set>
#include <iostream>
#include <vector>
#include <map>

#include "Occurence.h"

#ifndef ERMINER_VER2_RIGHTRULE_H
#define ERMINER_VER2_RIGHTRULE_H

using namespace std;

class RightRule {

public:
    vector<int> itemsetJ;
    vector<int> tidsJ;
    vector<int> tidsIJ;
    map<int, Occurence> occurencesJ;

    RightRule(vector<int> itemsetJ, vector<int> tidsJ, vector<int> tidsIJ, map<int, Occurence> occurencesJ);
    void toString();

};


#endif //ERMINER_VER2_RIGHTRULE_H
