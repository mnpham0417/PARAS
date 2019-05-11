//
// Created by Minh Pham on 2019-05-04.
//

#ifndef ERMINER_SEQUENCEDATABASE_H
#define ERMINER_SEQUENCEDATABASE_H

#include <vector>
#include <set>
#include <iostream>
#include "Sequence.h"

using namespace std;

class SequenceDatabase {
private:
    vector<Sequence> data;
public:
    SequenceDatabase(){};
    void loadFile(string filename);
    void addSequence(Sequence sequence);
    void toString();
    vector<Sequence> getSequences();
    int size();
};


#endif //ERMINER_SEQUENCEDATABASE_H
