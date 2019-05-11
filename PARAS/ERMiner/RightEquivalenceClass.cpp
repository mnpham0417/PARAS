//
// Created by Minh Pham on 2019-05-04.
//

#include <map>
#include <algorithm>

#include "RightEquivalenceClass.h"
#include "Occurence.h"
#include "RightRule.h"

using namespace std;

RightEquivalenceClass::RightEquivalenceClass(vector<int> itemsetI, vector<int> tidsI,
                                             map<int, Occurence> occurencesI) {
    this->itemsetI = itemsetI;
    this->tidsI = tidsI;
    this->occurencesI = occurencesI;
}

void RightEquivalenceClass::toString() {
    cout << "EQ: ";
    for (int i : this->itemsetI){
        cout << i << ", ";
    }
}

bool compareRight (int i,int j) { return (i<j); }

bool RightEquivalenceClass::equals(RightEquivalenceClass obj) {
//    if(obj == null){
//        return false;
//    }

    sort(this->itemsetI.begin(), this->itemsetI.end(), compareRight);
    sort(obj.itemsetI.begin(), obj.itemsetI.end(), compareRight);

    if( equal(this->itemsetI.begin(), this->itemsetI.end(), obj.itemsetI.begin()) ){
        return true;
    }
    return false;
}
