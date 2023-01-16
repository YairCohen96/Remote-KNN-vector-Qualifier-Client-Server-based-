#include "CommandThree.h"

using namespace std;

void CommandThree::execute() {
    //check avalability for runchecking if not exist print "data upload please."
    if(!validator.existFiles(my_data.unclass_path, my_data.class_path)){
        Command::dio->write("please upload data.\n");
    }
    //run the check and when finish write "complete data classifying"
    else {
        KnnCalc knn(my_data.k, my_data.class_path, my_data.distance);
        ifstream inFile;
        inFile.open(my_data.unclass_path);
        if (!inFile.is_open())
        { 
            // error openning file
            return;
        }
        
        string s;
        int counter = 0;
        //result vector.
        vector<pair<double, string>> runCheck;
        while (getline(inFile, s))
        {
            ++counter;
            vector<double>  vectorFromFile = knn.getVTFromCSVLine(s).first;
            pair<double, string> currentVectType;
            currentVectType.first = counter;
            knn.getCalc().setV1(vectorFromFile);
            currentVectType.second = knn.launchCheckVectors();
            //check if something failed
            if(currentVectType.second.size() == 0){
                //failed = true;
                //counter -= 1; the idea to do so was for the print at 4 be consecutive but it suppose to be as the line in text
                continue;
            }else {
               runCheck.push_back(currentVectType) ;
            }
        }
        my_data.set_results(runCheck);
        update_after_executed(my_data);
        Command::dio->write("classifying data complete\n");
    }
}