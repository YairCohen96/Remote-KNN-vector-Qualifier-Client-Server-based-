#include <CommandOne.h>

using namespace std;

void CommandOne::execute() {
    Command::dio.write("please upload your local train csv file.");
    string path = "";
    path = Command::dio.read();
    //here we will forward the path to the server and make sure it can be opened - if not - need to change message!
    Command::dio.write("upload complete.");
}