//
// Created by Minh Pham on 2019-05-04.
//

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include "LeftEquivalenceClass.h"
#include "Occurence.h"
#include "LeftRule.h"

using namespace std;

LeftEquivalenceClass::LeftEquivalenceClass(vector<int> itemsetJ, vector<int> tidsJ, map<int, Occurence> occurencesJ) {
    this->itemsetJ = itemsetJ;
    this->tidsJ = tidsJ;
    this->occurencesJ = occurencesJ;
}

void LeftEquivalenceClass::toString() {
    cout << "EQ: ";
    for (int i : this->itemsetJ){
        cout << i << ", ";
    }
}

bool compareLeft (int i,int j) { return (i<j); }

bool LeftEquivalenceClass::equals(LeftEquivalenceClass obj) {
//    if(obj == NULL){
//        return false;
//    }

    sort(this->itemsetJ.begin(), this->itemsetJ.end(), compareLeft);
    sort(obj.itemsetJ.begin(), obj.itemsetJ.end(), compareLeft);

    if( equal(this->itemsetJ.begin(), this->itemsetJ.end(), obj.itemsetJ.begin()) ){
        return true;
    }
    return false;
}
