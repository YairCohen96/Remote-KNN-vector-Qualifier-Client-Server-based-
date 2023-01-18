#include "CommandThree.h"
#include <filesystem>
#include <cstdio>

using namespace std;

/**
 * execute - emplmntation of command header.
*/

void CommandThree::execute() {
    //check avalability for runchecking if not exist print "data upload please."
    //DataSet mine = my_data;
    if(!validator.existFiles(my_data->unclass_path, my_data->class_path)){
        Command::dio->write("0");
        string retToMen = Command::dio->read();
    }
    //run the check and when finish write "complete data classifying"
    else {
        string retToWriteing;
        //first sent classify path.
        Command::dio->write(my_data->class_path);
        retToWriteing = Command::dio->read();
        //second sent unclassify path.
        Command::dio->write(my_data->unclass_path);
        string classVect =  Command::dio->read();
        
        //get all classify vectors as: string from client as vector and type and save as pair of vector and type.
        //"f" notify endof clasiffy
        
        //vector <pair<vector<double>, string>> classVectorsVect;
        
        ofstream out_file;
        out_file.open("classify.txt");
        
        while(classVect[0] != 'f'){
            out_file << classVect << endl;
            Command::dio->write(" ");
            classVect =  Command::dio->read();
        }
        out_file.close();

        KnnCalc knn(my_data->k, "classify.txt", my_data->distance);

        //get all unclass vectors as: string with only vector.and classify each one and save in the result.
        int counter = 0;
        //result vector.
        vector<pair<double, string>> runCheck;
        Command::dio->write(" ");
        classVect =  Command::dio->read();
        while (classVect[0] != 'f')
        {
            
            ++counter;
            vector<double>  vectorFromFile = knn.getVTFromCSVLine(classVect).first;
            pair<double, string> currentVectType;
            currentVectType.first = counter;
            knn.setInputVector(vectorFromFile);
            currentVectType.second = knn.launchCheckVectors();
            //check if something failed
            if(currentVectType.second.size() == 0){
                //failed = true;
                //counter -= 1; the idea to do so was for the print at 4 be consecutive but it suppose to be as the line in text
                //continue;
            }else {
               runCheck.push_back(currentVectType) ;
            }
            Command::dio->write(" ");
            classVect =  Command::dio->read();
            
        }

        //set result:
        my_data->set_results(runCheck);
        //update_after_executed(my_data);

        //send finish
        Command::dio->write("classifying data complete\n");
        string backToMain =  Command::dio->read();

        remove("classify.txt");

        /**
         * what if failed in middle?:
         * the files wasnt good(we check only opening)...
         * 
         */

        
    }
}