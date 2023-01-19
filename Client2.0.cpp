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
#include <thread>
#include "Validation.h"
#include "SocketIO.h"

using namespace std;

void printToFile(string fileName,vector<string> result) {
    ofstream outFile;
    outFile.open(fileName, std::ios::app); // open file in append mode
    if (!outFile.is_open())
    {
            return;
    }
    int i, endI = result.size();
    for (i = 0; i < endI; i++)
    {
        outFile << (result.at(i));
    }
    outFile.close(); // close file
}

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
        SocketIO socket(sock);
        // Receive data from server
        // char buffer[4096];
        // memset(buffer, 0, sizeof(buffer));
        // int expected_data_len = sizeof(buffer);
        // int read_bytes = recv(sock, buffer, expected_data_len, 0);
        // if (read_bytes == 0)
        // {
        //     std::cout << "connection closed by server" << std::endl;
        //     close(sock);
        //     return 1;
        // }
        // else if (read_bytes < 0)
        // {
        //     perror("error receiving data from server");
        //     close(sock);
        //     return 1;
        // }
        string ans = socket.read();
        // else
        // {
        std::cout << ans; //<< std::endl buffer
        //}

        // Send data to server
        string input;

        const char *data = "\n"; // = "1 2 3 4 MAN 12";
        getline(cin, input);
        if (!input.empty())
        {
            data = input.c_str();
        }
        int data_len = strlen(data);
        if (strcmp(data, "8") == 0)
        {
            // Close socket
            close(sock);
            return 0;
        }
        Validation validator;
        switch (input[0])
        {
            case '1':
                // code to execute for input starting with 1
                if (true)
                {

                    // send the input string
                    socket.write(data);
                    // recive from server message for enter train csv                   
                    ans = socket.read();

                    // print server message:"Please upload your local train CSV file.""
                    std::cout << ans;
                    // get file path from user.

                    getline(cin, input);
                    // check if it is a file.
                    if (!validator.validFile(input))
                    {
                        // send the input string
                        string notValid = "1";
                        socket.write(notValid);

                        cout << "invalid input\n";
                        break;
                    }

                    // set the sending data as the first file path
                    data = "\n";
                    if (!input.empty())
                    {
                        data = input.c_str();
                    }
                    socket.write(data);
                    
                    // the second file:
                    // recive from server message for enter test csv and if upload complete in same message.
                    ans = socket.read();

                    // print server message:"Please upload your local train CSV file.""
                    std::cout << ans;
                    // get second file path from user.
                    getline(cin, input);
                    // check if it is a file.
                    if (!validator.validFile(input))
                    {
                        // send the input string
                        string notValid = "1";
                        socket.write(notValid);

                        cout << "invalid input\n";
                        break;
                    }

                    // set the sending data as the second file path
                    data = "\n";
                    if (!input.empty())
                    {
                        data = input.c_str();
                    }
                    socket.write(data);

                    cout << "upload complete.\n";
                    // in the end the server need to send upload complete and the menu together.
                }
                break;
            case '2':
                // code to execute for input starting with 2
                if (true)
                {
                    // send the input string
                    socket.write(data);

                     ans = socket.read();
                    // print server message:"the current k, current dist"
                    std::cout << ans;
                    // get k and dist from user.
                    getline(cin, input);

                    // set the sending data as the k and dist from user.
                    data = "\n";
                    if (!input.empty())
                    {
                        data = input.c_str();
                    }
                    socket.write(data);

                    // put here a validator so send -1 if it not change (pressed enter or not valid and printed not valid)
                    }
                 //2 lines up:put here a validator so send -1 if it not change (pressed enter or not valid and printed not valid)
                break;
            case '3': {            
                // code to execute for input starting with 3
                if(true){
                //send the input string ('3')
                socket.write(input);
                
                //get first path:
                string classify = socket.read();
                 //send to server so server will send in future the menu. or the second path
                socket.write(" ");
                //if returned "0" there is no path
                if (classify[0] == '0' && classify.size() == 1){
                    cout << "please upload data.\n";                   
                } else {
                    //get second path
                    string unClassify = socket.read();
                    //dont send blank !!

                    //check if there is path???


                    //open first and send line by line. in commandThree- put in vector <pair <vector<double>, string>>
                    ifstream in_file(classify);
                    string ans;
                    while (getline(in_file, input)) {
                        socket.write(input);
                        ans = socket.read();
                    }
                    socket.write("f");
                    ans = socket.read();
                    in_file.close();

                    //open second and send line by line. in commandThree- classify the line and save in results.
                    ifstream in_file1(unClassify);
                    while (!in_file1.eof()) {
                        getline(in_file1, input);
                        socket.write(input);
                        ans = socket.read();
                    }
                    socket.write("f");
                    ans = socket.read();
                    in_file1.close();

                    //notify "classifying data complete."
                    cout << ans;
                    socket.write(" ");

                }               
                }
                //need to return to 
                break;}
            case '4':
                // code to execute for input starting with 4
                if (true) {
                //send the input string ('4') 
                socket.write(data);
                
                //recive from server message with please upload/classify or start get the results.
                ans = socket.read();
                //print server message:"please upload/classify or first result"
                std::cout << ans;
                //check if the buffer1 contain result.
                bool loop = true;
                if (ans[0] != 'p' && ans[0] != 'D'){
                    //read all of the results.
                    do{
                        //need to send data so return to place where server send result and client listen.
                        socket.write(data);
                        //read result line.
                        ans = socket.read();
                        //print server message:"please upload/classify or first result"
                        std::cout << ans;
                        if (ans[0] == 'D' || ans[0] == 'd') {
                            loop = false;
                        } 
                    } while (loop);
                    
                } 
                if (!loop)
                {
                    getline(cin, input);
                    //wait to user press enter.               
                    if(input.size() == 0){
                        input = "\n";
                    }
                    //need to send data so return to place where server send result and client listen.
                
                }
                socket.write("#");
                }
                break;
            case '5':
                // code to execute for input starting with 5
                if (true){
                //send the input string ('5') 
                socket.write("5");
                
                //recive from server message with please upload/classify or start get the results.
                string ans1 = socket.read();
                //print server message:"please upload/classify or first result"
                if (ans1[0] == 'p')
                {
                    std::cout << ans1;
                    socket.write("&");
                } else {
                    //add thread

                    //not sure this message need to shown.
                    cout << "please upload path to save the results.\n";
                    string fileName;
                    getline(cin, fileName);
                    //ifstream inFile;
                    ofstream outFile;
                    outFile.open(input, std::ios::app); // open file in append mode
                    if (!outFile.is_open())
                    {
                            cout << "error opening file.\n";
                            //need to send data so return to place where server send result and client listen.
                            socket.write("failed");
                    }else{
                        //if buffer1[0] != p print in the file
                        //outFile << ans; // write line to file
                        //start writeing to file the results.
                        bool loop = true;
                        vector <string> result;
                        result.push_back(ans);
                        do{
                            //need to send data so return to place where server send result and client listen.
                            socket.write("^");
                            //read result line.

                            ans = socket.read();

                            //print server message:"please upload/classify or first result"
                            
                            if (ans[0] == 'D' || ans[0] == 'd') {
                                loop = false;
                            } else {
                                result.push_back(ans);
                                //outFile << ans;
                            }
                        } while (loop);

                        thread t(printToFile, fileName, result);
                        t.detach();

                        // //wrap in thread and kill the thread after
                        // int i, endI = result.size();
                        // for (i = 0; i < endI; i++)
                        // {
                        //     outFile << (result.at(i));
                        // }
                        // outFile.close(); // close file
                    }
   
                }
                //wait to user press enter.
                //getline(cin, input);
                //need to send data so return to place where server send result and client listen.
                //socket.write("!");
                }
                
                break;
            case '8':
                // code to execute for input starting with 8
                break;
            default:
                // code to execute if input starts with any other character
                socket.write("6");
                break;

            // print server message:succes/failed
            //std::cout << defBuffer;
            break;
        }
        
    }
    return 0;
}
