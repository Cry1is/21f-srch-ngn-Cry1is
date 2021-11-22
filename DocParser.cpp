//
// Created by Zachary on 11/17/2021.
//

#include "DocParser.h"

DocParser::DocParser() {
    this->path = "";
    this->max = 0;
}

DocParser::DocParser(string path, int max) {
    this->path = path;
    this->max = max;
}

void DocParser::getFiles() {
    DIR *dir;
    struct dirent *ent;
    struct dirent *subEnt;

    int i = 0;

    if ((dir = opendir(path.c_str()))) {

        while ((ent = readdir(dir))) {
            DIR *subDir;
            string folderName = ent->d_name;
            if (folderName.find_last_of('.') == folderName.size() - 1 || folderName.find_last_of("..") == folderName.size() - 1) continue;
            string subPath = path + "/" + ent->d_name;
            if (ent->d_name[0] == '3') continue;

            if ((subDir = opendir(subPath.c_str()))) {
                cout << ent->d_name << endl;
                long count = 0;
                while ((subEnt = readdir(subDir))) {
                    string fileName = subEnt->d_name;

                    if (fileName.find_last_of(".json") == -1) continue;
                    if (fileName.find_last_of('.') == fileName.size() - 1 || fileName.find_last_of("..") == fileName.size() - 1) continue;

                    count += parseFile(subPath + "/" + fileName);
                    i++;
                    if (i%1000 == 0) {
                        cout << i << ": " << count << endl;
                        count = 0;
                    }
                    if (i >= max)
                        break;
                }
                closedir(subDir);
            }
            if (i >= max)
                break;
        }
        closedir(dir);
    } else {
        cout << "No directory found" << endl;
    }
    cout << "end of stuff" << endl;
}

int DocParser::parseFile(string filePath) {
    // initialize the document object
    rapidjson::Document doc;

    // open the file
    ifstream file(filePath);

    if (!file.is_open())
        throw logic_error("file " + filePath + " did not open");
    // read the file into a char array
    stringstream ss;

    file.seekg(0, ios::end);
    int length = file.tellg();
    file.seekg(0, ios::beg);
/*
    char* buffer = new char[length * 2];
    file.read(buffer, length);
    file.close();
    doc.Parse(buffer);
*/
    char* temp = new char[length + 1];
    while (file.getline(temp, length + 1, '\n')) {
        ss << temp;
    }

    file.close();
    delete[] temp;

    // parse the char array into the document object
    doc.Parse(ss.str().c_str());
    if (!doc.IsObject()) throw logic_error("file " + filePath + " did not read in correctly.");

    Document tempDoc(doc["uuid"].GetString(), doc["title"].GetString(), doc["text"].GetString());
    tempDoc.addText(tree, wordList);
    docs.insert(pair<string, Document>(tempDoc.getID(), tempDoc));

    return length;
}

AVLTree<string, vector<string>>& DocParser::getTree() { return this->tree; }
unordered_map<string, Document>& DocParser::getDocs() { return this->docs; }