#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
using namespace std;

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
        // get: vector   distance    k
        // cout << "please choose vector, distance, k";
        // Send data to server
        string input;
        const char *data; // = "1 2 3 4 MAN 12";
        getline(cin, input);
        data = input.c_str();
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
            std::cout << buffer << std::endl;
        }
    }
    return 0;
}
