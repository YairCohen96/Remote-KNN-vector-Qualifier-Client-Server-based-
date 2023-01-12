//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef COMMANDFIVE_H
#define COMMANDFIVE_H
#include <string>
#include <iostream>
#include "DefaultIO.h"
#include "SocketIO.h"
#include "StandardIO.h"
#include "Command.h"

using namespace std;
class CommandFive : public Command
{
private:
public:
    void execute();
};

#endif
