//
// Created by Minh Pham on 2019-05-04.
//

#include <iostream>
#include <string>
#include "Sequence.h"
#include <vector>

using namespace std;

Sequence::Sequence(int id) {
    this->id = id;
}

/*Add itemset to this sequence
 * @param: itemset An itemset (list of integers)
 */
void Sequence::addItemset(vector<int> itemset) {
    this->itemsets.push_back(itemset);
}

/*
 * Print sequence
 */
void Sequence::toString() {
    for (vector<int> itemset : this->itemsets){
        for (int i : itemset){
            cout << i << " ";
        }
        cout << "->";
    }
}

/*
 * Get id of squence
 * @return the id of the sequence
 */
int Sequence::getId() {
    return this->id;
}

/*
 * Get itemseta
 * @return the sequence
 */
vector<vector<int>> Sequence::getItemsets() {
    return this->itemsets;
}

/*
 * Get itemset given a position
 * @param id integer
 * @return the itemset corresponding to the index
 */
vector<int> Sequence::get(int index) {
    return this->itemsets[index];
}

/*
 * Get the size of the sequence (number of itemsets)
 * @return the size (integer)
 */
int Sequence::size() {
    return this->itemsets.size();
}

