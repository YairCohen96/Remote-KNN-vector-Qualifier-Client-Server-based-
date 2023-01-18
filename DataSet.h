//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef DATASET_H
#define DATASET_H
#include <vector>
#include <string>
using namespace std;
// inherate two interfaces - listener and notifier
class DataSet
{
public:
    // DataSet data - {int k, string unclass path, string class path, vector of pairs(int,string) results, string distance};
    int k = 5;
    string unclass_path, class_path, distance = "AUC";
    vector<pair<double, string>> results;
    virtual void setK(int j){
        k = j;
    };
    virtual void set_unclass(string path){
        unclass_path = path;
    };
    virtual void set_class(string path){
        class_path = path;
    };
    virtual void set_distance(string dist){
        distance = dist;
    };
    virtual void set_results(vector<pair<double, string>> update){
        results = update;
    };
};

#endif
