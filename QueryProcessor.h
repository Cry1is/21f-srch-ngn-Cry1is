//
// Created by Zachary on 11/22/2021.
//

#ifndef INC_21F_SRCH_NGN_QUERYPROCESSOR_H
#define INC_21F_SRCH_NGN_QUERYPROCESSOR_H

#include <iostream>
#include <set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <chrono>

#include "AVLTree.h"
#include "Document.h"

using namespace std;

class QueryProcessor {
private:
    map<double, Document> cache;
public:
    QueryProcessor();

    void UI(AVLTree<string, vector<string>>&, unordered_map<string, Document>&);
    void printUI();

    void search(AVLTree<string, vector<string>>&, unordered_map<string, Document>&);
    void readDocument();
    void stats(AVLTree<string, vector<string>>&, unordered_map<string, Document>&);
    void reindex(AVLTree<string, vector<string>>&, unordered_map<string, Document>&);

    void stemWord(string&);
};

#endif //INC_21F_SRCH_NGN_QUERYPROCESSOR_H
