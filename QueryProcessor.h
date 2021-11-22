//
// Created by Zachary on 11/22/2021.
//

#ifndef INC_21F_SRCH_NGN_QUERYPROCESSOR_H
#define INC_21F_SRCH_NGN_QUERYPROCESSOR_H

#include <iostream>
#include <set>
#include <unordered_map>

#include "AVLTree.h"
#include "Document.h"

using namespace std;

class QueryProcessor {
public:
    QueryProcessor();

    void search(string, AVLTree<string, vector<string>>&, unordered_map<string, Document>&);
    void stemWord(string&);
};

#endif //INC_21F_SRCH_NGN_QUERYPROCESSOR_H
