//REFERENCES:
//ALEC TUTOR
//weeks of work
//chatgpt

#include "userIn.h"
#include <iostream>

//argc should be at least 2
int main(int argc, char** argv) {
    if (argc < 2){
        cerr << "Not enough command lines" << endl;
        exit(1);

        //if the first argument is 1 then print out indexf
    }else {
        string mode = argv[1];
        userIn ui;


        if (mode == "index") {
            if (argc < 3) {
                cerr << "Not enough command lines" << endl;
            }
            //extracting directory adn passing the directory
            ui.runPerser(argv[2]);

            //creating the persistance
            ui.createPer();
        } else if (mode == "query") {
            //making sure we have enough arguments
            if (argc < 3) {
                cout << "ERROR" << endl;
                exit(1);
            }
            ui.readPers();
            ui.runQue(argv[2]);
            //calling the function that will print out all the information
        } else if (mode == "ui") {
            ui.startUserIn();
        } else {
            cout << "ERROR" << endl;
            exit(1);
        }
    }
    return 0;



        }

