#ifndef DISTANCECALC_H
#define DISTANCECALC_H
#include <vector>
#include <cmath>
#include <float.h>
#include <string.h>
#include <string>
using namespace std;

class DistanceCalc
{
private:
    const double maxDigits = log10(DBL_MAX);
    vector<double> v1;
    vector<double> v2;
    void printDouble(double d);
public:
    DistanceCalc();
    ~DistanceCalc();
    vector<double> getV1();
    vector<double> getV2();
    void setV1(vector<double> update);
    void setV2(vector<double> update);
    double euclidean_Distance();
    double manhattan_Distance();
    double chebyshev_Distance();
    double canberra_Distance();
    double minkowski_Distance();
    void printDistances();
    vector<double> newVectorFromUser();
    vector<double> createInputVector(string str);
    bool validVectors();
};

#endif