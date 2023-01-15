#include "StandardIO.h"

using namespace std;
void StandardIO:: write(string text) {
    cout << text;
}

string StandardIO:: read() {
    string input;
    getline(cin, input);
    return input;
}