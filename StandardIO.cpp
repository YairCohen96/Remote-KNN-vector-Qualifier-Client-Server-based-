#include "StandardIO.h"

using namespace std;

/**
 * write - write given text to given socket
 * @param text - string to send.
*/
void StandardIO:: write(string text) {
    cout << text;
}

/**
 * read - read from the given socket.
 * @return input string
*/
string StandardIO:: read() {
    string input;
    getline(cin, input);
    return input;
}