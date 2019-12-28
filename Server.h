#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include "Singleton.h"


using namespace std;

class Server {
public:
    void runServer(int port);
};