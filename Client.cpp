
#include "Client.h"

void Client::runClient(int client_socket) {

    Singleton *database = database->getInstance();
    while (1) {
        //vector<string> data_to_send = database->getArrayOfOrdersToServer();
        int i = 0;
        for (i = 0; i < database->getArrayOfOrdersToServer().size(); i++) {
            char buffer[database->getArrayOfOrdersToServer()[i].length()];
            int j = 0;
            for (j = 0; j < sizeof(buffer); j++) {
                buffer[i] = database->getArrayOfOrdersToServer()[i][j];
            }
            int is_sent = send(client_socket, buffer, strlen(buffer), 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            } else {
          //      cout << buffer << "-----client"<< endl;
            }
            //cout << "done"<< endl;
        }
    }
    //if here we made a connection
// message to send into the sever(game)
    char hello[] = "Hi from client";
// "hello" - char[] to send as message
    int is_sent = send(client_socket, hello, strlen(hello), 0);
    if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
    } else {
        std::cout << "Hello message sent to server" << std::endl;
    }

//    char buffer[1024] = {0};
//    int valread = read( client_socket , buffer, 1024);
//    std::cout<<buffer<<std::endl;`

    close(client_socket);

}