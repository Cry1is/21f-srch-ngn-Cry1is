//
// Created by Zachary on 11/17/2021.
//

#include "DocParser.h"

DocParser::DocParser() {
    this->path = "";
    this->max = 0;
    this->direntTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
    this->ifstreamTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
    this->jsonParseTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
    this->addTextTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
    this->seekgTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
}

DocParser::DocParser(string path, int max) {
    this->path = path;
    this->max = max;
    this->direntTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
    this->ifstreamTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
    this->jsonParseTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
    this->addTextTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
    this->seekgTime = chrono::duration_cast<chrono::duration<double>>(chrono::high_resolution_clock::now() - chrono::high_resolution_clock::now());
}

void DocParser::getFiles() {
    DIR *dir;
    struct dirent *ent;
    struct dirent *subEnt;

    int i = 0;
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
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

                    chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
                    count += parseFile(subPath + "/" + fileName);
                    chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
                    direntTime = direntTime - chrono::duration_cast<chrono::duration<double>>(t4 - t3);
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
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    direntTime = direntTime + chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    cout << "end of stuff" << endl;
}

int DocParser::parseFile(string filePath) {
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    // initialize the document object
    rapidjson::Document doc;

    chrono::high_resolution_clock::time_point t3 = chrono::high_resolution_clock::now();
    // open the file
    ifstream file(filePath);
    chrono::high_resolution_clock::time_point t4 = chrono::high_resolution_clock::now();
    seekgTime = seekgTime + chrono::duration_cast<chrono::duration<double>>(t4 - t3);

    /*if (!file.is_open())
        throw logic_error("file " + filePath + " did not open");*/
    // read the file into a char array
    stringstream ss;

    file.seekg(0, ios::end);
    int length = file.tellg();
    file.seekg(0, ios::beg);

    char* temp = new char[length + 1];
    while (file.getline(temp, length + 1, '\n')) {
        ss << temp;
    }
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    ifstreamTime = ifstreamTime + chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    file.close();
    delete[] temp;

    // parse the char array into the document object
    t1 = chrono::high_resolution_clock::now();
    doc.Parse(ss.str().c_str());
    t2 = chrono::high_resolution_clock::now();
    jsonParseTime = jsonParseTime + chrono::duration_cast<chrono::duration<double>>(t2 - t1);
    if (!doc.IsObject()) throw logic_error("file " + filePath + " did not read in correctly.");

    t1 = chrono::high_resolution_clock::now();
    Document tempDoc(doc["uuid"].GetString(), doc["title"].GetString(), doc["text"].GetString());
    tempDoc.addText(tree, wordList);
    docs.insert(pair<string, Document>(tempDoc.getID(), tempDoc));
    t2 = chrono::high_resolution_clock::now();
    addTextTime = addTextTime + chrono::duration_cast<chrono::duration<double>>(t2 - t1);

    return length;
}

AVLTree<string, vector<string>>& DocParser::getTree() { return this->tree; }
unordered_map<string, Document>& DocParser::getDocs() { return this->docs; }
void DocParser::printTimes() {
    cout << "dirent took me " << this->direntTime.count() << " seconds." << endl;
    cout << "ifstream took me " << this->ifstreamTime.count() << " seconds." << endl;
    cout << "json took me " << this->jsonParseTime.count() << " seconds." << endl;
    cout << "addText took me " << this->addTextTime.count() << " seconds." << endl;
    cout << "seekg took me " << this->seekgTime.count() << " seconds." << endl;
}