//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <string>
#include <iostream>
#include "Listener.h"
#include "Validation.h"
#include "DefaultIO.h"
#include "SocketIO.h"
#include "StandardIO.h"

using namespace std;
//inherate interface - listener
class Command : public Listener{
protected:
    
    //to hold a list of listeners.
    //description will change only if command is valid
    string description;
    //will be changed to socket only by a client approach
    DefaultIO* dio;
    Validation validator;
    
public:
    virtual void execute() {} ;
    void setDio(DefaultIO* update) {dio = update;};
    /*void setListeners (vector<Command> listen) {
        int len = listen.size();
        listeners.clear();
        for (int i = 0; i < len; i++)
        {
            listeners.push_back(listen.at(i));
        }
        
    }*/
};


#endif
