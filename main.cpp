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

void lexer(const char *file_path, vector<string> &str_array);

void parser(vector<string> &str_array);

int main(int argc, char *argv[]);

void check_line(string &line, vector<string> &str_array) {
    const char *token = &(line[0]);
    const char *start = token;
    int foundpattern = 0, enterstringtoarray = 0, counter = 0, skipfound_patternflag=0,check_equal_sign=0;
    string c;
    regex r1("[0-9]*[.][ ]");
    if (*token == '/') {
        token++;
        if (*token == '/') {
            return;
        }
    }
    start = token;
    while (*token != '\0' && *token != '\n' && *token != '\r') {
      skipfound_patternflag=0;
        if (*token == '\t') {
            token++;
            start = token;
        }
        if(check_equal_sign==1) {
          check_equal_sign=0;
          start=token;
          while(*token!='\n' && *token!='{' && *token!='}' && *token != '\0' ) {
            token++;
          }
          foundpattern++;
        }
      /*if( *token == '{') {
        start=token;
        token++;
        while(*token !='}') {
          token++;
        }
        string f(start,token);
        for (int i = 0; i < c.length(); ++i) {
          if (c[i] == '\n')
            c[i] = ',';
        }
        str_array.insert(str_array.end(), f);
      }*/
        if( *token == '\"') {
          start=token;
          token++;
          while(*token !='\"') {
            token++;
          }
          skipfound_patternflag=1;
        }
        if (*token == ' '  || *token == '(' || *token == ')' || *token == ',') {
            foundpattern = 1;
        }
        if (foundpattern == 1 && skipfound_patternflag==0) {
            foundpattern = 0;
            enterstringtoarray = 1;
            string key_str(start, token);
            c = key_str;
            if (c.compare("////") != 0 && c.compare("") != 0) {
              if(c == "=" || c=="<=" || c==">=") {
                check_equal_sign=1;
              }
                str_array.insert(str_array.end(), c);
              if(*token!='\0' && *token!='{' && *token!='}') {
                token++;
              }
              if(*token=='{') {
                c = "{";
                str_array.insert(str_array.end(), c);
                token++;
                start=token;
              }
              if(*token=='}') {
                c = "}";
                str_array.insert(str_array.end(), c);
                token++;
                start=token;
              }
                start = token;
            } else {
                return; //encounter comment
            }
        }
        if (enterstringtoarray == 0) {
            token++;
        } else {
            enterstringtoarray = 0;
        }
    }
    string key_str(start, token);
    if (start != token && *start != '\0') {
        c = key_str;
        str_array.insert(str_array.end(), c);
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
    a=0;
  //val = calculateMathExpression("-1.000*80");
    return 0;
}
