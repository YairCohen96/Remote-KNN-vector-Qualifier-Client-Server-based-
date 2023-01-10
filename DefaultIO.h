//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef DEFAULTIO_H
#define DEFAULTIO_H
#include <string>
#include <iostream>

using namespace std;
class DefaultIO {
private:
    
    
public:
    virtual void write(string text);
    virtual string read();
    
};


#endif
