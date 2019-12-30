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

map<string, Command *>& Singleton::getCommandMap() {
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

void Singleton ::set_generic_smallMap(string buf_to_value, int sim_index) {
    string::size_type sz;
    float value = stof(buf_to_value, &sz);
    if (sim_index == 1) {
        this->generic_smallMap["/instrumentation/airspeed-indicator/indicated-speed-kt"] = value;
    }
    if (sim_index == 2) {
        this->generic_smallMap["/sim/time/warp"] = value;
    }
    if (sim_index == 3) {
        this->generic_smallMap["/controls/switches/magnetos"] = value;
    }
    if (sim_index == 4) {
        this->generic_smallMap["/instrumentation/heading-indicator/offset-deg"] = value;
    }
    if (sim_index == 5) {
        this->generic_smallMap["/instrumentation/altimeter/indicated-altitude-ft"] = value;
    }
    if (sim_index == 6) {
        this->generic_smallMap["/instrumentation/altimeter/pressure-alt-ft"] = value;
    }
    if (sim_index == 7) {
        this->generic_smallMap["/instrumentation/attitude-indicator/indicated-pitch-deg"] = value;
    }
    if (sim_index == 8) {
        this->generic_smallMap["/instrumentation/attitude-indicator/indicated-roll-deg"] = value;
    }
    if (sim_index == 9) {
        this->generic_smallMap["/instrumentation/attitude-indicator/internal-pitch-deg"] = value;
    }
    if (sim_index == 10) {
        this->generic_smallMap["/instrumentation/attitude-indicator/internal-roll-deg"] = value;
    }
    if (sim_index == 11) {
        this->generic_smallMap["/instrumentation/encoder/indicated-altitude-ft"] = value;
    }
    if (sim_index == 12) {
        this->generic_smallMap["/instrumentation/encoder/pressure-alt-ft"] = value;
    }
    if (sim_index == 13) {
        this->generic_smallMap["/instrumentation/gps/indicated-altitude-ft"] = value;
    }
    if (sim_index == 14) {
        this->generic_smallMap["/instrumentation/gps/indicated-ground-speed-kt"] = value;
    }
    if (sim_index == 15) {
        this->generic_smallMap["/instrumentation/gps/indicated-vertical-speed"] = value;
    }
    if (sim_index == 16) {
        this->generic_smallMap["/instrumentation/heading-indicator/indicated-heading-deg"] = value;
    }
    if (sim_index == 17) {
        this->generic_smallMap["/instrumentation/magnetic-compass/indicated-heading-deg"] = value;
    }
    if (sim_index == 18) {
        this->generic_smallMap["/instrumentation/slip-skid-ball/indicated-slip-skid"] = value;
    }
    if (sim_index == 19) {
        this->generic_smallMap["/instrumentation/turn-indicator/indicated-turn-rate"] = value;
    }
    if (sim_index == 20) {
        this->generic_smallMap["/instrumentation/vertical-speed-indicator/indicated-speed-fpm"] = value;
    }
    if (sim_index == 21) {
        this->generic_smallMap["/controls/flight/aileron"] = value;
    }
    if (sim_index == 22) {
        this->generic_smallMap["/controls/flight/elevator"] = value;
    }
    if (sim_index == 23) {
        this->generic_smallMap["/controls/flight/rudder"] = value;
    }
    if (sim_index == 24) {
        this->generic_smallMap["/controls/flight/flaps"] = value;
    }
    if (sim_index == 25) {
        this->generic_smallMap["/controls/engines/engine/throttle"] = value;
    }
    if (sim_index == 26) {
        this->generic_smallMap["/controls/engines/current-engine/throttle"] = value;
    }
    if (sim_index == 27) {
        this->generic_smallMap["/controls/switches/master-avionics"] = value;
    }
    if (sim_index == 28) {
        this->generic_smallMap["/controls/switches/starter"] = value;
    }
    if (sim_index == 29) {
        this->generic_smallMap["/engines/active-engine/auto-start"] = value;
    }
    if (sim_index == 30) {
        this->generic_smallMap["/controls/flight/speedbrake"] = value;
    }
    if (sim_index == 31) {
        this->generic_smallMap["/sim/model/c172p/brake-parking"] = value;
    }
    if (sim_index == 32) {
        this->generic_smallMap["/controls/engines/engine/primer"] = value;
    }
    if (sim_index == 33) {
        this->generic_smallMap["/controls/engines/current-engine/mixture"] = value;
    }
    if (sim_index == 34) {
        this->generic_smallMap["/controls/switches/master-bat"] = value;
    }
    if (sim_index == 35) {
        this->generic_smallMap["/controls/switches/master-alt"] = value;
    }
    if (sim_index == 36) {
        this->generic_smallMap["/engines/engine/rpm"] = value;
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
    if (getsymbolTableToServerMap().find(AllVarsFromXML[kv.first].get_name()) == getsymbolTableToServerMap().end()) {
      if ( getsymbolTableFromServerMap().find(AllVarsFromXML[kv.first].get_name()) == getsymbolTableToServerMap().end()) {

      } else {
        getsymbolTableFromServerMap()[AllVarsFromXML[kv.first].get_name()]->set_value(kv.second);
      }
    } else {
      getsymbolTableToServerMap()[AllVarsFromXML[kv.first].get_name()]->set_value(kv.second);
    }
  }
  setMutexUnlocked();
}
void Singleton::setMutexLocked() {
  this->Mutex.lock();
}
void Singleton::setMutexUnlocked() {
  this->Mutex.unlock();
}
