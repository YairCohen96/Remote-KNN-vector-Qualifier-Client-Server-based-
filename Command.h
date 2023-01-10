//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <iostream>
#include <DefaultIO.h>
#include <SocketIO.h>
#include <StandardIO.h>
using namespace std;
class Command {
protected:
    //description will change only if command is valid
    string description;
    //will be changed to socket only by a client approach
    DefaultIO dio = StandardIO();
    
public:
    virtual void execute();
};


#endif
