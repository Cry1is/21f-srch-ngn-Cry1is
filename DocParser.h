//
// Created by Zachary on 11/17/2021.
//

#ifndef INC_21F_SRCH_NGN_CRY1IS_DOCPARSER_H
#define INC_21F_SRCH_NGN_CRY1IS_DOCPARSER_H

#include <iostream>
#include <dirent.h>
#include <filesystem>

#include "include/rapidjson/document.h"
#include "include/rapidjson/istreamwrapper.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/Writer.h"

using namespace std;
using namespace rapidjson;

class DocParser {
private:
    string path;
public:
    DocParser();
    DocParser(string);

    void getFiles();
    bool parseFile();
};

#endif //INC_21F_SRCH_NGN_CRY1IS_DOCPARSER_H