//
// Created by yair cohen and ahiya schneider on 10/01/23.
//

#ifndef DATASET_H
#define DATASET_H
#include <vector>
#include<string>
using namespace std;
//inherate two interfaces - listener and notifier
class DataSet {
public:
    //DataSet data - {int k, string unclass path, string class path, vector of pairs(int,string) results, string distance};
    int k = 5;
    string unclass_path, class_path, distance = "EUC";
    vector<pair<double, string>> results;
    void setK(int j);
    void set_unclass(string path);
    void set_class(string path);
    void set_distance(string dist);
    void set_results(vector<pair<double, string>> update);

    
};


#endif
