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
    int foundpattern = 0, enterstringtoarray = 0, skipfound_patternflag=0,check_equal_sign=0;
    string c;
    regex r1("[0-9]*[.][ ]");
    if (*token == '/') { //encountered comment
        token++;
        if (*token == '/') {
            return;
        }
    }
    start = token;
    while (*token != '\0' && *token != '\n' && *token != '\r') { //start iterating over the line char by chaar
      skipfound_patternflag=0; // first of all at each iteration zero the found word flag
        if (*token == '\t') {//encountered tab
            token++;
            start = token;
        }
        if(check_equal_sign==1) {//encountered equal sign at last iteration, now take everything after it and put it as one string
          check_equal_sign=0;
          start=token;
          while(*token!='\n' && *token!='{' && *token!='}' && *token != '\0' ) {
            token++;
          }
          foundpattern++;
        }
        if( *token == '\"') {//encountered comment in the middle of analyzing the string
          start=token;
          token++;
          while(*token !='\"') {
            token++;
          }
          skipfound_patternflag=1; //dont insert this string to the string vector
        }
        if (*token == ' '  || *token == '(' || *token == ')' || *token == ',') { //if i encounter one of these sign, i put everything i gathered until these sign and add to vector
            foundpattern = 1;
        }
        if (foundpattern == 1 && skipfound_patternflag==0) {//i have now a start char and end char and i want to make a string out of them and push to my string vector
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
              if(*token=='{') {//insert curly braces to vector
                c = "{";
                str_array.insert(str_array.end(), c);
                token++;
                start=token;
              }
              if(*token=='}') { //insert curly braces to vector
                c = "}";
                str_array.insert(str_array.end(), c);
                token++;
                start=token;
              }
                start = token;
            } else {
                return;
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
    database->InitializationofAllVarsFromXML();
  //val = calculateMathExpression("-1.000*80");
    return 0;
}
