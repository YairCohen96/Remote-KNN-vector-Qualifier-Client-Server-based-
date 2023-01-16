#include "Validation.h"
#include <string.h>
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <fstream>
using namespace std;

/**
 * Validation - empty constructor.
 */
Validation::Validation()
{
}

/**
 * ~Validation - empty distructor.
 */
Validation::~Validation()
{
}

/**
 * validK - check if the string has only digits
 */
bool Validation::validK(string str)
{
    int i, strLength = str.size();
    bool numStarted = false;
    // run on the string check if there is a non digit char
    for (i = 0; i < strLength; i++)
    {
        if (!numStarted && isdigit(str[i]))
        {
            numStarted = true;
        }
        else if (!isdigit(str[i]) && str[i] != ' ')
        {
            return false;
        }
        else if (!isdigit(str[i]) && str[i] == ' ' && numStarted)
        {
            return false;
        }
    }
    return true;
}

/**
 * validDist - compare the string to the 5 types.
 */
bool Validation::validDist(string distanceType)
{
    if (!distanceType.compare("AUC"))
    {
        return true;
    }
    else if (!distanceType.compare("MAN"))
    {
        return true;
    }
    else if (!distanceType.compare("CHB"))
    {
        return true;
    }
    else if (!distanceType.compare("CAN"))
    {
        return true;
    }
    else if (!distanceType.compare("MIN"))
    {
        return true;
    }
    return false;
}

/**
 * validVector - run validation on string to check if it can be modify to be vector of double
 */
bool Validation::validVector(string s)
{
    int i = 0, sLen = s.length();
    int v2Size = 0;
    bool minusF = false, dotF = false, letterEF = false, numF = false;
    for (i = 0; i < sLen; i++)
    {
        if (s[i] == ' ' && numF)
        {
            v2Size++;
            minusF = false;
            dotF = false;
            letterEF = false;
            numF = false;
        }
        else if (s[i] == ' ' && !numF)
        {
        }
        else if (s[i] == '-')
        {
            if (numF || minusF)
            {
                if (s[i - 1] != 'e' && s[i - 1] != 'E')
                {
                    return false;
                }
            }
            minusF = true;
        }
        else if (s[i] == '.')
        {
            if (!numF || dotF)
            {
                return false;
            }
            dotF = true;
        }
        else if ((s[i] < '0' || s[i] > '9'))
        {
            if (s[i] == 'e' || s[i] == 'E')
            {
            }
            else
            {
                cout << s[i];
                return false;
            }
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            numF = true;
        }
    }
    return true;
}

/**
 * validVectorsCompare - check if the vectors can be compared.
 */
bool Validation::validVectorsCompare(vector<double> v1, vector<double> v2)
{
    if (v1.size() != v2.size())
    {
        return false;
    }
    return true;
}

/**
 * validVDK - check if string can be modify into vector and if there is dist and k.
 */
bool Validation::validVDK(vector<string> strVect)
{
    if (strVect.size() != 3)
    {
        return false;
    }
    string vStr = strVect.at(0), distStr = strVect.at(1), kStr = strVect.at(2);
    if (validVector(vStr) && validDist(distStr) && validK(kStr))
    {
        return true;
    }
    return false;
}

bool Validation::validVectorAndType(string str)
{
    int i = 0, sLen = str.length();
    bool minusF = false, dotF = false, letterEF = false, numF = false, theType = false;
    for (i = 0; i < sLen; i++)
    {
        if (str[i] == ',' && numF)
        {
            // seperator detected so prepare for new number.
            minusF = false;
            dotF = false;
            letterEF = false;
            numF = false;
        }
        else if (str[i] == ',' && theType)
        {
            // saw allready something that can be a type so if there is something after return false.
            return false;
        }
        else if (str[i] == '-')
        {
            // do some checks after find '-'char.
            if (numF || minusF)
            {
                // after the letter E as number will come '-'.
                if (str[i - 1] != 'e' && str[i - 1] != 'E')
                {
                    return false;
                }
            }
            minusF = true;
        }
        else if (str[i] == '.')
        {
            // do checks after see dot.
            if (!numF || dotF)
            {
                return false;
            }
            dotF = true;
        }
        else if ((str[i] < '0' || str[i] > '9'))
        {
            if (str[i] == 'e' || str[i] == 'E' && !letterEF)
            {
                letterEF = true;
            }
            else
            {
                theType = true;
            }
        }
        else if (str[i] >= '0' && str[i] <= '9')
        {
            numF = true;
        }
    }
    return true;
}

