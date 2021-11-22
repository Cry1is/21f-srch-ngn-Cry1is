//
// Created by Zachary on 11/21/2021.
//

#ifndef INC_21F_SRCH_NGN_DOCUMENT_H
#define INC_21F_SRCH_NGN_DOCUMENT_H

#include <map>
#include <unordered_map>
#include <vector>
#include <sstream>

#include "AVLTree.h"
#include "include/olestem/stemming/english_stem.h"

using namespace std;

class Document {
private:
    string id, title, text;
    unordered_map<string, int> words;
public:
    Document();
    Document(string, string, string);

    bool operator==(const Document&) const;
    bool operator<(const Document&) const;
    bool operator>(const Document&) const;

    void addText(AVLTree<string, vector<string>>&, unordered_map<string, int>&);

    string getID();
    string getTitle();
    string getText();
    double getFreq(string word);
    double TF_IDF(string, vecotr<string>&, unordered_map<string, Document>&);

    int wordCount(string);
    static void stemWord(string&);
};

#endif //INC_21F_SRCH_NGN_DOCUMENT_H
