//
// Created by meni on 22/12/2019.
//
#include "Singleton.h"
#include "Command.h"
#include "Var_Data.h"
using namespace std;

Singleton *Singleton::instance = 0;
/*
 * private contructor, instance created only once
 */
Singleton::Singleton() {
  OpenServerCommand* os = new OpenServerCommand;
  ConnectCommand* cc = new ConnectCommand;
  DefineVarCommand* defineVar = new DefineVarCommand;
  SimCommand* simCommand = new SimCommand;
  setToClientCommand* setToClient = new setToClientCommand;
  setToSimulatorCommand* settosimulatorcommand = new setToSimulatorCommand;
  assignCommand* assigncommand = new assignCommand;
  PrintCommand* print = new PrintCommand;
  WhileCommand* whilee = new WhileCommand;
  SleepCommand* sleep = new SleepCommand;
  IfCommand* ifcommand = new IfCommand;
  // var
  this->strToCommandMap["openDataServer"] = os;
  this->strToCommandMap["connectControlClient"] = cc;
  this->strToCommandMap["var"] = defineVar;
  this->strToCommandMap["sim"] = simCommand;
  this->strToCommandMap["<-"] = setToClient;
  this->strToCommandMap["->"] = settosimulatorcommand;
  this->strToCommandMap["="] = assigncommand;
  this->strToCommandMap["Print"] = print;
  this->strToCommandMap["print"] = print;
  this->strToCommandMap["While"] = whilee;
  this->strToCommandMap["while"] = whilee;
  this->strToCommandMap["Sleep"] = sleep;
  this->strToCommandMap["sleep"] = sleep;
  this->strToCommandMap["if"] = ifcommand;
  this->strToCommandMap["If"] = ifcommand;

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

map<string, Command*>& Singleton::getCommandMap() {
  return this->strToCommandMap;
}

map<string,Var_Data*>& Singleton:: getsymbolTableToServerMap() {
    return this->symbolTableToServer;
}
map<string,Var_Data*>& Singleton:: getsymbolTableFromServerMap() {
  return this->symbolTableFromServer;
}
map<string,float>& Singleton:: getgeneric_smallMap() {
  return this->generic_smallMap;
}
vector<string> &Singleton::getArrayOfOrdersToServer() {
  return this->orderToSendToSimulator;
}


Var_Data* Singleton::getVar_Data(string& str) {
  // search for the key(parameter) in my From and To game maps and return the pointer at the end
  if (getsymbolTableToServerMap().find(str) == getsymbolTableToServerMap().end()) {
    if (getsymbolTableFromServerMap().find(str) == getsymbolTableToServerMap().end()) {
      throw "variable doesnt exist in Maps";
    } else {
      Var_Data* temp = getsymbolTableFromServerMap()[str];
      return temp;
    }
  } else {
    Var_Data* temp = getsymbolTableToServerMap()[str];
    return temp;
  }
}
/*
 * initialize generic_smallMap each time new data comes from game
 */
void Singleton ::set_generic_smallMap(string buf_to_value, int sim_index) {
    string::size_type sz;
    float value = stof(buf_to_value, &sz);
    if (sim_index == 1) {
        this->AllVarsFromXML["/instrumentation/airspeed-indicator/indicated-speed-kt"].set_value(value);
    }
    if (sim_index == 2) {
        this->AllVarsFromXML["/sim/time/warp"].set_value(value);
    }
    if (sim_index == 3) {
        this->AllVarsFromXML["/controls/switches/magnetos"].set_value(value);
    }
    if (sim_index == 4) {
        this->AllVarsFromXML["/instrumentation/heading-indicator/offset-deg"].set_value(value);
    }
    if (sim_index == 5) {
        this->AllVarsFromXML["/instrumentation/altimeter/indicated-altitude-ft"].set_value(value);
    }
    if (sim_index == 6) {
        this->AllVarsFromXML["/instrumentation/altimeter/pressure-alt-ft"].set_value(value);
    }
    if (sim_index == 7) {
        this->AllVarsFromXML["/instrumentation/attitude-indicator/indicated-pitch-deg"].set_value(value);
    }
    if (sim_index == 8) {
        this->AllVarsFromXML["/instrumentation/attitude-indicator/indicated-roll-deg"].set_value(value);
    }
    if (sim_index == 9) {
        this->AllVarsFromXML["/instrumentation/attitude-indicator/internal-pitch-deg"].set_value(value);
    }
    if (sim_index == 10) {
        this->AllVarsFromXML["/instrumentation/attitude-indicator/internal-roll-deg"].set_value(value);
    }
    if (sim_index == 11) {
        this->AllVarsFromXML["/instrumentation/encoder/indicated-altitude-ft"].set_value(value);
    }
    if (sim_index == 12) {
        this->AllVarsFromXML["/instrumentation/encoder/pressure-alt-ft"].set_value(value);
    }
    if (sim_index == 13) {
        this->AllVarsFromXML["/instrumentation/gps/indicated-altitude-ft"].set_value(value);
    }
    if (sim_index == 14) {
        this->AllVarsFromXML["/instrumentation/gps/indicated-ground-speed-kt"].set_value(value);
    }
    if (sim_index == 15) {
        this->AllVarsFromXML["/instrumentation/gps/indicated-vertical-speed"].set_value(value);
    }
    if (sim_index == 16) {
        this->AllVarsFromXML["/instrumentation/heading-indicator/indicated-heading-deg"].set_value(value);
    }
    if (sim_index == 17) {
        this->AllVarsFromXML["/instrumentation/magnetic-compass/indicated-heading-deg"].set_value(value);
    }
    if (sim_index == 18) {
        this->AllVarsFromXML["/instrumentation/slip-skid-ball/indicated-slip-skid"].set_value(value);
    }
    if (sim_index == 19) {
        this->AllVarsFromXML["/instrumentation/turn-indicator/indicated-turn-rate"].set_value(value);
    }
    if (sim_index == 20) {
        this->AllVarsFromXML["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"].set_value(value);
    }
    if (sim_index == 21) {
        this->AllVarsFromXML["/controls/flight/aileron"].set_value(value);
    }
    if (sim_index == 22) {
        this->AllVarsFromXML["/controls/flight/elevator"].set_value(value);
    }
    if (sim_index == 23) {
        this->AllVarsFromXML["/controls/flight/rudder"].set_value(value);
    }
    if (sim_index == 24) {
        this->AllVarsFromXML["/controls/flight/flaps"].set_value(value);
    }
    if (sim_index == 25) {
        this->AllVarsFromXML["/controls/engines/engine/throttle"].set_value(value);
    }
    if (sim_index == 26) {
        this->AllVarsFromXML["/controls/engines/current-engine/throttle"].set_value(value);
    }
    if (sim_index == 27) {
        this->AllVarsFromXML["/controls/switches/master-avionics"].set_value(value);
    }
    if (sim_index == 28) {
        this->AllVarsFromXML["/controls/switches/starter"].set_value(value);
    }
    if (sim_index == 29) {
        this->AllVarsFromXML["/engines/active-engine/auto-start"].set_value(value);
    }
    if (sim_index == 30) {
        this->AllVarsFromXML["/controls/flight/speedbrake"].set_value(value);
    }
    if (sim_index == 31) {
        this->AllVarsFromXML["/sim/model/c172p/brake-parking"].set_value(value);
    }
    if (sim_index == 32) {
        this->AllVarsFromXML["/controls/engines/engine/primer"].set_value(value);
    }
    if (sim_index == 33) {
        this->AllVarsFromXML["/controls/engines/current-engine/mixture"].set_value(value);
    }
    if (sim_index == 34) {
        this->AllVarsFromXML["/controls/switches/master-bat"].set_value(value);
    }
    if (sim_index == 35) {
        this->AllVarsFromXML["/controls/switches/master-alt"].set_value(value);
    }
    if (sim_index == 36) {
        this->AllVarsFromXML["/engines/engine/rpm"].set_value(value);
    }
}
map<string,ValueAndNameObject>& Singleton::getAllVarsFromXMLMMap() {
  return this->AllVarsFromXML;
}
void Singleton::InitializationofAllVarsFromXML() {
  map<string, float>::iterator it;
  setMutexLocked();
  for (const auto& kv : generic_smallMap) {
    AllVarsFromXML[kv.first].set_value(kv.second);
      if ( getsymbolTableFromServerMap().find(AllVarsFromXML[kv.first].get_name()) == getsymbolTableToServerMap().end()) {

      } else {
        getsymbolTableFromServerMap()[AllVarsFromXML[kv.first].get_name()]->set_value(kv.second);
      }
    }
  setMutexUnlocked();
}
/*
 * public method to lock the mutex
 */
void Singleton::setMutexLocked() {
  this->Mutex.lock();
}
/*
 * public method to unlock the mutex
 */
void Singleton::setMutexUnlocked() {
  this->Mutex.unlock();
}
void Singleton::deleteAllElementsinOrdersToArrayVector() {
  while(!getArrayOfOrdersToServer().empty()) {
    getArrayOfOrdersToServer().erase(getArrayOfOrdersToServer().begin());
  }
}
void Singleton::updateFromSimulatorTable() {
  setMutexLocked();
  for (auto it=symbolTableFromServer.begin();it!=symbolTableFromServer.end(); ++it) {
    it->second->set_value(AllVarsFromXML[it->second->get_sim()].get_value());
  }
  setMutexUnlocked();
}
