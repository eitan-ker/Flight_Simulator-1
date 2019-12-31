#ifndef FLIGHTSIMULATOR__COMMAND_H_
#define FLIGHTSIMULATOR__COMMAND_H_
#include <string>
#include "Var_Data.h"
#include <vector>

enum WHiCHMAP { ISNTINMAPS, ISINFROMSERVERMAP, ISINTOSERVERMAP }; //help to find where the variable to update its value/place into according to value assigned to it in fly.txt
using namespace std;
float findValueOfVarInMap(string var); //give the name key and return its value
float getFloatValuefromString(const vector<string> &str, int i);//helper function to calculate value of complex string with strings instead of number and return the float value result
void buildVectorFromString(vector<string>& vec, string& str);//helper function to calculate value of complex string with strings instead of number and return the float value result
float calculateMathExpression(string str);//main function to calculate complex expression, uses "buildVectorFromString" and "getFloatValuefromString" functions
void gothroughloop(int startofloop, int endofloop); //function to iterate through statement in while\if curly braces from fly.txt
int WhichMapToPutVariable(string& str);//function to analyze to which map to habit the variable from fly.txt
class Command {
 public:
  virtual int execute(vector<string> &str, int i) = 0;
  virtual ~Command(){}
};

class ConnectCommand : public Command {
  virtual int execute(vector<string> &str, int i);
  virtual ~ConnectCommand(){};
  void executeConnect(int port);
};

class OpenServerCommand: public Command {
  virtual int execute(vector<string> &str, int i);
  virtual ~OpenServerCommand(){};
  void executeServer(int port);
};

class ConditionalParser: public Command {
 public:
  virtual int execute(vector<string> &str, int i) = 0;
  int checkCondition(float operand1, float operand2, string op) {
    if (op.compare("<")) {
      if(operand1<operand2) {
        return 1;
      }
      else {
        return 0;
      }
    }
    if (op.compare("==")) {
      if(operand1==operand2) {
        return 1;
      }
      else {
        return 0;
      }
    }
    if (op.compare(">")) {
      if(operand1>=operand2) {
        return 1;
      }
      else {
        return 0;
      }
    }
    if (op.compare("<=")) {
      if(operand1<=operand2) {
        return 1;
      }
      else {
        return 0;
      }
    }
    if (op.compare(">=")) {
      if(operand1>=operand2) {
        return 1;
      }
      else {
        return 0;
      }
    }
  }
  virtual ~ConditionalParser(){};
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
class SleepCommand : public Command {
 public:
  virtual int execute(vector<string> &str, int i);
  virtual ~SleepCommand(){};
};

class WhileCommand : public ConditionalParser {
 public:
  virtual int execute(vector<string> &str, int i);
  virtual ~WhileCommand(){};
};

class PrintCommand : public Command {
 public:
  virtual int execute(vector<string> &str, int i);
  virtual ~PrintCommand(){};
};
class IfCommand : public ConditionalParser {
 public:
  virtual int execute(vector<string> &str, int i);
  virtual ~IfCommand(){};
};


#endif //FLIGHTSIMULATOR__COMMAND_H_