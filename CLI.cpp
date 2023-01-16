#include "CLI.h"

using namespace std;

/**
 * CLI - constructor
 * @param - client_sockfd 
 * get socket as param and use in socket io
*/
CLI::CLI(int client_sockfd) {
    dio = new SocketIO(client_sockfd);
}

/**
 * start - start cli start new 1-5,8 commands and call to the correct command
*/
void CLI::start()
{
    CommandOne one;
    //commands.push_back(one);
    CommandTwo two;
    //commands.push_back(two);
    CommandThree three;
    //commands.push_back(three);
    CommandFour four;
    //commands.push_back(four);
    //CommandFive five;
    //commands.push_back(five);
    //CommandEight eight;
    //commands.push_back(eight);
    // here we will need to init all dio's to be the same socket-client
    // for now - init dio to standard
    string menu = "Welcome to KNN Classifier Server. Please choose an option:\n1. upload an unclassified csv data file\n2. algorithm settings\n3. classify data\n4. display results\n5. download results\n8. exit\n";

    //while (true)
    //{
        dio->write(menu);
        string option = dio->read();
        if(option.size() == 0) {
            return;
        }
        if (stoi(option) == 8)
        {
            //commands.at(5).execute(); // command eight
            // exit
        }
        else
        {
            int com = stoi(option) - 1;
            one.setDio(dio);
            //commands.at(com).execute();
            one.execute();
        }
    //}
}