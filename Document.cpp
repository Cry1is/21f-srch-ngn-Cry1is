//
// Created by Zachary on 11/21/2021.
//

#include "Document.h"

Document::Document() {
    id = "";
    title = "";
    text = "";
}

Document::Document(string id, string title, string text) {
    this->id = id;
    this->title = title;
    this->text = text;
}

bool Document::operator==(const Document& other) const { return this->id == other.id; }
bool Document::operator<(const Document& other) const { return this->id < other.id; }
bool Document::operator>(const Document& other) const { return this->id > other.id; }

string Document::getID() { return this->id; }
string Document::getTitle() { return this->title; }
string Document::getText() { return this->text; }
double Document::getFreq(string word) { return (1.0*words.find(word)->second)/words.size(); }
double Document::TF_IDF(string word, vector<string>& wordDocs, unordered_map<string, Document>& documents) {
    double wordFreq = getFreq(word);
    double invDocFreq = 1.0 - 1.0*wordDocs.size()/documents.size();
    return wordFreq*invDocFreq;
}

int Document::wordCount(string word) { return words.at(word); }

void Document::addText(AVLTree<string, vector<string>>& tree, unordered_map<string, int>& wordList) {
    stringstream ss(text);

    while (ss.good()) {
        string word;
        ss >> word;

        if (word.size() < 4 || word.size() > 20 || !isalpha(word[0]))
            continue;

        if (wordList.find(word) != wordList.end()) {
            wordList.find(word)->second++;
            continue;
        }

        wordList.insert(pair<string, int>(word, 1));
        stemWord(word);

        if (words.find(word) == words.end()) {
            vector<string> docs;
            tree.insert(word, docs).push_back(this->id);
            words.insert(pair<string, int>(word, 1));
        }
        else
            words.find(word)->second++;
    }
}

void Document::stemWord(string& temp) {
    wstring wword(temp.begin(), temp.end());
    stemming::english_stem<wstring> StemEnglish;
    StemEnglish(wword);
    string word(wword.begin(), wword.end());
    temp = word;
    for (int i = 0; i < temp.size(); i++)
        temp[i] = tolower(temp[i]);
}