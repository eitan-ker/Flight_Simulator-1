#ifndef MAIN
#define MAIN
#include <fstream>
#include <map>
#include <iterator>
#include <string>
#include <iostream>
#include <list>
#include <utility>
#include <fstream>
#include <sstream>
using namespace std;

void check_line(string &line, vector<string> &str_array);
void lexer(const char* file_path, vector<string> &str_array);
void parser(char *str_array[]);
int main(int argc, char* argv[]);
#endif
