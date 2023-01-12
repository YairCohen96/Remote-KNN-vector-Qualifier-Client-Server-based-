//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef COMMANDTWO_H
#define COMMANDTWO_H
#include <string>
#include <iostream>
#include "DefaultIO.h"
#include "SocketIO.h"
#include "StandardIO.h"
#include "Command.h"
using namespace std;
class CommandTwo : public Command
{
private:
public:
    void execute();
};

#endif
