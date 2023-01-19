#include "CommandOne.h"

using namespace std;

/**
 * execute - emplmntation of command header.
 */

void CommandOne::execute()
{
    if (dio->getClientSockfd() != -1)
    {
        Command::dio->write("Please upload your local train CSV file.\n");
    }
    string path_to_class = Command::dio->read();
    if (path_to_class[0] == '1')
    {
        return;
    }

    if (dio->getClientSockfd() != -1)
    {
        Command::dio->write("Please upload your local test CSV file.\n");
    }
    string path_to_unclass = Command::dio->read();

    /*if (!validator.validFile(path_to_unclass))
    {
        Command::dio->write("invalid input\n");
    }*/

    if (path_to_unclass[0] == '1')
    {

        return;
    }

    my_data->set_class(path_to_class);
    my_data->set_unclass(path_to_unclass);
    // let all other commands know
    // update_after_executed(my_data);
    // here we will forward the path to the server and make sure it can be opened - if not - need to change message!

    // Command::dio->write("upload complete.\n");

    // Command::dio->write("upload complete.");
}