//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef SOCKETIO_H
#define SOCKETIO_H
#include <string>
#include <iostream>
#include "DefaultIO.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>


using namespace std;
class SocketIO : public DefaultIO
{
private:
    //int client_sockfd;
public:
    SocketIO(int client_sockfd);
    string read() override;
    void write(string text) override;
};


#endif
