#ifndef FLIGHTSIMULATOR__COMMAND_H_
#define FLIGHTSIMULATOR__COMMAND_H_
#include <string>
#include "Var_Data.h"
#include <vector>

using namespace std;

class Command {
 public:
  virtual int execute(string str[]) = 0;
  virtual ~Command()= default;
};

class ConnectCommand : public Command {
  int execute(string str[]) override;
  ~ConnectCommand() override;
};

class OpenServerCommand: public Command {
  int execute(string str[]) override;
  ~OpenServerCommand() override;
};

class DefineVarCommand : public Command {
 public:
  virtual int execute(string str[]);
  void addTosymbolTable(string key, Var_Data value);
  ~DefineVarCommand(){};
};

class SimCommand : public Command {
 public:
  virtual int execute(string str[]);
  virtual ~SimCommand(){};
};

class setToClientCommand : public Command {
 public:
  virtual int execute(string str[]);
  ~setToClientCommand(){};
};

class setToSimulatorCommand : public Command {
 public:
  virtual int execute(string str[]);
  virtual ~setToSimulatorCommand(){};
};

class assignCommand : public Command {
 public:
  virtual int execute(string str[]);
  virtual ~assignCommand(){};
};


#endif //FLIGHTSIMULATOR__COMMAND_H_