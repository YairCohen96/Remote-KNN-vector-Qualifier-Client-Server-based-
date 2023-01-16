#include "SocketIO.h"
#include <cstring>
#include <string>

using namespace std;
SocketIO::SocketIO(int client_sockfd)
{
    this->client_sockfd = client_sockfd;
};

string SocketIO::read()
{
    char buffer[4096] = "";
    // int n = read(client_sockfd, buffer, sizeof(buffer));
    int bytes_received = recv(client_sockfd, buffer, sizeof(buffer), 0);
    if (buffer == "-2") {
        return "";
    }
    if (bytes_received == 0)
    {
        // Client has disconnected
        close(client_sockfd);
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

void SocketIO::write(string text)
{
    const char *response = text.c_str();
    int bytes_sent = send(client_sockfd, response, strlen(response), 0);
    if (bytes_sent == -1)
    {
        std::cerr << "Error sending data to client" << std::endl;
        close(client_sockfd);
        //continue;
    }
};