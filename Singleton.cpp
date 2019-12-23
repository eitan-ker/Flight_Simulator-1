//
// Created by meni on 22/12/2019.
//
#include "Singleton.h"
//Constructor
Singleton::Singleton() {
    OpenServerCommand* os = new OpenServerCommand;
    ConnectCommand* cc = new ConnectCommand;
    // var
    this->strToCommandMap["openDataServer"] = os;
    this->strToCommandMap["connectControlClient"] = cc;
    // Insert var
}

Singleton *Singleton::instance = 0;

Singleton *Singleton::getInstance() {
    if (!instance)
        instance = new Singleton;
    return instance;
}

vector<string> &Singleton::getVector() {
    return this->str_array;
}

map<string, Command *> Singleton::getCommandMap() {
    return this->strToCommandMap;
}