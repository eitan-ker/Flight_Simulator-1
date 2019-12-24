#ifndef FLIGHTSIMULATOR__COMMAND_H_
#define FLIGHTSIMULATOR__COMMAND_H_
#include <string>
#include "Var_Data.h"
#include <vector>

using namespace std;

class Command {
 public:
  virtual int execute(vector<string> &str, int i) = 0;
  virtual ~Command(){}
};

class ConnectCommand : public Command {
  virtual int execute(vector<string> &str, int i);
  virtual ~ConnectCommand(){};
};

class OpenServerCommand: public Command {
  virtual int execute(vector<string> &str, int i);
  virtual ~OpenServerCommand(){};
};

class DefineVarCommand : public Command {
 public:
  virtual int execute(vector<string> &str, int i);
  void addTosymbolTable(string key, Var_Data value);
  virtual ~DefineVarCommand(){};
};

class SimCommand : public Command {
 public:
  virtual int execute(vector<string> &str, int i);
  virtual ~SimCommand(){};
};

class setToClientCommand : public Command {
 public:
  virtual int execute(vector<string> &str, int i);
  ~setToClientCommand(){};
};

class setToSimulatorCommand : public Command {
 public:
  virtual int execute(vector<string> &str, int i);
  virtual ~setToSimulatorCommand(){};
};

class assignCommand : public Command {
 public:
  virtual int execute(vector<string> &str, int i);
  virtual ~assignCommand(){};
};


#endif //FLIGHTSIMULATOR__COMMAND_H_