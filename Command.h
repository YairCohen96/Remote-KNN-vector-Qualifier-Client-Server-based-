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
#include <Listener.h>
#include <Notifier.h>
#include <Validation.h>
using namespace std;
//inherate two interfaces - listener and notifier
class Command : public Notifier, public Listener{
protected:
    
    //to hold a list of listeners.
    //description will change only if command is valid
    string description;
    //will be changed to socket only by a client approach
    DefaultIO dio = StandardIO();
    Validation validator;
    
public:
    virtual void execute();
};


#endif
