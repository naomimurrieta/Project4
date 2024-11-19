//
// Created by MNGal on 11/13/2024.
//

#ifndef PROJECT4_DOCUPAR_H
#define PROJECT4_DOCUPAR_H

#include "InHan.h"
#include "porter2_stemmer.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"

#include <unordered_set>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <regex>

using namespace std;
using namespace rapidjson;
using namespace Porter2Stemmer;

struct DocumObje{

    //extracting the information that the user wants from the various documents
    string title;
    string publication;
    string date;
    string text;

};

class DocuPar {
private:
    //we are creating the shell copy so that the query engine and document parser point
    //to index handler
    InHan* ih;
    unordered_set<string> stopwords;

public:
    //constructor
    DocuPar();
    //we are not allocating a deep copy so no rule of three...we are doing a shell copy
    void setIndex(InHan*);

    void readStopWords();

    //iterate every file
    void readFolder(string);

    //read a jason file
    void parseJson(string);

    //function that will gather all the impor data
    DocumObje getDocData(string);

};


#endif //PROJECT4_DOCUPAR_H
