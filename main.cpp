// Copyright 2019 Meni Ashurov
#include <thread>
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
#include "Singleton.h"
#include "Command.h"

using namespace std;

void check_line(string &line, vector<string> &str_array);

void AddToVector(const char* start, const char *string1, vector<std::__cxx11::string>& vector);
void lexer(const char *file_path, vector<string> &str_array);

void parser(vector<string> &str_array);

int main(int argc, char *argv[]);
void check_line(string &line, vector<string> &str_array) {
  vector<string> ops ={"<",">","!"};
  const char *token = &(line[0]);
  const char *start = token;
  const char *temp = token;
  int open_parenthesis = 0, after_equal_sign = 0;
  string c;
  regex r1("[0-9]*[.][ ]");
  if (*token == '/') { //encountered comment
    token++;
    if (*token == '/') {
      return;
    }
  }
  while(*token == '\t' || *token == ' ') {
    token++;
  }
  start = token;
  while (*token != '\0' && *token != '\n' && *token != '\r') { //start iterating over the line char by chaar
    if (*token == '\t') {
      token++;
      start = token;
    }
    if (*token == '(' && after_equal_sign == 0) {
      int skip_colons = 0;
      AddToVector(start, token, str_array);
      token++;
      start = token;
      open_parenthesis++;
      while (open_parenthesis > 0) {
        if (*token == ',') {
          AddToVector(start, token, str_array);
          token++;
          start = token;
        }
        if (*token == '(') {
          open_parenthesis++;
        } else if (*token == ')') {
          open_parenthesis--;
        }
        token++;
      }
      string r(start, token);
      r = r.substr(0, r.size() - 1);
      const char *s = &r[0];
      const char *t = &r[r.size()];
      AddToVector(s, t, str_array);
      start = token;
    }
    if (*token == '{' || *token == '}') {
      AddToVector(start, token, str_array);
      if (*token == '{') {
        str_array.emplace(str_array.end(), "{");
      } else {
        str_array.emplace(str_array.end(), "}");
      }
      token++;
      start = token;
    }
    if (*token == ' ' && after_equal_sign == 0) {
      if (start != token) {
        AddToVector(start,token,str_array);
      }
      token++;
      start = token;
    }
    if (*token == '=') {
      if (start != token) {
        string c(start,token);
        if (std::find(ops.begin(), ops.end(), c) != ops.end()) {
          c += *token;
          str_array.emplace(str_array.end(), c);
          token++;
        } else if (c!= " ") {
          AddToVector(start,token,str_array);
        }
      }
      if(*token == ' ') {
        token++;
      }
      temp=token;
      temp++;
      if(*temp == '=' && *token == '=') {
        str_array.emplace(str_array.end(), "==");
        token++;
        token++;
      } else if (*temp=='=' && *token!='=') {
        str_array.emplace(str_array.end(), "=");
        token++;
        token++;
      } else if (*token == '=') {
        str_array.emplace(str_array.end(), "=");
        token++;
        if(*token == ' ') {
          token++;
        }
        start = token;
      }
      if(*token == ' ') {
        token++;
      }
      after_equal_sign++;
      start = token;
    }
    if (*token != '\0') {
      token++;
    }
  }
  if (start != token && *start != '\0') {
    AddToVector(start,token,str_array);
  }
}
void AddToVector(const char *start, const char *token, vector<std::__cxx11::string>& str_array) {
  if(start!=token) {
    string c(start, token);
    str_array.emplace(str_array.end(), c);
  }
}

void lexer(const char *file_path, vector<string> &str_array) {
    string line;
    try {
        ifstream my_file(file_path,ios::in);
        if (my_file.is_open()) {
            while (getline(my_file, line)) {
                check_line(line, str_array);
                line="";
            }
            my_file.close();
        }
    } catch (const char *e) {
        cout << e << endl;
    }
}

void parser(vector<string> &str_array) {
  //   thread tread1;
  unsigned int i = 0;
  Singleton *sin = sin->getInstance();
  while (i < str_array.size()) {
    // this map needs to be initialized already
    Command *c = sin->getCommandMap().find(str_array.at(i))->second;
    if (sin->getCommandMap().find(str_array.at(i)) == sin->getCommandMap().end()) {
      i++;
    } else {
      i += (*c).execute(str_array, i);
    }
  }
}

int main(int argc, char *argv[]) {
    int a = argc;
    if(a==0) {
      cout << "no parameters were given";
    }
    Singleton *database = database->getInstance();
    lexer(argv[1], database->getVector());
    parser(database->getVector());
  //double val = calculateMathExpression("(h0 - heading)/80");
    return 0;
}