/**
 * strToKDV - get a string and change it to vector of 3 strings.
 * return - vector with three strings: 1. vector of numbers, 2. distance type, 3. k.
 */
vector<string> Validation::strToKDV(string str, int assign)
{
    vector<string> stringVect;
    bool dk = true;
    if (assign == 3)
    {
        dk = false;
    }
    bool failed = false;

    if (!dk)
    {
        int endDistIndex = 0, distIndex = 0, kIndex = 0, endKIndex = 0, i, strLength = str.size();
        // find the indexes of the distance and the k.
        for (i = 0; i < strLength; i++)
        {
            if (distIndex == 0)
            {
                if (isalpha(str[i]) && i >= 1 && str[i - 1] == ' ')
                {
                    distIndex = i;
                }
            }
            else if (endDistIndex == 0)
            {
                if (!isalpha(str[i]))
                {
                    if (str[i] == ' ')
                    {
                        endDistIndex = i;
                    }
                    else
                    {
                        failed = true;
                        break;
                    }
                }
            }
            else if (kIndex == 0)
            {
                if (isdigit(str[i]))
                {
                    kIndex = i;
                }
            }
            else if (endKIndex == 0)
            {
                if (!isdigit(str[i]))
                {
                    if (str[i] == ' ')
                    {
                        endKIndex = i;
                    }
                    else
                    {
                        failed = true;
                        break;
                    }
                }
            }
            else if (endKIndex != 0)
            {
                if (str[i] != ' ')
                {
                    failed = true;
                    break;
                }
            }
        }
        // check if the k ends in the end of the string.
        if (endKIndex == 0)
        {
            endKIndex = strLength;
        }
        // didnt enetered a distance or k.
        if (distIndex == 0 || kIndex == 0 || failed)
        {
            string comment = "invalid";
            stringVect.push_back(comment);
        }
        else
        {
            string vectStr, kStr, distStr;
            // substr(starting index, length of chars to copy).
            // seperate the given string to three strings representing vector, distance,k.
            vectStr = str.substr(0, distIndex - 1);
            stringVect.push_back(vectStr);
            distStr = str.substr(distIndex, (endDistIndex - distIndex));
            stringVect.push_back(distStr);
            kStr = str.substr(kIndex, (endKIndex - kIndex));
            stringVect.push_back(kStr);
            // run validation on the strings vector.
            if (!validVDK(stringVect))
            {
                stringVect.clear();
                string comment = "invalid";
                stringVect.push_back(comment);
            }
        }
        return stringVect;
    }
    // check only Dist and K
    else
    {
        int endDistIndex = 0, distIndex = 0, i, strLength = str.size();
        for (i = 0; i < strLength; i++)
        {

            if (distIndex == 0)
            {
                if (isalpha(str[i]) && i >= 1 && str[i - 1] == ' ')
                {
                    distIndex = i;
                }
            }
            else if (endDistIndex == 0)
            {
                if (!isalpha(str[i]))
                {
                    if (str[i] == ' ')
                    {
                        endDistIndex = i;
                    }
                    else
                    {
                        failed = true;
                        break;
                    }
                }
            }
            
        }
            // check if the k ends in the end of the string.
            if (endDistIndex == 0)
            {
                endDistIndex = strLength;
            }
            // didnt enetered a distance or k.
            if (distIndex == 0 || failed)
            {
                string comment = "invalid";
                stringVect.push_back(comment);
            }
            else
            {
                string kStr, distStr;
                // substr(starting index, length of chars to copy).
                // seperate the given string to three strings representing vector, distance,k.
                kStr = str.substr(0, distIndex - 1);
                distStr = str.substr(distIndex, (endDistIndex - distIndex));
                if (validDist(distStr))
                {
                    stringVect.push_back(distStr);
                }
                else
                {
                    string comment = "invalid";
                    stringVect.push_back(comment);
                }

                
                if (validK(kStr))
                {
                    stringVect.push_back(kStr);
                }
                else
                {
                    string comment = "invalid";
                    stringVect.push_back(comment);
                }
            }
        
        return stringVect;
    }
}

bool Validation::validFile(string path)
{
    // Validate file before openning the server for clients
    ifstream inFile;
    inFile.open(path);
    if (!inFile.is_open())
    {
        // cout << "error openning file" << std::endl;
        return false;
    }
    inFile.close();
    return true;
}

bool Validation::existFiles(string file1, string file2)
{
    if (!file1.size())
    {
        return false;
    }
    if (!file2.size())
    {
        return false;
    }
    return true;
}