// Copyright 2019 Meni Ashurov
#include <fstream>
#include <map>
#include <string>
#include <iostream>
#include <list>
#include <utility>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
using namespace std;

class Command {
  virtual int execute(string str) = 0;
};
class ConnectCommand : Command {
  int execute(string str) {

  }
  ~ConnectCommand();
};
class OpenServerCommand : Command {
int execute(string str) {

}
~OpenServerCommand();
};
class DefineVarCommand : Command {
int execute(string str) {

}
~DefineVarCommand();
};
class Var_Data {

 private:
  double _value;
  string _sim;

 public:
  Var_Data(double value, string sim) :
      _value(value), _sim(sim) {}
      string get_sim() {
        return this->_sim;
      }
      void set_sim(string sim) {
        this->_sim = sim;
      }
  double get_value() {
    return this->_value;
  }
  void set_value(double value) {
    this->_value = value;
  }
  ~Var_Data(){}
};
void check_line(string &line, vector<string> &str_array) {
  const char* token = &(line[0]);
  const char* start = token;;
  int i = 0, passednumberingflag = 0;
  string c;
  regex r1("[1-9]*[.][ ]");
  if (*token == '/') {
    return;
  }
  while (*token != '\0' && passednumberingflag==0) {
    token++;
    if (isalpha(*token) || *token == '}' ) {
      if (!regex_match(start, token, r1)) {
        cout << "illegal line format" << endl;
        return;
      }
      passednumberingflag=1;
    }
  }
  start = token;
  if (*token == '}') {
    return;
  }
  start = token;
  while (*token!='\0' ||  *token!='/') {
    if(*token=="") {
      token++;
    }
    if (*token == '(' || *token == ' ') {
      string key_str(start,token);
      c= key_str;
      str_array.insert(str_array.end(),c);
      token++;
      start=token;
    } else if (*token == ')') {
      string key_str(start,token);
      c= key_str;
      str_array.insert(str_array.end(),c);
      start=token;
    }
    token++;
  }
}
void lexer(const char* file_path, vector<string> &str_array) {
  char *ptr = nullptr;
  string line;
  try {
    ifstream my_file(file_path);
    if (my_file.is_open()) {
      while ( getline (my_file,line) ) {
        check_line(line,str_array);
      }
      my_file.close();
    }
  }catch (const char *e) {
    cout << e << endl;
  }
}
void parser(char *str_array[]) {

}
int main(int argc, char* argv[]) {

  vector<string> str_array;
  lexer(argv[1], str_array);
  return 0;
}

