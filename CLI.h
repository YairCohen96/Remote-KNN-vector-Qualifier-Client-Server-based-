//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef CLI_H
#define CLI_H
#include "DefaultIO.h"
#include "Command.h"
#include "CommandOne.h"
#include "CommandTwo.h"
#include "CommandThree.h"
#include "CommandFour.h"
//#include "CommandFive.h"
//#include "CommandEight.h"
#include <string>

#include <vector>

using namespace std;
class CLI
{
private:
    //vector<Command> commands;
    DefaultIO *dio;

public:
    CLI();
    void start();
    
};

#endif
