//
// Created by meni on 22/12/2019.
//
#include "Singleton.h"
#include "Command.h"
#include "Var_Data.h"
using namespace std;

Singleton *Singleton::instance = 0;

Singleton::Singleton() {
  OpenServerCommand* os = new OpenServerCommand;
  ConnectCommand* cc = new ConnectCommand;
  DefineVarCommand* defineVar = new DefineVarCommand;
  SimCommand* simCommand = new SimCommand;
  setToClientCommand* setToClient = new setToClientCommand;
  setToSimulatorCommand* settosimulatorcommand = new setToSimulatorCommand;
  assignCommand* assigncommand = new assignCommand;
  // var
  this->strToCommandMap["openDataServer"] = os;
  this->strToCommandMap["connectControlClient"] = cc;
  this->strToCommandMap["var"] = defineVar;
  this->strToCommandMap["sim"] = simCommand;
  this->strToCommandMap["<="] = setToClient;
  this->strToCommandMap["=>"] = settosimulatorcommand;
  this->strToCommandMap["="] = assigncommand;

  // Insert var
}

Singleton *Singleton::getInstance() {
  if (!instance)
    instance = new Singleton;
  return instance;
}

vector<string> &Singleton::getVector() {
  return this->str_array;
}

map<string, Command *>& Singleton::getCommandMap() {
  return this->strToCommandMap;
}

map<string,Var_Data>& Singleton:: getsymbolTableToServerMap() {
    return this->symbolTableToServer;
}
map<string,Var_Data>& Singleton:: getsymbolTableFromServerMap() {
  return this->symbolTableFromServer;
}
map<string,double>& Singleton:: getgeneric_smallMap() {
  return this->generic_smallMap;
}
vector<string> &Singleton::getArrayOfOrdersToServer() {
  return this->orderToSendToSimulator;
}



