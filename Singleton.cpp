//
// Created by meni on 22/12/2019.
//
#include "Singleton.h"

Singleton *Singleton::instance = 0;
  Singleton *Singleton::getInstance() {
    if (!instance)
      instance = new Singleton;
    return instance;
  }
  vector<string>& Singleton:: getVector() {
    return this->str_array;
  }

