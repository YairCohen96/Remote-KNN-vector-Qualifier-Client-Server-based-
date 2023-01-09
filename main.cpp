#include "DistanceCalc.h"
#include "KnnCalc.h"
#include <iostream>
#include <unistd.h>
using namespace std;

/**
 * main - try to run the program with given args.
 * argc - the length of argv
 *  excepcted:
 * argv[1] - k as int num.
 * argv[2] - the path to the directory.
 * argv[3] - the distance type.
*/
int main(int argc, char *argv[]) {
    try
    {
        string j = argv[1];
        int kNum = stoi(j);
        // validate - k is an integer:
        if(j.compare(to_string(kNum))) { // not zero - not equal
            cout << "chosen k is not a valid integer";
            exit(1);
        }
        KnnCalc k(kNum, argv[2], argv[3]);
        k.launchCheckVectors();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << " invalid k\n"; //if the stoi failed exception trowned.
    }
    return 0;
}