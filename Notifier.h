//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef NOTIFIER_H
#define NOTIFIER_H
#include <vector>
#include <Listener.h>
using namespace std;
// inherate two interfaces - listener and notifier
class Notifier
{
public:
    vector<Listener> listeners;
    virtual void update_after_executed(DataSet data)
    {
        for (int i = 0; i < listeners.size(); i++)
        {
            listeners.at(i).setData(data);
        }
    };
};

#endif
