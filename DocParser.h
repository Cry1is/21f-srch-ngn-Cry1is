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
#include <chrono>

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
    unordered_map<string, Document> docs;

    chrono::duration<double> direntTime, ifstreamTime, jsonParseTime, addTextTime, seekgTime;
public:
    DocParser();
    DocParser(string, int);

    void getFiles();
    int parseFile(string);

    AVLTree<string, vector<string>>& getTree();
    unordered_map<string, Document>& getDocs();

    void printTimes();
};

#endif //INC_21F_SRCH_NGN_CRY1IS_DOCPARSER_H