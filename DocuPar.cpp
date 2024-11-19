//
// Created by MNGal on 11/13/2024.
//

#include "DocuPar.h"

//change to null ptr
void DocuPar::setIndex(InHan *i) {
    //shallow copy
    ih = i;

}

void DocuPar::readStopWords() {
    //go down the list and stem them and add them to our unorder set
    ifstream input("../stopwords.txt");
    //make sure hte file opened
    if (!input.is_open()){
        cerr << "FAiled to open the file of stopwords" << endl;
        exit(1);
    }
    //delete everyting in the hash table to make sure it is empty
    stopwords.clear();
    while(!input.eof()){
        string word;
        //read the next stop word
        getline(input, word);

        //stop if theres no words after
        if(word.empty()){
            break;
        }

        //removes white space fo the end of the string
        trim(word);

        //actually stem the word
        stem(word);

        //adding them to the set
        stopwords.insert(word);


    }
    input.close();
}

//open all the archive folder and make adjustments
void DocuPar::readFolder(string folder) {

    //itr=iterator
    //transverse the data set from the folder
    auto itr = filesystem::recursive_directory_iterator(folder);

    for(const auto& file : itr){
        //make sure this is a jason file
        if(file.is_regular_file() && file.path().extension().string() == ".json"){
            parseJson(file.path().string());
        }
    }
}


void DocuPar::parseJson(string filename) {
    ifstream input(filename);
    if (!input.is_open()){
        cerr << "FAiled to open the file: " << filename << endl;
        exit(1);
    }

    //so that json can understand
    IStreamWrapper isw (input);

    //lessen the many get lines by making json making it do it
    Document doc;
    doc.ParseStream(isw);

    //extract the text so json cna read
    string text = doc["text"]. GetString();

//fancier tokenizer(Regex)

    //anything that matches with this pattern kick it out

    //establishing patter we are looking for
    //find the word or go until the next black space---gets rid of the punctuation
    regex patt("[A-Za-z]+");

    //establishing an iterator to go through all the matches
    //start here and there and find any matches
    sregex_token_iterator itr(text.begin(), text.end(), patt);

    //what it will look like when the string ends
    //place holder for the end of the iteration
    sregex_token_iterator end;

    //while there are no matches until the end

    //grabbing every word and tokenizing and adding to the AVLTree
    while(itr!=end){
        //extracting the next match
        string token =*itr;
        trim(token);
        stem(token);


        //if it is not a stopword
        if(token.length() > 2 && stopwords.find(token)==stopwords.end()){
            ih ->addingWord(token, filename);
        }
        //goes to the next word
        itr++;

    }
    //extracting array with people in it
    auto people= doc ["entities"]["persons"].GetArray();
    //iterating through that array with people in it
    for(const auto& person:people){
        stringstream ss(person["name"].GetString());

        //while it is not
        while(!ss.eof()){
            string name;
            getline(ss, name, ' ');
            trim(name);
            stem(name);
            //if not whitename then add to people AVLTree
            if(!name.empty()){
                ih ->addingPeople(name, filename);
            }
        }
    }

    //extracting array with people in it
    auto orgs= doc ["entities"]["organizations"].GetArray();
    //iterating through that array with people in it
    for(const auto& org:orgs){
        stringstream ss(org["name"].GetString());

        //while it is not
        while(!ss.eof()) {
            string name;
            getline(ss, name, ' ');
            trim(name);
            stem(name);
            //if not whitename then add to organization AVLTree
            if (!name.empty()) {
                ih->addingOrg(name, filename);
            }

        }
    }
    input.close();
}

//constructor
DocuPar::DocuPar() {
    //read through the stop words
    readStopWords();

    ih = nullptr;
}

DocumObje DocuPar::getDocData(string path) {
    ifstream input(path);
    if (!input.is_open()){
        cerr << "FAiled to open the file: " << path << endl;
        exit(1);
    }

    //so that json can understand
    IStreamWrapper isw (input);

    //lessen the many get lines by making json making it do it
    Document docu;
    docu.ParseStream(isw);
    //creating an object with all attributes
    DocumObje doc;

    //Stores the information and should display it
    doc.title = docu["title"].GetString();
    doc.publication = docu["thread"]["site"].GetString();
    doc.text = docu["text"].GetString();
    doc.date = docu["published"].GetString();
    input.close();

    return doc;



}




