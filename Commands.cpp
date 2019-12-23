//file to write all Commands implementation
#include "Command.h"
#include "Singleton.h"
int OpenServerCommand :: execute(string str) {
 return 0;
}
OpenServerCommand ::~OpenServerCommand() {
}

int ConnectCommand :: execute(string str) {
  return 1;
}

ConnectCommand ::~ConnectCommand() {}


int DefineVarCommand::execute(string str) {
  Singleton *database=database->getInstance() ;
  string key = database->getVector().at(0);
  Var_Data temp(0,nullptr);
  database->getsymbolTableToServerMap().emplace(key,temp);
  return 1;
}
int SimCommand::execute(string str) {
  return 1;
}
int setToClientCommand::execute(string str) {
  return 1;
}
int setToSimulatorCommand::execute(string str) {
  return 1;
}
int assignCommand::execute(string str) {
  return 1;
}