#include "CLI.h"

using namespace std;
CLI::CLI(int client_sockfd)
{
    dio = new SocketIO(client_sockfd);
}
void CLI::start()
{
    CommandOne one;
    commands.push_back(one);
    CommandTwo two;
    commands.push_back(two);
    CommandThree three;
    commands.push_back(three);
    CommandFour four;
    commands.push_back(four);
    // CommandFive five;
    // commands.push_back(five);
    // CommandEight eight;
    // commands.push_back(eight);
    //  here we will need to init all dio's to be the same socket-client
    //  for now - init dio to standard
    one.setListeners(commands);
    two.setListeners(commands);
    three.setListeners(commands);
    four.setListeners(commands);
    string menu = "Welcome to KNN Classifier Server. Please choose an option:\n1. upload an unclassified csv data file\n2. algorithm settings\n3. classify data\n4. display results\n5. download results\n8. exit\n";

    // while (true)
    //{
    dio->write(menu);
    string option = dio->read();
    if (option.size() == 0)
    {
        return;
    }
    switch (stoi(option))
    {
    case 8:
        // command eight
        // exit
        break;
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
    /*case 5:
        five.setDio(dio);
        five.execute();
        break;*/
        default:
            return;
    }
}