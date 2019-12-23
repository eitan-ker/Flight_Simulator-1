//file to write all Commands implementation
#include "Command.h"
#include "Singleton.h"
#include <string>
int OpenServerCommand :: execute(string str[]) {
 return 0;
}
OpenServerCommand ::~OpenServerCommand() {
}

int ConnectCommand :: execute(string str[]) {
  return 1;
}

ConnectCommand ::~ConnectCommand() {}


int DefineVarCommand::execute(string str[]) {
  Singleton* t = t->getInstance();
  for(int i=0; i < 2;i++){
    cout << (str[i]) << endl;
  }
  t->getCommandMap()["sim"]->execute(str);
  return 6;
}
int SimCommand::execute(string str[]) {
  Singleton* t = t->getInstance();
  if(str[1]=="->") {
    t->getCommandMap()["->"]->execute(str);
  } else if(str[1]=="<-") {
    t->getCommandMap()["<-"]->execute(str);
  }
  return 0;
}
int setToClientCommand::execute(string str[]) {
  Singleton* t = t->getInstance();
  Var_Data temp(0,str[3]);
  t->getsymbolTableFromServerMap().emplace(str[1],temp);
  return 0;
}
int setToSimulatorCommand::execute(string str[]) {
  Singleton* t = t->getInstance();
  Var_Data temp(0,str[1]);
  t->getsymbolTableToServerMap().emplace(str[1],temp);
  string c = to_string(1.05);
  t->getArrayOfOrdersToServer().emplace(t->getArrayOfOrdersToServer().begin(), "set " + str[1] + c);
  return 0;
}
int assignCommand::execute(string str[]) {
  Singleton* t = t->getInstance();
  double val = stod(str[2]);
  t->getsymbolTableToServerMap()["throttle"].set_value(val);
  return 3;
}