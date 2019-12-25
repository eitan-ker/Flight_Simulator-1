//file to write all Commands implementation
#include "Command.h"
#include "Singleton.h"
#include "Server.h"
#include <string>
#include <thread>
#include <float.h>


int OpenServerCommand::execute(vector<string> &str, int i) {
    thread *ods = new thread(&OpenServerCommand::executeServer, this, 2);
    ods->detach();

    //
    executeServer(2);
    for (int i = 0; i < 2; i++) {
        cout << "thread OSD runs 2 times" << endl;
    }
    return 2;
}

void OpenServerCommand::executeServer(int port) {
    Server *server = new Server();
    server->runServer(port);
}

int ConnectCommand::execute(vector<string> &str, int i) {
    for (int i = 0; i < 3; i++) {
        cout << "thread OSD runs 3 times" << endl;
    }
    return 3;
}
int DefineVarCommand::execute(vector<string> &str, int i) {
  int j = 0;
  Singleton* t = t->getInstance();
  string c = str.at(i+2);
  if(c=="=") {
    j = t->getCommandMap()[c]->execute(str, i);
    j+=2;
  } else if(c=="->" || c=="<-" ) {
    j = t->getCommandMap()[c]->execute(str, i+2);
  }  return j;
  }

int SimCommand::execute(vector<string> &str, int i) {
  int j = i;
  Singleton* t = t->getInstance();
  string temp = str.at(i+2);
  if(temp=="->") {
    j = t->getCommandMap()[temp]->execute(str,i);
  } else if(str.at(i+2)=="<-") {
    j = t->getCommandMap()[str.at(i+2)]->execute(str,i);
  }
  return j;
}
int setToClientCommand::execute(vector<string> &str, int i) {
  Singleton* t = t->getInstance();
  Var_Data temp(0,str.at(i+4));
  t->getsymbolTableFromServerMap().emplace(str.at(i+1),temp);
  return i+5;
}
int setToSimulatorCommand::execute(vector<string> &str, int i) {
  Singleton* t = t->getInstance();
  Var_Data temp(0,str.at(i+4));
  t->getsymbolTableToServerMap().emplace(str.at(i+1),temp);
  float c = t->getsymbolTableToServerMap()[str.at(i+1)].get_value();
  string temp1 = to_string(c);
  return i+5;
}
int PrintCommand::execute(vector<string> &str, int i) {
  cout << str.at(i+1) << endl;
  return i+2;
}
int assignCommand::execute(vector<string> &str, int i) {
  string str_val= "";
  Singleton* t = t->getInstance();
  float d = stod(str.at(i+1));
  if ((d > 0 && (d > FLT_MAX || d < FLT_MIN))
      || (d < 0 && (d < -FLT_MAX || d > -FLT_MIN))) {
    if (t->getsymbolTableToServerMap().find(str.at(i+1)) == t->getsymbolTableToServerMap().end()) {
      if (t->getsymbolTableFromServerMap().find(str.at(i+1)) == t->getsymbolTableToServerMap().end()) {
        throw "error: variable not found";
      } else {
         str_val = to_string(t->getsymbolTableFromServerMap()[str.at(i+1)].get_value());
      }
    } else {
       str_val = to_string(t->getsymbolTableToServerMap()[str.at(i+1)].get_value());
    }
    t->getArrayOfOrdersToServer().emplace(t->getArrayOfOrdersToServer().end(), "set " + t->getsymbolTableToServerMap()[str.at(i-1)].get_sim() +" "+ str_val + "/n");

  } else {
    if (t->getsymbolTableToServerMap().find(str.at(i-1)) == t->getsymbolTableToServerMap().end()) {
    throw "variable not found";
    } else {
      t->getsymbolTableToServerMap()[str.at(i-1)].set_value(d);
      string floatTostring = to_string(d);
      t->getArrayOfOrdersToServer().emplace(t->getArrayOfOrdersToServer().end(), "set " + t->getsymbolTableToServerMap()[str.at(i-1)].get_sim() +" "+ floatTostring+ "/n");
    }
  }
  return i+2;
}