//
// Created by MNGal on 11/15/2024.
//

#include "userIn.h"

userIn::userIn() {
//get rid of anything previous to that
    clearIn();
}

userIn::userIn(const userIn & ui) {
    //dynaminacilly allocate
    //call copy constructor
    //passing old index handler into the new one
    ih= new InHan(*ui.ih);
    dp = ui.dp;
    qe = ui.qe;
}

userIn &userIn::operator=(const userIn & ui) {
    delete ih;


    //dynaminacilly allocate
    //call copy constructor
    ih= new InHan(*ui.ih);
    dp = ui.dp;
    qe = ui.qe;


    return *this;


}



userIn::~userIn() {
    delete ih;
}

void userIn::startUserIn() {
    while(true){
        //printing out all the options that could be done by the functions that were given
        cout << "Enter one of these options: " << endl;
        cout << "Option 0 to quit" << endl;
        cout << "Option 1 to run the doc parser" << endl;
        cout << "Option 2 to create persistance" << endl;
        cout << "Option 3 to read the persistance" << endl;
        cout << "Option 4 to run the que" << endl;




        string choice;
        getline(cin,choice);

        //if statement to see if the choice matches the option
        //only run parser and run query have a parameter
        if (choice == "1"){
            string path;

            //prompt user for path
            getline(cin, path);
            runPerser(path);

        }
        //for running query
        if (choice == "4"){
            string query;

            //prompt user for query
            getline(cin, query);
            runQue(query);
        }
        //giving choices that do not require a parameter
        else if (choice == "2") {
            createPer();

        }
        else if (choice == "3") {
            readPers();

        }
        else{
            cout << "Invalid Input" << endl;
        }


    }

}

//creating the code for what will run the Parser
//COPY EXACTLY LIKE THAT TO THE OTHER FUNCTIONS EXCEPT THE DP PART
void userIn::runPerser(string path) {
    try{
        //so that the clear runs automaticall when the run parser is needed
        clearIn();
        dp.readFolder(path);
    }
    catch(const exception& err){
        cerr << "Failed to open the doc Perser" << endl;

        //print out the normal error message
        cerr << err.what() << endl;
    }
}


//function that will creat the Persistenace
void userIn::createPer() {
    try{
        ih->createPersistence();
    }
    catch(const exception& err){
        cerr << "Failed to create" << endl;

        //print out the normal error message
        cerr << err.what() << endl;
    }
}

//function that will run the persistance
void userIn::readPers() {
    try{

        //clearing the Index Handler
        clearIn();
        ih->readPersistence();
    }
    catch(const exception& err){
        cerr << "Failed to read" << endl;

        //print out the normal error message
        cerr << err.what() << endl;
    }
}

void userIn::runQue(string query) {
    try {
        vector<pair<double, string>> results = qe.parseQuery(query);
        qe.parseQuery(query);
        if (results.size() > 0){
            //keep looping until end of the result vector or until it hits 15
            for (int i=0; i<15 && i < results.size(); i++){

                //for the pair
                DocumObje doc = dp.getDocData(results[i].second);
                //Result (n+1)
                cout << "#" << (i + 1) << endl;

                //printing date and title and publication
                cout << "Name of Tittle: " << doc.title << endl;
                cout << "Date of Publication: " << doc.date << endl;
                cout << "Publication: " << doc.publication << endl;
                cout << endl;

            }

            string choice;
            while(choice != "0"){
                cout << "Enter the number to view the text and press 0 to exit" << endl;
                getline(cin, choice);

                //converting the string into a number
                int index = stoi(choice)-1;
                if (index >=0 && index < 15 && index < results.size()){
                    DocumObje doc = dp.getDocData(results[index].second);
                    cout << doc.text << endl;
                }

            }

        }else{
            cout << "No results found" << endl;
        }

    }
    catch(const exception& err){
        cerr << "Failed to run the que" << endl;

        //print out the normal error message
        cerr << err.what() << endl;
    }
}

void userIn::clearIn() {
    //deleting the last one
    delete ih;
    ih = new InHan;
    //allocate to a new one
    dp.setIndex((ih));
    //shell copies to the
    qe.setIndex(ih);
}
