//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef DEFAULTIO_H
#define DEFAULTIO_H
#include <string>
#include <iostream>

using namespace std;
class DefaultIO {
protected:
    int client_sockfd = -1;
    
public:
    virtual void write(string text) = 0;
    virtual string read() = 0;
    int getClientSockfd () {return client_sockfd;}
    void setClientSockfd (int upd) {client_sockfd = upd;}
};


#endif
