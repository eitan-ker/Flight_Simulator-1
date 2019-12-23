//
// Created by meni on 22/12/2019.
//

#ifndef FLIGHTSIMULATOR__SINGLETON_H_
#define FLIGHTSIMULATOR__SINGLETON_H_
#include "Command.h"
#include "Var_Data.h"
#include <fstream>
#include <map>
#include <iterator>
#include <string>
#include <iostream>
#include <list>
#include <utility>
#include <fstream>
#include <regex>
#include <sstream>
using namespace std;
class Singleton {
 private:
  vector<string> str_array;
  map<string,Command*> strToCommandMap;//this is the map of string-command relation
  map<string,Var_Data> symbolTableToServer;//this the map to store data that we want to send to server
  map<string,Var_Data> symbolTableFromServer; //this is the map to store data we got from server
  map<string,double> generic_smallMap; //this is the map to store data from ‫‪generic_small.xml‬‬
  vector<string> orderToSendToSimulator;//this is the string vector which will store all new set commands to send to the simulator. you send a single set and then delete it
  static Singleton* instance;
  Singleton(); // will be called only when calling getInstance
 public:
  static Singleton *getInstance();
  vector<string>& getVector();
  map<string,Var_Data>& getsymbolTableToServerMap();
  map<string,Var_Data>& getsymbolTableFromServerMap();
  map<string,Command*>& getCommandMap();
  map<string,double>& getgeneric_smallMap();
  vector<string>& getArrayOfOrdersToServer();
};

#endif //FLIGHTSIMULATOR__SINGLETON_H_
