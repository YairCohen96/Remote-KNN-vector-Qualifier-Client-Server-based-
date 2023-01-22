#include "SocketIO.h"
#include <cstring>
#include <string>

using namespace std;

/**
 * SocketIO - set the client socket as given.
 * @param client_sockfd - client socket to send and recive.
*/
SocketIO::SocketIO(int client_sockfd)
{
    this->client_sockfd = client_sockfd;
};

/**
 * read - read from the given socket.
 *  @return input string
*/
string SocketIO::read()
{
    char buffer[4096] = "";
    int bytes_received = recv(client_sockfd, buffer, sizeof(buffer), 0);
    if (buffer == "-2") {
        return "";
    }
    if (bytes_received == 0)
    {
        // Client has disconnected
        close(client_sockfd);
        setClientSockfd(-1);
        return "";
        // continue;
    }

    if (bytes_received == -1)
    {
        // std::cerr << "Error receiving data from client" << std::endl;
        close(client_sockfd);
        return "";
        // continue;
        // break;
    }
    string res = string(buffer);
    return res;
};

/**
 * write - write given text to given socket
 * @param text - string to send.
*/
void SocketIO::write(string text)
{
    const char *response = text.c_str();
    int bytes_sent = send(client_sockfd, response, strlen(response), 0);
    if (bytes_sent == -1)
    {
        std::cerr << "Error sending data" << std::endl;
        close(client_sockfd);
        //throw new exception();
        //continue;
    }
};