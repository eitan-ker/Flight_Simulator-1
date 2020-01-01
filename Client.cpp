//
// Created by meni on 30/12/2019.
//

#include "Client.h"

void Client::runClient(int client_socket) {

  int is_sent=0;
  Singleton *database = database->getInstance();
  while (1) {
    database->setMutexLocked();
    vector<string> data_to_send = database->getArrayOfOrdersToServer();
    database->deleteAllElementsinOrdersToArrayVector();
    database->setMutexUnlocked();
    while(!data_to_send.empty()) {
      is_sent = send(client_socket, data_to_send[0].c_str(), strlen(data_to_send[0].c_str()), 0);
      //cout << "\'"<< data_to_send[0] << "\'"<< endl;
      data_to_send.erase(data_to_send.begin());
    }
    /*if(is_sent > 0){
      cout << "\'"<< database->getArrayOfOrdersToServer().begin()[0] << "\'"<< endl;
    }*/
      if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
      } else {
        //      cout << buffer << "-----client"<< endl;
      }
      //cout << "done"<< endl;

  }
 /* //if here we made a connection
// message to send into the sever(game)
  char hello[] = "Hi from client";
// "hello" - char[] to send as message
  //int is_sent = send(client_socket, hello, strlen(hello), 0);
  if (is_sent == -1) {
    std::cout << "Error sending message" << std::endl;
  } else {
    std::cout << "Hello message sent to server" << std::endl;
  }

//    char buffer[1024] = {0};
//    int valread = read( client_socket , buffer, 1024);
//    std::cout<<buffer<<std::endl;`*/

  //close(client_socket);

}