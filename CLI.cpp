#include "CLI.h"

using namespace std;

/**
 * CLI - constructor
 * @param - client_sockfd
 * get socket as param and use in socket io
 */
CLI::CLI(int client_sockfd)
{

    dio = new SocketIO(client_sockfd);
}

/**
 * start - start cli start new 1-5,8 commands and call to the correct command
 */
void CLI::start()
{
    DataSet *data = new DataSet();
    CommandOne one;
    one.setData(data);
    CommandTwo two;
    two.setData(data);
    CommandThree three;
    three.setData(data);   
    CommandFour four;
    four.setData(data);
    CommandFive five;
    five.setData(data);
    // CommandEight eight;
    // eight.setData(data);
    //commands.push_back(one);
    //commands.push_back(two);
    //commands.push_back(three);
    //commands.push_back(four);
    //commands.push_back(five);
    // commands.push_back(eight);

    //  here we will need to init all dio's to be the same socket-client
    //  for now - init dio to standard
    /*one.setListeners(commands);
    two.setListeners(commands);
    three.setListeners(commands);
    four.setListeners(commands);*/
    
    string menu = "Welcome to KNN Classifier Server. Please choose an option:\n1. upload an unclassified csv data file\n2. algorithm settings\n3. classify data\n4. display results\n5. download results\n8. exit\n";

    while (true)
    {
        dio->write(menu);
        string option = dio->read();
        if (option.size() == 0)
        {
            return;
        }
        int opt;
        try
        {
            opt = stoi(option);
        }
        catch (exception e)
        {
            dio->write("invalid option.\n");
            continue;
        }

        switch (opt)
        {
        case 1:
            one.setDio(dio);
            one.execute();
            break;
        case 2:
            two.setDio(dio);
            two.execute();
            break;
        case 3:
            three.setDio(dio);
            three.execute();
            break;
        case 4:
            four.setDio(dio);
            four.execute();
            break;
        case 5:
            five.setDio(dio);
            five.execute();
            break;
        case 8:
            return;
        default:
            dio->write("invalid option.\n");
            break;
        }
    }
}