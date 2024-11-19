//
// Created by MNGal on 11/15/2024.
//

#ifndef PROJECT4_USERIN_H
#define PROJECT4_USERIN_H

#include "QueryEngine.h"
#include "DocuPar.h"

class userIn {
private:
    InHan* ih;
    DocuPar dp;
    QueryEngine qe;

public:
    userIn();
    //do need to do the 3 rule bc we would dynamically allocate memory
    //copy constructor
    //copy assignment form class
    userIn(const userIn&);



    userIn& operator= (const userIn&);//assignment operator
    //overraidng an existing value



    //deleting
    ~userIn();
    //destructor

    //does all the print options
    void startUserIn();

    //must have 5 functions to print all the requirements

    void runPerser(string);
    void createPer();
    void readPers();
    void runQue(string);
    void clearIn();



















};


#endif //PROJECT4_USERIN_H
