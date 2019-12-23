#ifndef FLIGHTSIMULATOR__COMMAND_H_
#define FLIGHTSIMULATOR__COMMAND_H_
#include <string>
#include "Var_Data.h"

using namespace std;

class Command {
 public:
  virtual int execute(string str) = 0;
  virtual ~Command()= default;
};

class ConnectCommand : public Command {
  int execute(string str) override;
  ~ConnectCommand() override;
};

class OpenServerCommand: public Command {
  int execute(string str) override;
  ~OpenServerCommand() override;
};

class DefineVarCommand : public Command {
 public:
  int execute(string str);
  void addTosymbolTable(string key, Var_Data value);
  ~DefineVarCommand(){};
};

class SimCommand : public Command {
 public:
  int execute(string str);
  ~SimCommand(){};
};

class setToClientCommand : public Command {
 public:
  int execute(string str);
  ~setToClientCommand(){};
};

class setToSimulatorCommand : public Command {
 public:
  int execute(string str);
  ~setToSimulatorCommand(){};
};

class assignCommand : public Command {
 public:
  int execute(string str);
  ~assignCommand(){};
};


#endif //FLIGHTSIMULATOR__COMMAND_H_