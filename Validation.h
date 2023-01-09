#ifndef VALIDATION_H
#define VALIDATION_H

#include <string.h>
#include <string>
#include <utility>
#include <vector>
#include <list>

using namespace std;

class Validation {
private:
    
        

    
public:
    Validation();
    ~Validation();
    bool validK(string str);
    bool validDist(string distanceType);
    bool validVector(string s);
    bool validVDK(vector<string> strVectt);
    bool validVectorsCompare(vector<double> v1, vector<double> v2);
    bool validVectorAndType(string str);
    vector<string> strToKDV(string str);
};


#endif
