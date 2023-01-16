#include "CommandFour.h"

using namespace std;

/**
 * execute - emplmntation of command header.
*/
void CommandFour::execute() {
    //check avalability for runchecking if not exist print "data upload please."
    if(!validator.existFiles(my_data.unclass_path, my_data.class_path)){
        Command::dio->write("please upload data.\n");
    } else if (!my_data.results.size())
    {
        Command::dio->write("please classify the data.\n");
    } else {
        int i, endI = my_data.results.size();
        for (i = 0; i < endI; i++)
        {
            //string s = to_string(my_data.results.at(i).first) + "\t" + my_data.results.at(i).second + "\n";
            Command::dio->write(to_string(my_data.results.at(i).first) + "\t" + my_data.results.at(i).second + "\n");
        }
        Command::dio->write("done.\n");
    }
    
}