#include "CommandThree.h"
#include <filesystem>
#include <cstdio>
#include <thread>
#include <sstream>

using namespace std;

/**
 * execute - emplmntation of command header.
*/

void CommandThree::execute() {
    //check avalability for runchecking if not exist print "data upload please."
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
        
        ofstream out_file;
        thread::id id = this_thread::get_id();
        stringstream ss;
        ss << id;
        string file = ss.str();
        out_file.open(file);
        
        while(classVect[0] != 'f'){
            out_file << classVect << endl;
            Command::dio->write(" ");
            classVect =  Command::dio->read();
        }
        out_file.close();

        KnnCalc knn(my_data->k, file, my_data->distance);

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
            }else {
               runCheck.push_back(currentVectType) ;
            }
            Command::dio->write(" ");
            classVect =  Command::dio->read();
            
        }

        if(runCheck.size() > 0) {
            //set result:
            my_data->set_results(runCheck);
            //send finish
            Command::dio->write("classifying data complete\n");
            string backToMain =  Command::dio->read();
        } else {
            my_data->set_results(runCheck);
            Command::dio->write("data uploaded incompitable\n");
            string backToMain =  Command::dio->read();
        }
        remove(file.c_str());
    }
}