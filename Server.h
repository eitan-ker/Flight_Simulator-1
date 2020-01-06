
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
    int sock_num;
 public:
    Server(int client_socket) {
        this->sock_num = client_socket;
    }
    ~Server() {
        close(sock_num);
    }
  void runServer(int client_socket);
};

#endif //FLIGHTSIMULATOR__SERVER_H_
