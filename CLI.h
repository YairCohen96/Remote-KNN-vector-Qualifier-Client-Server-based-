//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef CLI_H
#define CLI_H
#include <DefaultIO.h>
#include <Command.h>
#include <CommandOne.h>
#include <CommandTwo.h>
#include <CommandThree.h>
#include <CommandFour.h>
#include <CommandFive.h>
#include <CommandEight.h>
#include <string>

#include <vector>

using namespace std;
class CLI
{
private:
    vector<Command> commands;
    DefaultIO dio = StandardIO();

public:
    void start()
    {
        Command one = CommandOne();
        commands.push_back(one);
        Command two = CommandTwo();
        commands.push_back(two);
        Command three = CommandThree();
        commands.push_back(three);
        Command four = CommandFour();
        commands.push_back(four);
        Command five = CommandFive();
        commands.push_back(five);
        Command eight = CommandEight();
        commands.push_back(eight);
        // here we will need to init all dio's to be the same socket-client
        // for now - init dio to standard
        string menu = "Welcome to KNN Classifier Server. Please choose an option:\n1. upload an unclassified csv data file\n2. algorithm settings\n3. classify data\n4. display results\n5. download results\n8. exit\n";
        
        while (true) {
            dio.write(menu);
            string option = dio.read();
            if(stoi(option) == 8) {
                //exit
            }
            else {
                commands.at(stoi(option) - 1).execute();
            }
        }
        
    }
};

#endif
