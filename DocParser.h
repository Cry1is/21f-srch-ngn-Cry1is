//
// Created by Zachary on 11/17/2021.
//

#ifndef INC_21F_SRCH_NGN_CRY1IS_DOCPARSER_H
#define INC_21F_SRCH_NGN_CRY1IS_DOCPARSER_H

#include <iostream>
#include <dirent.h>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

#include "include/rapidjson/document.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/Writer.h"
#include "AVLTree.h"
#include "Document.h"

using namespace std;

class DocParser {
private:
    string path;
    int max;
    AVLTree<string, vector<string>> tree;
    unordered_map<string, int> wordList;
    set<Document> docs;
public:
    DocParser();
    DocParser(string, int);

    void getFiles();
    void parseFile(string);
};

#endif //INC_21F_SRCH_NGN_CRY1IS_DOCPARSER_H