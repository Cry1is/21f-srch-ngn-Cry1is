//
// Created by Zachary on 11/22/2021.
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor() {}

void QueryProcessor::search(string word, AVLTree<string, vector<string>>& tree, unordered_map<string, Document>& docs) {
    if (word == "1")
        return;
    cout << "Word: " << word << endl;
    stemWord(word);
    if (tree.find(word)) {
        vector<string> temp = sort(tree.find(word)->second);
        for (int i = 0; i < temp.size(); i++) {
            Document doc = docs.find(temp[i])->second;
            cout << doc.TF_IDF(word, temp, docs) << ": " << doc.getTitle() << endl;
        }
    }
    cout << "Search for a word (1 to exit): " << endl;
    cin >> word;
    search(word, tree, docs);
}

void QueryProcessor::stemWord(string& temp) {
    wstring wword(temp.begin(), temp.end());
    stemming::english_stem<wstring> StemEnglish;
    StemEnglish(wword);
    string word(wword.begin(), wword.end());
    temp = word;
    for (int i = 0; i < temp.size(); i++)
        temp[i] = tolower(temp[i]);
}