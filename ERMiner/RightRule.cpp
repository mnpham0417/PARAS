//
// Created by Minh Pham on 2019-05-04.
//

#include "RightRule.h"

RightRule::RightRule(vector<int> itemsetJ, vector<int> tidsJ, vector<int> tidsIJ, map<int, Occurence> occurencesJ){
this->itemsetJ = itemsetJ;
this->tidsJ = tidsJ;
this->tidsIJ = tidsIJ;
this->occurencesJ = occurencesJ;
}

void RightRule::toString() {
    for(int i : this->itemsetJ){
        cout << i << ", ";
    }
    cout << " ==> ...";
}