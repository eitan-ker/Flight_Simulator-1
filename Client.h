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
    int client_socket;
public:
    Client(int sock_num) {
        this->client_socket = sock_num;
    }
    ~Client() {
        close(client_socket);
    }
    void runClient(int client_socket);
};


#endif //FLIGHTSIMULATOR_CLIENT_H
