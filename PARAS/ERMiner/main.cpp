#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <iterator>
#include <vector>
#include<utility>
#include <map>
#include <time.h>
#include <chrono>
#include <typeinfo>

#include "Sequence.h"
#include "SequenceDatabase.h"
#include "Occurence.h"
#include "LeftRule.h"
#include "RightRule.h"
#include "RightEquivalenceClass.h"
#include "LeftEquivalenceClass.h"
#include "AlgoERMiner.h"

using namespace std;

bool myfunction (int i,int j) { return (i<j); }

void testWrite(ofstream& myfile, string str){
    myfile << str << endl;
}

void add(int num, vector<int> *vec){
    vec->push_back(num);
}

int main() {
    SequenceDatabase sdb = SequenceDatabase();
    sdb.loadFile("data.txt");
    sdb.toString();

    AlgoERMiner algoERMiner = AlgoERMiner(0.01, 0.01, sdb);
    algoERMiner.runAlgorithm(0,0.5);

//    vector<int> *testing_vec = new vector<int>();
//    add(10, testing_vec);
//    add(15, testing_vec);
//    for(int i : *testing_vec){
//        cout << i << endl;
//    }


//    map<int, map<int, Occurence>> mapItemCount = algoERMiner.calculateFrequencyOfEachItem(sdb);
//    cout << mapItemCount.size() << endl;
//
//    vector<int> myvector = {32,71,12,45,26,80,53,33};
//    sort (myvector.begin(), myvector.end(), myfunction);
//
//    for (int i : myvector){
//        cout << i << endl;
//    }
//
//    algoERMiner.generateMatrix(sdb);
//
//    vector<int> vector1 = {1,2,3};
//    vector<int> vector2 = {1,3,2};
//    vector<int> vector3 = vector2;
//    vector3[1] = 100;
//
//    sort (vector2.begin(), vector2.end(), myfunction);
//
//    for(int i : vector2){
//        cout << i << ", ";
//    }
//
//    if( equal(vector1.begin(), vector1.end(), vector2.begin()) ){
//        cout << "matched";
//    }
//
//    string str1 = "Hello ";
//    string str2 = "World!";
//    ofstream myfile;
//    myfile.open ("example2.txt");
//    testWrite(myfile, str1.append(str2));
//    testWrite(myfile, "Heool");
//    myfile.close();
//
//    for (int i : {1,2,3}){
//        cout << i;
//        cout << ", ";
//    }
//
//    cout << "testing map" << endl;
//    map<int, map<int,int>*> testing_map;
//    map<int, int> *pointer_map = new map<int, int>();
//    pointer_map->insert(pair<int,int>(4,5));
//
//    testing_map.insert(pair<int, map<int, int>*>(1,pointer_map));
//
//
//    map<int, map<int, int>*>::iterator itr = testing_map.find(1);
//    if(itr != testing_map.end()){
//        cout << "Found";
//        map<int,int>::iterator itr2 = itr->second->find(4);
//        cout << "First is: " << itr->first << endl;
//        if(itr2 != itr->second->end()){
//            cout << "Found again";
//        }
//    }
//
//    cout << "========== Testing 2 ========" << endl;
//
//    map<int, map<int, vector<int>*>*> store;
//    map<int, vector<int>*> *pointer_map2 = new map<int, vector<int>*>();
//    vector<int> *pointer_vector2 = new vector<int>();
//
//    pointer_vector2->push_back(1);
//    pointer_vector2->push_back(3);
//
//    pointer_map2->insert(pair<int, vector<int>*>(10, pointer_vector2));
//    store.insert(pair<int, map<int, vector<int>*>*>(20, pointer_map2));
//
//    map<int, map<int, vector<int>*>*>::iterator itr1 = store.find(20);
//
//    if(itr1 != store.end()){
//        cout << "Found" << endl;
//        map<int,vector<int>*>::iterator itr2 = itr1->second->find(10);
//        if(itr2 != itr1->second->end()){
//            cout << "Found 2" << endl;
//            for(int i : (*itr2->second)){
//                cout << i;
//            }
//        }
//    }
//
//    cout << "========== Testing 2 ========" << endl;


    return 0;


}