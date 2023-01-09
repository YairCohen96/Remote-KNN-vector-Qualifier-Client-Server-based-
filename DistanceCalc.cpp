#include <vector>
#include <cmath>
#include "DistanceCalc.h"
#include <iostream>
#include <float.h>
#include <string.h>

using namespace std;

    /**
     * DistanceCalc - constructor to this class
    */
    DistanceCalc::DistanceCalc()
    {
        //get 2 vectors from user.
        //v1 = createInputVector();
        //v2 = createInputVector();
    }

    /**
     * ~DistanceCalc - distructor to this class.
    */
    DistanceCalc::~DistanceCalc()
    {
    }

    /**
     * validVectors - validate if the vectors are the same sizes.
    */
    bool DistanceCalc::validVectors()
    {
        // validate by vectors length.
        if (v1.size() != v2.size())
        {
            return false;
        }
        return true;
    }

    /**
     * printDouble - print double as shown in the example.
    */
    void DistanceCalc::printDouble(double d)
    {
        //check if d is an integer
        if (d == ceil(d) && d == floor(d))
        { 
            fixed(cout);
            cout.precision(1);
            cout << d;
        }
        //d is a real number
        else 
        {
            fixed(cout);
            cout.precision(16);
            cout << d;
        }
        cout << "\n";
    }

    /**
     * getV1 - getter for v1.
     * return v1.
    */
    vector<double>  DistanceCalc::getV1()
    {
        return v1;
    }

    /**
     * getV2 - getter for v2.
     * return v2.
    */
    vector<double> DistanceCalc::getV2()
    {
        return v2;
    }

    /**
     * setV1 - seter to v1
     * param - the new v1. 
     */
    void DistanceCalc::setV1(vector<double> update)
    {
        v1 = update;
    }

    /**
     * setV2 - seter to v2
     * param - the new v2. 
     */
    void DistanceCalc::setV2(vector<double> update)
    {
        v2 = update;
    }

    /**
     * newVectorFromUser - wait for user to enter a vector than generate from string a vector.
    */
    vector<double> DistanceCalc::newVectorFromUser(){
        string input;
        //read buffer to input
        getline(cin, input);
        vector<double> v;
        v = createInputVector(input);
        return v;
    }

    /**
     * createInputVector - creating vector from buffer.
     * return vector of double values.
    */
    vector<double> DistanceCalc::createInputVector(string input)
    {
        vector<double> v;
        string temp = ""; //input
        //set boolean varabales for negative numbers and decimal points.
        bool dotFlag = false, minusFlag = false;
        //read buffer to input
        // getline(cin, input);
        //check if there is no input
        if (input.size() == 0)
        {
            //cout << "no input entered\n";
            v.clear();
            return v;
        }
        //run on input string and generate double varabales.
        for (int i = 0; i < input.size(); i++)
        {
            //check if the char at i is digit if it is add to temp string.
            if (isdigit(input.at(i)))
            {
                temp += input.at(i);
            }
            //check pussabilitty for negative value.
            else if (!minusFlag && temp.size() == 0 && input.at(i) == '-')
            {
                //set minus flag as true.
                temp += input.at(i);
                minusFlag = true;
            }
            //check pussabilitty for dacimal value.
            else if (input.at(i) == '.' && temp.size() != 0)
            { 
                // valid dot location
                if (!dotFlag && !(temp.size() == 1 && minusFlag))
                {
                //check if the first char in '-'
                    temp += input.at(i);
                    dotFlag = true;
                }
                // input is no valid
                else
                {
                    //cout << "real number can not have more than one decimal point!\n";
                    v.clear();
                    return v;
                }
            }
            //check if the input is not a ' ' or '\n' so it a - Z or other sign that not connected to double numbers.
            else if (input.at(i) != ' ' && input.at(i) != '\n')
            {
                //cout << "real number can not contain these characters!\n";
                v.clear();
                return v;
            }
            // space key and check if temp.size is greater than 0 and smaller than double range (~308)
            else if (temp.size() != 0)
            { 
                if(temp.size() > maxDigits) { //too many digit for double range
                    //cout << "too many digit for double range - invalid input\n";
                    v.clear();
                    return v;
                }
                // if we got here we have valid number
                double valid = stod(temp);
                v.push_back(valid);
                //re set for the next double var from user
                temp = "";
                minusFlag = false;
                dotFlag = false;
            }
        }
        // check if temp is valid number within double range
        if (temp != "") {
            if(temp.size() > maxDigits) { //too many digit for double range
                    //cout << "too many digit for double range - invalid input\n";
                    v.clear();
                    return v;
                }
            // if we got here we have valid number
            double valid = stod(temp); 
            v.push_back(valid);
        }
        return v;
    }

    /**
     * euclidean_Distance - calculae the distance in euclidean method.
     * return distance.
    */
    double DistanceCalc::euclidean_Distance()
    {
        if(!validVectors()) {
            cout << "the vectors not the same length";
            exit(1);
        }
        double sum = 0;
        int i;
        for (i = 0; i < v1.size(); i++)
        {               
            // calculate all dimentions                        
            sum += pow(v1.at(i) - v2.at(i), 2); 
        }
        return sqrt(sum);
    }

    /**
     * manhattan_Distance - calculae the distance in manhattan method.
     * return distance.
    */
    double DistanceCalc::manhattan_Distance()
    {
        if(!validVectors()) {
            cout << "the vectors not the same length";
            exit(1);
        }
        double sum = 0;
        int i;
        for (i = 0; i < v1.size(); i++)
        {                               
            // calculate all dimentions
            sum += abs(v1.at(i) - v2.at(i)); 
        }
        return sum;
    }

    /**
     * chebyshev_Distance - calculae the distance in chebyshev method.
     * return distance.
    */
    double DistanceCalc::chebyshev_Distance()
    {
        if(!validVectors()) {
            cout << "the vectors not the same length";
            exit(1);
        }
        double sum = 0, max = 0;
        int i;
        for (i = 0; i < v1.size(); i++)
        {                    
            // calculate all dimentions
            sum = abs(v1.at(i) - v2.at(i)); 
            if (sum > max)
            {
                max = sum;
            }
        }
        return max;
    }

    /**
     * canberra_Distance - calculae the distance in canberra method.
     * return distance.
    */
    double DistanceCalc::canberra_Distance()
    {
        if(!validVectors()) {
            cout << "the vectors not the same length";
            exit(1);
        }
        double sum = 0, mone, machne;
        int i;
        for (i = 0; i < v1.size(); i++)
        {
            // calculate all dimentions
            mone = abs(v1.at(i) - v2.at(i));
            machne = (abs(v1.at(i)) + abs(v2.at(i)));
            if (!machne)
            {
                continue;
            }  
            sum += mone / machne;                     
        }
        return sum;
    }

    /**
     * minkowski_Distance - calculae the distance in minkowski method.
     * return distance.
    */
    double DistanceCalc::minkowski_Distance()
    {
        if(!validVectors()) {
            cout << "the vectors not the same length";
            exit(1);
        }
        double sum = 0;
        int i;
        for (i = 0; i < v1.size(); i++)
        {
            // calculate all dimentions
            sum += pow(v1.at(i) - v2.at(i), 2); 
        }
        return sqrt(sum);
    }

    /**
    * printDistances - printing all of the distances.
    */
    void DistanceCalc::printDistances()
    {
        printDouble(euclidean_Distance());
        printDouble(manhattan_Distance());
        printDouble(chebyshev_Distance());
        printDouble(canberra_Distance());
        printDouble(minkowski_Distance());
    }  
