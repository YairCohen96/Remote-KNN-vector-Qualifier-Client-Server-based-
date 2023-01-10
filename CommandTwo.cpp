#include <CommandTwo.h>

using namespace std;

void CommandTwo::execute() {
    Command::dio.write("The current KNN parameters are: K =  , distance metric  = ");
    //TODO - recognize keyboard and current real k and dist on server. change them if needed and print message accordingly
    /*string path = "";
    path = Command::dio.read();
    //here we will forward the path to the server and make sure it can be opened - if not - need to change message!
    Command::dio.write("upload complete.");*/

}