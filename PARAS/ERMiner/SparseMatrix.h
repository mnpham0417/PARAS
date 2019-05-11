//
// Created by Minh Pham on 2019-05-04.
//

#ifndef ERMINER_VER2_SPARSEMATRIX_H
#define ERMINER_VER2_SPARSEMATRIX_H

#include <map>

using namespace std;

class SparseMatrix {
private:
    map<int , map<int, int>> matrix;
public:
    SparseMatrix(){};
    void increaseCountOfPair(int i, int j);
    int getCount(int i, int j);
    map<int , map<int, int>> getMatrix();
};


#endif //ERMINER_VER2_SPARSEMATRIX_H
