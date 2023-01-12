//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef STANDARTIO_H
#define STANDARTIO_H
#include <string>
#include <iostream>
#include "DefaultIO.h"
#include <fstream>

using namespace std;
class StandardIO : public DefaultIO
{
private:
public:
    string read() override;
    void write(string text) override;
};

#endif
