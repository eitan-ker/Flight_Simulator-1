//
// Created by meni on 22/12/2019.
//

#ifndef FLIGHTSIMULATOR__SINGLETON_H_
#define FLIGHTSIMULATOR__SINGLETON_H_
#include "Command.h"
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
    map<string,Command*> strToCommandMap;
   // map<string,Var_Data> symbolTable;
    static Singleton* instance;
    Singleton(); // will be called only when calling getInstance
public:
    static Singleton *getInstance();
    vector<string>& getVector();
    map<string,Command*> getCommandMap();
};

#endif //FLIGHTSIMULATOR__SINGLETON_H_