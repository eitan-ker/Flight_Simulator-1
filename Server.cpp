
#include "Server.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>


//#define PORT 8081
void Server :: runServer(int client_socket)
{

    while(1) {
        //reading from client
        char buffer[1024] = {0};

        int valread = read(client_socket, buffer, 1024);

        std::cout << buffer << std::endl;

        //writing back to client
//        char *hello = "Hello, I can hear you! \n";
//        send(client_socket, hello, strlen(hello), 0);
//        std::cout << "Hello message sent\n" << std::endl;
     //   return 0;
    }

}
