#include "CommandFive.h"

using namespace std;

/**
 * execute - emplmntation of command header.
*/
void CommandFive::execute() {
    //check avalability for runchecking if not exist print "data upload please."
    if(!validator.existFiles(my_data.unclass_path, my_data.class_path)){
        Command::dio->write("please upload data.\n");
        string retToMen = Command::dio->read();
    } else if (!my_data.results.size())
    {
        Command::dio->write("please classify the data.\n");
        string retToMen1 = Command::dio->read();
    } else {
        int i, endI = my_data.results.size();
        for (i = 0; i < endI; i++)
        {
            //string s = to_string(my_data.results.at(i).first) + "\t" + my_data.results.at(i).second + "\n";
            Command::dio->write(to_string(my_data.results.at(i).first) + "\t" + my_data.results.at(i).second + "\n");
            string retToMen2 = Command::dio->read();
        }
        Command::dio->write("done.\n");
        string retToMen3 = Command::dio->read();
    }
    
}