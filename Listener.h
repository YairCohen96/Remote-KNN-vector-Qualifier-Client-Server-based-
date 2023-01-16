//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef LISTENER_H
#define LISTENER_H
#include "DataSet.h"
using namespace std;
// inherate two interfaces - listener and notifier
class Listener
{
public:
    DataSet my_data;
    virtual void setData(DataSet data) { my_data = data; };

};

#endif
