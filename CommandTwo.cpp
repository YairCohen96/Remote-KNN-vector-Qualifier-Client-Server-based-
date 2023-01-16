#include "CommandTwo.h"

using namespace std;

void CommandTwo::execute() {
    Command::dio->write("The current KNN parameters are: K =  " + to_string(my_data.k) + ", distance metric  = " + my_data.distance + "\n");
    //TODO - recognize keyboard and current real k and dist on server. change them if needed and print message accordingly
    // get ENTER or new K and DISTANCE from user:
    string update = Command::dio->read();
    if(update.size()) { // input was entered - need to update
        //need to modify strToVDK only for KD
        string kStr, distStr;
        bool kFlag = false, distFlag = false;
        if(!validator.validK(kStr)) {
            Command::dio->write("invalid value for K\n");
            kFlag = true;
        }
        if(!validator.validDist(distStr)) {
            Command::dio->write("invalid value for metric\n");
            distFlag = true;
        }
        if (kFlag || distFlag) {
            return;
        }
        my_data.setK(stoi(kStr));
        my_data.set_distance(distStr);
        update_after_executed(my_data);
    }
}