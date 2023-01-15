//
// Created by oem on 12/2/22.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "KnnCalc.h"
#include "DistanceCalc.h"
#include <utility>
#include <bits/stdc++.h>
#include <map>

using namespace std;

/**
 * class KnnCalc will use DistaceCalc to calculate a distance from one vector of data to
 * its K neighbors and conclude its kind accordingly
 */

/**
 * constructor
 * param:
 * j the int that serve as k for k nearest.
 * file - the path to the file.
 * type - type of wanted distances.
 * 
 * other fields:
 * vector<vector<double>> vectorList      initialized in launch
   vector<pair<string, double>> distanceList;   initialized in launch
   calc already initialized
 * 
 */
KnnCalc::KnnCalc(int newK, string file, string type)
{
    k = newK;
    inputFile = file;
    distanceType = type;
}

/**
 * gets a pair of vector and its Type classification from a data file
 * could be also an unclassified data (string will be empty)
*/
pair<vector<double>, string> KnnCalc::getVTFromCSVLine(string s){
    pair<vector<double>, string> pair1;
    pair1.second = "";
    vector<double> v;
    if(!valid.validVectorAndType(s)){
        pair1.first = v;
    }else {
        istringstream ss(s);
        string temp = "";
        while(ss){
            double x;
            ss >> x;
            v.push_back(x);
            
            ss.get();
            if (!isdigit(ss.peek())) {break;}
        }
        /*
         * check if in ss remained numbers if so exit.
        * check if the next char of stream is part of number or part of the name.
        * is it okay to string - a type, to start with a number
        */
        ss >> temp;
        pair1.first = v;
        pair1.second = temp;
    }
    return pair1;
}

/**
 * setDistanceList - safly collects the right distances from the input vector (according to chosen metrica)
 * to a list of pairs - <distance, type of specific vector according to file>
 * eventually sort the list - prep for finding first k neighbors
 */
int KnnCalc::setDistanceList()
{
    ifstream inFile;
    inFile.open(inputFile);
    if (!inFile.is_open())
    { 
        // error openning file
        return 0;
    }
    // int v1Length = calc.getV1().size();
    // vector<double> v;
    string s;
    while (getline(inFile, s))
    {
        pair<vector<double>, string>  pair1 = getVTFromCSVLine(s);
        //the vector that entered is smaller than the existing vector.
        if (pair1.first.size() != calc.getV1().size() || pair1.first.size() == 0)
        {
            return 0;//to stop or continue for the next line.
        }
        calc.setV2(pair1.first);
        vectorList.push_back(pair1.first);
        pair<double, string> p1;
        p1.first = wantedDist(); //wantedDist return -1 if it failed.
        //p1.second = "";
        p1.second = pair1.second;
        //check if it failed.
        if(p1.first == -1){
            return 0;
        }
        distanceList1.push_back(p1);
    }
    inFile.close();
    sort(distanceList1.begin(), distanceList1.end());
    return 1;
}

/**
 * wantedDist - search for the wanted type of distance and return the double value.
 * return the wanted dist.
 */
double KnnCalc::wantedDist()
{
    if (!distanceType.compare("AUC"))
    {
        return calc.euclidean_Distance();
    }
    else if (!distanceType.compare("MAN"))
    {
        return calc.manhattan_Distance();
    }
    else if (!distanceType.compare("CHB"))
    {
        return calc.chebyshev_Distance();
    }
    else if (!distanceType.compare("CAN"))
    {
        return calc.canberra_Distance();
    }
    else if (!distanceType.compare("MIN"))
    {
        return calc.minkowski_Distance();
    }
    // cout << "not valid distance";
    // exit(1);
    return -1;
}

/**
 * TheMostReturnType - search maximal frequency of type within the first k neighbors in the list and returns it.
 */
string KnnCalc::TheMostReturnType()
{
    multimap<string, double> distanceMap1;
    // make sure that k is the smaller between given k and given vectors amount
    int listSize = distanceList1.size();
    if (listSize == 0) {
        string s = "";
        return s;
    }
    int localK = std::min(listSize, k);
    for (int i = 0; i < localK; i++)
    {
        distanceMap1.insert(pair<string, double>(distanceList1.at(i).second, distanceList1.at(i).first));
    }
    pair<double, string> max1;
    max1.first = 0;
    map<string, double>::iterator it1;
    for (it1 = distanceMap1.begin(); it1 != distanceMap1.end(); it1++)
    {
        if (max1.first < distanceMap1.count(it1->first))
        {
            max1.first = distanceMap1.count(it1->first);
            max1.second = it1->first;
        }
    }
    return max1.second;
}

/**
 * launchCheckVectors - ask for vector and return the type according to knn.
 * the method will run as long as the user wishes.
 * return - 0 if failed 1 for succes.
 */
string KnnCalc::launchCheckVectors()
{
    //while (true)
    //{
        // reset everything to beggining - for new input.
        vectorList.clear();
        distanceList1.clear();
        // for convinience - make sure the file to open is valid before taking input from user
        ifstream inFile;
        inFile.open(inputFile);
        if (!inFile.is_open())
        { // error openning file
            //cout << "error openning file";
            return "";
        }
        inFile.close();
        // launch the sequence.
        //calc.setV1(calc.createInputVector());
        int set = setDistanceList();
        string respon;
        if (!set) {
            respon = "";
            return respon;
        }
        return TheMostReturnType();
        //cout << "the type is: " + TheMostReturnType() + '\n';
    //}
}

/**
 * validString - validate if from given line from the file can generate a vector.
 * return true if from the string can be generated a vector.
*/
bool KnnCalc::validString(string s)
{
    int i = 0, sLen = s.length();
    int v1Size = calc.getV1().size(), v2Size = 0;
    bool minusF = false, dotF = false, letterEF = false, numF = false;
    for(i = 0; i < sLen; i++) {
        //the new vector is bigger than the user vector
        if(v2Size > v1Size){
            return false;        
        }else if(s[i] == ',' && numF){
            // seperator detected so prepare for new number.
            v2Size++;
            minusF = false;
            dotF = false;
            letterEF = false;
            numF = false;
        }else if(s[i] == '-'){
            //do some checks after find '-'char.
            if(numF || minusF){
                if(s[i - 1] != 'e' && s[i - 1] != 'E'){
                    // cout<<"there is '-' in wrong place";
                    // exit(1);
                    return false;
                }
            }
            minusF = true;
        }else if(s[i] == '.'){
            //do checks after see dot.
            if(!numF || dotF){
                return false;
            }
            dotF = true;
        }else if((s[i] < '0' || s[i] > '9') && v1Size > v2Size){
            if(s[i] == 'e' || s[i] == 'E'){
            }
            else {
                // cout <<s[i];
                // cout << "  there is letter where it shoudnt be in the file \n";
                // exit(1);
                return false;
            }
        } else if(s[i] >= '0' && s[i] <= '9') {
            numF = true;
        }
    }
    return true;
}

/**
 * setInputVector- setter for user vector.
*/
void KnnCalc::setInputVector(vector<double> update) {
    calc.setV1(update);
}

/**
 * getCalc - getter to calc.
*/
DistanceCalc KnnCalc::getCalc(){
    return calc;
}