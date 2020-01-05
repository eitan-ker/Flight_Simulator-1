
#ifndef FLIGHTSIMULATOR__SERVER_H_
#define FLIGHTSIMULATOR__SERVER_H_

#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include "Singleton.h"

class Server {
private:
    int client_socket;
 public:
    Server(int sock_num) {
        this->client_socket = sock_num;
    }
    ~Server() {
        close(client_socket);
    }
  void runServer(int client_socket);
};

#endif //FLIGHTSIMULATOR__SERVER_H_
