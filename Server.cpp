#include "Server.h"

// runServer will get all data from game to buffer and put into map
void Server::runServer(int client_socket) {
    Singleton *database = database->getInstance();
    string next_buff = "";
    int  sim_index = 0;
    while (1) {

        //reading from client
        char buffer[1024] = {0};
        string value_buf = next_buff;
        int valread = read(client_socket, buffer, 1024);
        int i = 0, counter = 0;
        string bufferString = buffer;
        // send 1024 bites of buffer - info required is 328 bites
        for (i = 0; i < valread; i++) {
            if ((bufferString[i] == ',') || (buffer[i] == '\n')) {
                sim_index++;
                database->set_generic_smallMap(value_buf, sim_index);
                value_buf = "";
                if (buffer[i] == '\n') {
                    sim_index = 0;
                }
                continue;
            } else if (i == valread - 1) { // in case i have string that continues in the next buffer
                value_buf = value_buf + bufferString[i];
                next_buff = value_buf;
                continue;
            }
            // concatenate value
            value_buf = value_buf + bufferString[i];
        }

    }

}
