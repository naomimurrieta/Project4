//
// Created by MNGal on 11/12/2024.
//
#include "AVLTree.h"

//Persistance

//gathering input
#include <fstream>
//parcing the files
#include <sstream>


#ifndef PROJECT4_INHAN_H
#define PROJECT4_INHAN_H


class InHan {
private:
    //3 avl trees for people org and word
    //searching for individual words and filename for document
    //refrencing to the map created in the AVLTree.h
    AVLTree < string, string> phra;
    AVLTree < string, string> org;
    AVLTree < string, string> peo;

    //add new private variable
    map<string, int> docCounts;

public:
    //3 setters to call the insert, etc
    //3 getters

    void addingWord(string word, string doc){
        //add words to tree and map
        addDocCount(doc);
        phra.insert(word,doc);
    }
    map<string,int> getWord(string word){
        return phra.getNode(word);
    }


    void addingOrg(string word, string doc){
        addDocCount(doc);
        org.insert(word,doc);
    }
    map<string,int> getOrg(string word){
        return org.getNode(word);
    }


    void addingPeople(string word, string doc){
        addDocCount(doc);
        peo.insert(word,doc);
    }
    map<string,int> getPeo(string word){
        return peo.getNode(word);
    }

    //will store in an output file
    void createPersistence();
    void readPersistence();

    int getDocCount(string doc){
        return docCounts[doc];
    }
    void addDocCount(string doc){
        if(docCounts.find(doc) == docCounts.end()){
            //never seen before
            docCounts[doc]=1;
        }else{
            docCounts[doc]++;
        }
    }


};


#endif //PROJECT4_INHAN_H
