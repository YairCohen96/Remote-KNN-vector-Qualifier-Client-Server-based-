//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef COMMANDEIGHT_H
#define COMMANDEIGHT_H
#include <string>
#include <iostream>
#include "DefaultIO.h"
#include "SocketIO.h"
#include "StandardIO.h"
#include "Command.h"

using namespace std;
class CommandEight : public Command
{
private:
public:
    void execute();
};

#endif
