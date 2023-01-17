#include <iostream>
#include <string.h>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "Validation.h"
using namespace std;

/**
 * main - generate a client side and comunicate with user and server.
 * @param argc - num of arguments. 
 * @param argv[] - array of chars arrays.
*/
int main(int argc, char *argv[])
{
    // Validate command-line arguments
    if (argc < 3)
    {
        std::cerr << "Usage: tcp_client <ip_address> <port>" << std::endl;
        return 1;
    }

    const char *ip_address = argv[1];
    // const char *ip_address = "127.0.0.1";
    int port_no = atoi(argv[2]);
    if (port_no <= 0 || port_no > 65535)
    {
        std::cerr << "Invalid port number" << std::endl;
        return 1;
    }

    struct in_addr addr;
    int result = inet_pton(AF_INET, ip_address, &addr);
    if (result != 1)
    {
        // ip_address is NOT a valid IPv4 address
        std::cerr << "Invalid IPv4 adress" << std::endl;
        return 1;
    }

    // Create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("error creating socket");
        return 1;
    }

    // Connect to server
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(ip_address);
    sin.sin_port = htons(port_no);
    if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("error connecting to server");
        close(sock);
        return 1;
    }
    while (true)
    {
        // Receive data from server
        char buffer[4096];
        memset(buffer, 0, sizeof(buffer));
        int expected_data_len = sizeof(buffer);
        int read_bytes = recv(sock, buffer, expected_data_len, 0);
        if (read_bytes == 0)
        {
            std::cout << "connection closed by server" << std::endl;
            close(sock);
            return 1;
        }
        else if (read_bytes < 0)
        {
            perror("error receiving data from server");
            close(sock);
            return 1;
        }
        else
        {
            std::cout << buffer ;//<< std::endl
        }

        // Send data to server
        string input;

        const char *data = "\n"; // = "1 2 3 4 MAN 12";
        getline(cin, input);
        if(!input.empty()) {
        data = input.c_str();}
        int data_len = strlen(data);
        if (strcmp(data, "-1") == 0)
        {
            // Close socket
            close(sock);
            return 0;
        }
        int sent_bytes = send(sock, data, data_len, 0);
        if (sent_bytes < 0)
        {
            perror("error sending data to server");
            close(sock);
            return 1;
            }
        Validation validator;
        switch (input[0])
        {       
            case '1':
                // code to execute for input starting with 1
                if(true){
                
                //send the input string 
                int sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                
                //recive from server message for enter train csv
                char buffer1[4096] = "";
                read_bytes = recv(sock, buffer1, expected_data_len, 0);
                if (read_bytes == 0)
                {
                    std::cout << "connection closed by server" << std::endl;
                    close(sock);
                    return 1;
                }
                
                //print server message:"Please upload your local train CSV file.""
                std::cout << buffer1;
                //get file path from user.
                getline(cin, input);
                //check if it is a file.
                if(!validator.validFile(input)){
                    //send the input string 
                    string notValid = "1";
                    int sent_bytes = send(sock, notValid.c_str(), notValid.size(), 0);
                    if (sent_bytes < 0)
                    {
                        perror("error sending data to server");
                        close(sock);
                        return 1;
                    }
                    cout << "invalid input\n";
                    break;
                }
                
                //set the sending data as the first file path
                data = input.c_str();
                sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                
                //the second file:
                //recive from server message for enter test csv and if upload complete in same message.
                char buffer2[4096] = "";
                int read_bytes = recv(sock, buffer2, expected_data_len, 0);
                if (read_bytes == 0)
                {
                    std::cout << "connection closed by server" << std::endl;
                    close(sock);
                    return 1;
                }
                
                //print server message:"Please upload your local train CSV file.""
                std::cout << buffer2;
                //get second file path from user.
                getline(cin, input);
                //check if it is a file.
                if(!validator.validFile(input)){
                    //send the input string 
                    string notValid = "1";
                    int sent_bytes = send(sock, notValid.c_str(), notValid.size(), 0);
                    if (sent_bytes < 0)
                    {
                        perror("error sending data to server");
                        close(sock);
                        return 1;
                    }

                    cout << "invalid input\n";
                    break;
                }
                
                //set the sending data as the second file path
                data = input.c_str();
                sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                cout << "upload complete\n";
                //in the end the server need to send upload complete and the menu together.
            }
                break;
            case '2':
                // code to execute for input starting with 2
                if(true){
                //send the input string 
                int sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                
                //recive from server message with the existing k and dist
                int read_bytes = recv(sock, buffer, expected_data_len, 0);
                if (read_bytes == 0)
                {
                    std::cout << "connection closed by server" << std::endl;
                    close(sock);
                    return 1;
                }
                
                //print server message:"the current k, current dist"
                std::cout << buffer;
                //get k and dist from user.
                getline(cin, input);

                //set the sending data as the k and dist from user.
                data = input.c_str();
                sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                // put here a validator so send -1 if it not change (pressed enter or not valid and printed not valid)
                }
                //2 lines up:put here a validator so send -1 if it not change (pressed enter or not valid and printed not valid)
                break;
            case '3':
                // code to execute for input starting with 3
                if(true){
                //send the input string 
                int sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                
                //recive from server message with succes or failure.
                int read_bytes = recv(sock, buffer, expected_data_len, 0);
                if (read_bytes == 0)
                {
                    std::cout << "connection closed by server" << std::endl;
                    close(sock);
                    return 1;
                }
                
                //print server message:succes/failed
                std::cout << buffer;
                
                }
                //need to return to 
                break;
            case '4':
                // code to execute for input starting with 4
                if (true) {
                //send the input string ('4') 
                int sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                
                //recive from server message with please upload/classify or start get the results.
                char buffer1[4096] = "";
                int read_bytes = recv(sock, buffer1, expected_data_len, 0);
                if (read_bytes == 0)
                {
                    std::cout << "connection closed by server" << std::endl;
                    close(sock);
                    return 1;
                }
                //print server message:"please upload/classify or first result"
                std::cout << buffer1;
                //check if the buffer1 contain result.
                if (buffer1[0] != 'p' || buffer1[0] != 'd'){
                    bool loop = true;
                    //read all of the results.
                    do{
                        //need to send data so return to place where server send result and client listen.
                        int sent_bytes = send(sock, data, strlen(data), 0);
                        if (sent_bytes < 0)
                        {
                            perror("error sending data to server");
                            close(sock);
                            return 1;
                        }
                        //read result line.
                        char buffer2[4096] = "";
                        int read_bytes = recv(sock, buffer2, expected_data_len, 0);
                        if (read_bytes == 0){
                            std::cout << "connection closed by server" << std::endl;
                            close(sock);
                            return 1;
                        }
                        //print server message:"please upload/classify or first result"
                        std::cout << buffer2;
                        if (buffer2[0] == 'd') {
                            loop = false;
                        } 
                    } while (loop);
                    
                } 
                //wait to user press enter.
                getline(cin, input);
                //need to send data so return to place where server send result and client listen.
                int sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                }
                break;
            case '5':
                // code to execute for input starting with 5
                if (true){
                //send the input string ('5') 
                int sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                
                //recive from server message with please upload/classify or start get the results.
                char buffer1[4096] = "";
                int read_bytes = recv(sock, buffer1, expected_data_len, 0);
                if (read_bytes == 0)
                {
                    std::cout << "connection closed by server" << std::endl;
                    close(sock);
                    return 1;
                }
                //print server message:"please upload/classify or first result"
                if (buffer1[0] == 'p')
                {
                    std::cout << buffer1;
                } else {
                    //add thread

                    //not sure this message need to shown.
                    cout << "please upload path to save the results.\n";
                    getline(cin, input);
                    //ifstream inFile;
                    ofstream outFile;
                    outFile.open(input, std::ios::app); // open file in append mode
                    if (!outFile.is_open())
                    {
                            cout << "error opening file.\n";
                            //need to send data so return to place where server send result and client listen.
                            int sent_bytes = send(sock, data, strlen(data), 0);
                            if (sent_bytes < 0)
                            {
                                perror("error sending data to server");
                                close(sock);
                                return 1;
                            }
                    }else{
                        //if buffer1[0] != p print in the file
                        outFile << buffer1; // write line to file
                        //start writeing to file the results.
                        bool loop = true;
                        do{
                            //need to send data so return to place where server send result and client listen.
                            int sent_bytes = send(sock, data, strlen(data), 0);
                            if (sent_bytes < 0)
                            {
                                perror("error sending data to server");
                                close(sock);
                                return 1;
                            }
                            //read result line.
                            char buffer2[4096] = "";
                            int read_bytes = recv(sock, buffer2, expected_data_len, 0);
                            if (read_bytes == 0){
                                std::cout << "connection closed by server" << std::endl;
                                close(sock);
                                return 1;
                            }
                            //print server message:"please upload/classify or first result"
                            outFile << buffer2;
                            if (buffer2[0] == 'd') {
                                loop = false;
                            } 
                        } while (loop);
                        
                        
                        outFile.close(); // close file
                    }
   
                }
                //wait to user press enter.
                getline(cin, input);
                //need to send data so return to place where server send result and client listen.
                int sent_bytes = send(sock, data, strlen(data), 0);
                if (sent_bytes < 0)
                {
                    perror("error sending data to server");
                    close(sock);
                    return 1;
                }
                }
                
                break;
            case '8':
                // code to execute for input starting with 8
                break;
            default:
                // code to execute if input starts with any other character
                break;

        }
        // data = input.c_str();
        // int data_len = strlen(data);
        // if (strcmp(data, "8") == 0)
        // {
        //     // Close socket
        //     close(sock);
        //     return 0;
        // }
        // int sent_bytes = send(sock, data, data_len, 0);
        // if (sent_bytes < 0)
        // {
        //     perror("error sending data to server");
        //     close(sock);
        //     return 1;
        // }
    }
    return 0;
}
