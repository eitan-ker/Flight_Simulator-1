//
// Created by eizzker on 30/12/2019.
//

#ifndef FLIGHTSIMULATOR_CLIENT_H
#define FLIGHTSIMULATOR_CLIENT_H
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include "Singleton.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <cstring>

class Client {
private:
    int sock_num;
public:
    Client(int client_socket) {
        this->sock_num = client_socket;
    }
    ~Client() {
        close(sock_num);
    }
    void runClient(int client_socket);
};


#endif //FLIGHTSIMULATOR_CLIENT_H
