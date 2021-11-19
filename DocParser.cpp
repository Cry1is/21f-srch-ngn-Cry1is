//
// Created by Zachary on 11/17/2021.
//

#include "DocParser.h"

DocParser::DocParser() {
    this->path = "";
}

DocParser::DocParser(string path) {
    this->path = path;
}

void DocParser::getFiles() {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            cout << ent->d_name << endl;
        }
        closedir(dir);
    } else {
        cout << "No directory found" << endl;
    }
}

bool DocParser::parseFile() {
    return true;
}