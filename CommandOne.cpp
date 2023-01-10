#include <CommandOne.h>

using namespace std;

void CommandOne::execute() {
    Command::dio.write("Please upload your local train CSV file.");
    string path_to_class = Command::dio.read();
    if(!validator.validFile(path_to_class)) {
        Command::dio.write("invalid input");
        return;
    }
    my_data.set_class(path_to_class);
    
    Command::dio.write("Please upload your local test CSV file.");
    string path_to_unclass = Command::dio.read();
    if(!validator.validFile(path_to_unclass)) {
        Command::dio.write("invalid input");
        return;
    }
    
    my_data.set_unclass(path_to_unclass);
    //let all other commands know
    update_after_executed(my_data);
    //here we will forward the path to the server and make sure it can be opened - if not - need to change message!
    Command::dio.write("upload complete.");
}