//
// Created by Minh Pham on 2019-05-04.
//

#include "SparseMatrix.h"
#include <map>
#include <iterator>
#include <iostream>

using namespace std;

void SparseMatrix::increaseCountOfPair(int i, int j) {
    //IMPORTANT
    if(i < j){
        return;
    }

    map<int, map<int,int>>::iterator itr1 = matrix.find(i);
    if(itr1 == this->matrix.end()){ //not found
        map<int, int> m;

        m.insert(pair<int, int>(j,1));

        matrix.insert(make_pair(i, m));
        cout << endl;

    }else{ //found

        map<int, int>::iterator itr2 = itr1->second.find(j);
        if(itr2 == itr1->second.end()){ //not found
            itr1->second.insert(pair<int, int>(j,1));
        }else{ //found
            itr2->second++;
        }
    }
}

int SparseMatrix::getCount(int i, int j){
    map<int, map<int,int>>::iterator itr1 = this->matrix.find(i);
    if(itr1 == this->matrix.end()){ //not found
        return 0;
    }else{
        map<int, int>::iterator itr2 = itr1->second.find(j);
        if(itr2 == itr1->second.end()){ //not found
            return 0;
        }
        return itr2->second;
    }
}

map<int, map<int, int>> SparseMatrix::getMatrix() {
    return this->matrix;
}