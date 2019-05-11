//
// Created by Minh Pham on 2019-05-04.
//

#include "LeftRule.h"

LeftRule::LeftRule(vector<int> itemsetI, vector<int> tidsI, vector<int> tidsIJ) {
    this->itemsetI = itemsetI;
    this->tidsI = tidsI;
    this->tidsIJ = tidsIJ;
}

void LeftRule::toString() {
    for(int i : this->itemsetI){
        cout << i << ", ";
    }
    cout << " ==> ...";
}