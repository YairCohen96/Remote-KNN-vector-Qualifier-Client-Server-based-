//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef SOCKETIO_H
#define SOCKETIO_H
#include <string>
#include <iostream>
#include "DefaultIO.h"

using namespace std;
class socketIO : public DefaultIO
{
private:
public:
    string read() override;
    void write(string text) override;
};


#endif
