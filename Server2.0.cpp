#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <thread>
#include "KnnCalc.h"
#include "DistanceCalc.h"
#include "Validation.h"
#include "CLI.h"

void handleClient(int client_sockfd)
{
    // const char *response1 = "hello\n";
    // int bytes_sent1 = send(client_sockfd, response1, strlen(response1), 0);

    CLI cli(client_sockfd);
    cli.start();
    // Close the server socket
    close(client_sockfd);
}

/**
 * main -  generate the server main .
 */
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: tcpserver <ip-address> <port>" << std::endl;
        return 1;
    }

    // Validate the port number
    long port = -1;
    try{
    port = stol(argv[1]);
    }
    catch (exception e) {
        std::cerr << "Invalid port number" << std::endl;
        return 1;
    }
    if (port <= 0 || port > 65535)
    {
        std::cerr << "Invalid port number" << std::endl;
        return 1;
    }
    Validation valid;
    
    struct sockaddr_in sa;
    // Create the socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return 1;
    }

    // Bind the socket to the IP address and port
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    int result = bind(sockfd, (struct sockaddr *)&sa, sizeof(sa));
    if (result == -1)
    {
        std::cerr << "Error binding socket" << std::endl;
        return 1;
    }

    // Listen for incoming connections
    result = listen(sockfd, 5);
    if (result == -1)
    {
        std::cerr << "Error listening for connections" << std::endl;
        return 1;
    }

    vector<double> v;
    string dist;
    string kStr;
    //vector<thread> clientThreads;
    while (true)
    {
        // Accept incoming connections
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        //if (clientThreads.size() < 5)
        //{
            int client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);

            if (client_sockfd == -1)
            {
                std::cerr << "Error accepting connection" << std::endl;
                continue;
            }
            //clientThreads.emplace_back(handleClient, client_sockfd);
            thread t(handleClient, client_sockfd);
            t.detach();
        //}
        /*else
        {
            for (auto &thread : clientThreads)
            {
                if (thread.joinable())
                {
                    thread.join();
                }
            }
            clientThreads.clear();
        }*/
    }
  
    return 0;
}
