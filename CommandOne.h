//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef COMMANDONE_H
#define COMMANDONE_H
#include <string>
#include <iostream>
#include <DefaultIO.h>
#include <SocketIO.h>
#include <StandardIO.h>
#include <Command.h>
using namespace std;
class CommandOne : public Command
{
public:
    void execute() override;
};

#endif
