//
// Created by Minh Pham on 2019-05-04.
//

#ifndef ERMINER_SEQUENCE_H
#define ERMINER_SEQUENCE_H

#include <vector>

using namespace std;

class Sequence {
private:
    int id;
    vector<vector<int>> itemsets;
public:
    Sequence(int id);
    void addItemset(vector<int> itemset);
    void toString();
    int getId();
    vector<vector<int>> getItemsets();
    vector<int> get(int index);
    int size();
};


#endif //ERMINER_SEQUENCE_H
