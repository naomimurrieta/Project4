//
// Created by MNGal on 11/12/2024.
//
#include <iostream>
#include "InHan.h"

void InHan::createPersistence() {

    //this will print the frequency of phrases, organization, and people.
    ofstream out("persistence.txt");
    out << (phra.getSize())<<endl;
    phra.printTree(out);

    out << (org.getSize())<<endl;
    org.printTree(out);

    out << (peo.getSize())<<endl;
    peo.printTree(out);

    out.close();

}

void InHan::readPersistence() {

//???REPEAT FOR PEOPLE AND ORG??


    ifstream input("persistence.txt");

    //if the file is not able open then display a message
    if(!input.is_open()){
        cout << "File failed to open" << endl;
        exit(1);
    }

    phra.clear();
    org.clear();
    peo.clear();


    string buffer;
    getline(input, buffer);

    //converting the string into an int
    int count = stoi(buffer);

    //1 interation means 1 node that needs to be added
    for(int i = 0; i < count; i++){
        getline(input, buffer);

        //makes it easier to input the files
        stringstream str(buffer);

        string word;
        //reading in the key
        getline(str, word, ';');

        //eof means end of file
        while(!str.eof()){

            //reading for the key that contains the document and the document contains teh frequency of each word
            //this will put semicolens
            //one for the document and frequency
            string doc, freqStr;
            getline(str, freqStr, ';' );
            int freq = stoi(freqStr);

            phra.insert(word, doc, freq);
        }
    }

    //One for the orgs
    getline(input, buffer);

    //converting the string into an int
    int count2 = stoi(buffer);

    //1 interation means 1 node that needs to be added
    for(int i = 0; i < count2; i++){
        getline(input, buffer);

        //makes it easier to input the files
        stringstream str(buffer);

        string word;
        //reading in the key
        getline(str, word, ';');

        //eof means end of file
        while(!str.eof()){

            //reading for the key that contains the document and the document contains teh frequency of each word
            //this will put semicolens
            //one for the document and frequency
            string doc, freqStr;
            getline(str, freqStr, ';' );
            int freq = stoi(freqStr);

            peo.insert(word, doc, freq);
        }
    }

    //One for the people

    getline(input, buffer);

    //converting the string into an int
    int count3 = stoi(buffer);

    //1 interation means 1 node that needs to be added
    for(int i = 0; i < count3; i++){
        getline(input, buffer);

        //makes it easier to input the files
        stringstream str(buffer);

        string word;
        //reading in the key
        getline(str, word, ';');

        //eof means end of file
        while(!str.eof()){

            //reading for the key that contains the document and the document contains teh frequency of each word
            //this will put semicolens
            //one for the document and frequency
            string doc, freqStr;
            getline(str, freqStr, ';' );
            int freq = stoi(freqStr);

            org.insert(word, doc, freq);
        }
    }
    input.close();
}
