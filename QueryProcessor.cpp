//
// Created by Zachary on 11/22/2021.
//

#include "QueryProcessor.h"

QueryProcessor::QueryProcessor() {}

void QueryProcessor::UI(AVLTree<string, vector<string>>& tree, unordered_map<string, Document>& docs) {
    bool exit = false;
    while (!exit) {
        int choice;
        printUI();
        cin >> choice;
        switch (choice) {
            case 1:
                search(tree, docs);
                break;
            case 2:
                readDocument();
                break;
            case 3:
                stats(tree, docs);
                break;
            case 4:
                reindex(tree, docs);
                break;
            case 0:
                exit = true;
                break;
            default: cout << "Invalid choice." << endl;
        }
    }
}

void QueryProcessor::printUI() {
    cout << "=================" << endl;
    cout << "= Search Engine =" << endl;
    cout << "=================" << endl;
    cout << "[0] exit" << endl;
    cout << "[1] make a search" << endl;
    cout << "[2] read a document" << endl;
    cout << "[3] get stats" << endl;
    cout << "[4] re-index" << endl;
    cout << "Choice: " << endl;
}

void QueryProcessor::search(AVLTree<string, vector<string>>& tree, unordered_map<string, Document>& docs) {
    cache.clear();
    string word;
    cout << "Enter a word: " << endl;
    cin >> word;
    stemWord(word);
    if (tree.find(word)) {
        vector<string> temp = tree.find(word)->second;
        for (int i = 0; i < temp.size(); i++) {
            Document doc = docs.find(temp[i])->second;
            cache.insert(pair<double, Document>(doc.TF_IDF(word, temp, docs), doc));
        }
        int j = 0;
        for (auto itr : cache) {
            if (j >= 10)
                break;
            cout << "[" << j << "] " << itr.first << ": " << itr.second.getTitle() << endl;
            j++;
        }
    }
}

void QueryProcessor::readDocument() {
    int choice;
    cout << "Select a document number: " << endl;
    cin >> choice;
    if (choice < 0 || choice > 9 || choice >= cache.size())
        cout << "Invalid choice." << endl;
    else {
        int i = 0;
        for (auto itr : cache) {
            if (i >= 10)
                break;
            if (i == choice) {
                cout << "Title: " << itr.second.getTitle() << endl;
                cout << "Text: " << itr.second.getText() << endl;
            }
            i++;
        }
    }
}

void QueryProcessor::stats(AVLTree<string, vector<string>>& tree, unordered_map<string, Document>& docs) {
    cout << "Placeholder" << endl;
}

void QueryProcessor::reindex(AVLTree<string, vector<string>>& tree, unordered_map<string, Document>& docs) {
    tree.clear();
    cout << "How many files would you like to parse?: " << endl;
    int max;
    cin >> max;
    int i = 0;

    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();

    unordered_map<string, int> wordList;
    for (auto itr : docs) {
        itr.second.addText(tree, wordList);
        i++;
        if (i%1000 == 0)
            cout << i << endl;
        if (i >= max)
            break;
    }

    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();

    chrono::duration<double> time_span = chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    cout << "It took me " << time_span.count() << " seconds." << endl;
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