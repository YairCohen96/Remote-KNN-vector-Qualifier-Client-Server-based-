//
// Created by oem on 12/2/22.
//

#ifndef KNNCALC_H
#define KNNCALC_H
#include "DistanceCalc.h"
#include "Validation.h"
#include <string>
#include <utility>

using namespace std;
class KnnCalc {
private:
    DistanceCalc calc;
    int k;               // argv[1] for holding amuont of neighbors chosen by the user (args[0])
    string inputFile;    // argv[2] - file to read neighbors from
    string distanceType; // argv[3] - chosen metric
    vector<vector<double>> vectorList;
    vector<pair<double, string>> distanceList1;
    Validation valid;

    //private methods:
    int setDistanceList();
    double wantedDist();
    
    bool validString(std::string s);
    string TheMostReturnType();    

    
public:
    KnnCalc(int j, std::string file, std::string DistanceType);
    DistanceCalc getCalc();
    string launchCheckVectors();
    void setInputVector(vector<double> update);
    pair<vector<double>, string> getVTFromCSVLine(string s);
};


#endif
