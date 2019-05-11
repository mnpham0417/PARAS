//
// Created by Minh Pham on 2019-05-04.
//

#include <set>
#include <iostream>
#include <vector>

#ifndef ERMINER_VER2_LEFTRULE_H
#define ERMINER_VER2_LEFTRULE_H

using namespace std;

class LeftRule {

public:
    vector<int> itemsetI;
    vector<int> tidsI;
    vector<int> tidsIJ;

    LeftRule(vector<int> itemsetI, vector<int> tidsI, vector<int> tidsIJ);
    void toString();
};


#endif //ERMINER_VER2_LEFTRULE_H
