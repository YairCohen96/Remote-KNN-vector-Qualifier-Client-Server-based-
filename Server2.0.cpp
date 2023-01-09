#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "KnnCalc.h"
#include "DistanceCalc.h"
#include "Validation.h"

/**
 * main -  generate the server main .
*/
int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: tcpserver <ip-address> <port>" << std::endl;
        return 1;
    }
    
    // Validate the port number
    long port = stol(argv[2]);
    if (port <= 0 || port > 65535)
    {
        std::cerr << "Invalid port number" << std::endl;
        return 1;
    }
    // Validate file before openning the server for clients
    ifstream inFile;
        inFile.open(argv[1]);
        if (!inFile.is_open())
        { // error openning file
            cout << "error openning file" << std::endl;
            return 1;
        }
        inFile.close();
        

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
    while (true)
    {
        // Accept incoming connections
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int client_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sockfd == -1)
        {
            std::cerr << "Error accepting connection" << std::endl;
            continue;
        }
        while (true)
        {

            // Process the client's request
            char buffer[4096] = "";
            // int n = read(client_sockfd, buffer, sizeof(buffer));
            int bytes_received = recv(client_sockfd, buffer, sizeof(buffer), 0);
            if (bytes_received == 0)
            {
                // Client has disconnected
                close(client_sockfd);
                continue;
            }

            if (bytes_received == -1)
            {
                // std::cerr << "Error receiving data from client" << std::endl;
                close(client_sockfd);
                // continue;
                break;
            }

            string str(buffer), vectorAsString, respon = "";
            Validation valid;
            vector<string> strVect = valid.strToKDV(str);
            v.clear();
            dist.clear();
            kStr.clear();
            int kNum = 0;
            bool failedInPut = false;
            //check if the list of the vector distance and k is invalid.
            if (strVect.size() != 3){
                failedInPut = true;
            } else {
                vectorAsString = strVect.at(0);
                dist = strVect.at(1);
                kStr = strVect.at(2);
                kNum = stoi(kStr);
            }
            if (failedInPut)
            {
                const char *response = "Invalid Input";
                int bytes_sent = send(client_sockfd, response, strlen(response), 0);
                if (bytes_sent == -1)
                {
                    std::cerr << "Error sending data to client" << std::endl;
                    close(client_sockfd);
                    continue;
                }
                continue;
            }
            KnnCalc k(kNum, argv[1], dist); // argv[1] is the path to file from server arguments
            v = k.getCalc().createInputVector(vectorAsString);
            k.setInputVector(v);
            respon = k.launchCheckVectors();
            //check if the vectors is compareable.
            if(respon.size() == 0){
                const char *response = "Invalid Input";
                int bytes_sent = send(client_sockfd, response, strlen(response), 0);
                if (bytes_sent == -1)
                {
                    std::cerr << "Error sending data to client" << std::endl;
                    close(client_sockfd);
                    continue;
                }
                continue;
            } 
            //respon = k.TheMostReturnType();
            const char *response = respon.c_str();
            int bytes_sent = send(client_sockfd, response, strlen(response), 0);
            if (bytes_sent == -1)
            {
                std::cerr << "Error sending data to client" << std::endl;
                close(client_sockfd);
                continue;
            }

            // int endDistIndex = 0, distIndex = 0, kIndex = 0, i, strLength = str.size();
            // for (i = 0; i < strLength; i++)
            // {
            //     if(distIndex == 0){
            //         if(isalpha(str[i])){
            //             distIndex = i;
            //         }
            //     } else if(endDistIndex == 0){
            //         if(!isalpha(str[i])){
            //             endDistIndex = i;
            //         }
            //     } else if(kIndex == 0){
            //         if(isdigit(str[i])){
            //             kIndex = i;
            //         }
            //     }   
            // }
            // if (distIndex == 0)
            // {
            //     distIndex = strLength;
            // }
            //V = str.substr(0, distIndex);
            // str = str.substr(distIndex, strLength);
            // while (isdigit(iss.peek()))
            // {
            //     double x;
            //     iss >> x;
            //     v.push_back(x);
            //     iss.get();
            // }            
            // end of vector - now should be distance
            //distance
            //istringstream iss(str);
            // if (iss.eof())
            // {
            //     failedInPut = true;
            //     // const char *response = "no distance accepted!";
            //     // int bytes_sent = send(client_sockfd, response, strlen(response), 0);      
            //     // if (bytes_sent == -1)
            //     // {
            //     //     std::cerr << "Error sending data to client" << std::endl;
            //     //     close(client_sockfd);
            //     //     continue;
            //     // }
            //     // continue;
            // } else{
            //     iss >> dist;
            // }           
            // now k
            // if (iss.eof())
            // {
            //     const char *response = "no K accepted!";
            //     int bytes_sent = send(client_sockfd, response, strlen(response), 0);               
            //     if (bytes_sent == -1)
            //     {
            //         std::cerr << "Error sending data to client" << std::endl;
            //         close(client_sockfd);
            //         continue;
            //     }
            //     continue;
            // } else {
            //     iss >> kStr;
            //     int kNum = stoi(kStr);
            // }
            // iss.clear();
            //  validate - k is an integer:
            // if (kStr.compare(to_string(kNum)))
            // { // not zero - not equal
            //     cout << "chosen k is not a valid integer";
            //     exit(1);
            // }
            //KnnCalc k(kNum, argv[1], dist); // argv[1] is the path to file from server arguments
            // const char *response = k.TheMostReturnType().c_str();
            // int bytes_sent = send(client_sockfd, response, strlen(response), 0);
            // if (bytes_sent == -1)
            // {
            //     std::cerr << "Error sending data to client" << std::endl;
            //     close(client_sockfd);
            //     continue;
            // }
            // Close the client socket
            // close(client_sockfd);
        }
    }
    // Close the server socket
    close(sockfd);
    return 0;
}
