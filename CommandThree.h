//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef COMMANDTHREE_H
#define COMMANDTHREE_H
#include <string>
#include <iostream>
#include "DefaultIO.h"
#include "SocketIO.h"
#include "StandardIO.h"
#include "Command.h"
#include "KnnCalc.h"

using namespace std;
class CommandThree : public Command
{
private:
    //KnnCalc k;
public:
    void execute();
};

#endif
