//
// Created by Minh Pham on 2019-05-06.
//

#ifndef ERMINER_VER2_EXPANDLEFTSTORE_H
#define ERMINER_VER2_EXPANDLEFTSTORE_H

#include <map>
#include <vector>
#include <typeinfo>

#include "LeftEquivalenceClass.h"
#include "LeftRule.h"
#include "Occurence.h"



class ExpandLeftStore {
public:
    map<int, map<int, vector<LeftEquivalenceClass*>*>*> store;

    ExpandLeftStore(){};
    void registerELS(LeftRule leftRule, vector<int> itemsetJ,
            vector<int> tidsJ, map<int, Occurence> occurenceI,
            map<int, Occurence> occurenceJ);
    map<int, map<int, vector<LeftEquivalenceClass*>*>*> getStore();
};


#endif //ERMINER_VER2_EXPANDLEFTSTORE_H
