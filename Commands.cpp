//file to write all Commands implementation
#include "Command.h"
#include "Singleton.h"
#include "Server.h"
#include <string>
#include <thread>
#include <float.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include "ex1.h"
void SleepFunc(int x);

int OpenServerCommand::execute(vector<string> &str, int i) {
    stringstream strng(str[i + 1]);
    int port = 0;
    strng >> port;

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        //   return -1;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(port);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
        // return -2;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
        //    return -3;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *) &address,
                               (socklen_t *) &address);
    if (client_socket == -1) {
        std::cerr << "Error accepting client" << std::endl;
        //  return -4;
    }
    // will open thread to run infinite loop of recieving data from game
    thread ods(&OpenServerCommand::executeServer, this, client_socket);
    ods.detach();
//    close(socketfd); //closing the listening socket
}


void OpenServerCommand::executeServer(int client_socket) {
    Server *server = new Server();
    server->runServer(client_socket);
}

int ConnectCommand::execute(vector<string> &str, int i) {
    for (int i = 0; i < 3; i++) {
        cout << "thread OSD runs 3 times" << endl;
    }
    return 3;
}
int DefineVarCommand::execute(vector<string> &str, int i) {
  int j = 0;
  Singleton* t = t->getInstance();
  string c = str.at(i+2);
  string d = str.at(i+3);
  string var = str.at(i+1);
  if(c=="=") {
    Var_Data* temp = t->getVar_Data(d);
    if (t->getsymbolTableToServerMap().find(d) == t->getsymbolTableToServerMap().end()) {
      if (t->getsymbolTableFromServerMap().find(d) == t->getsymbolTableToServerMap().end()) {
      } else {
        t->getsymbolTableFromServerMap().emplace(var, temp);
      }
    } else {
      t->getsymbolTableToServerMap().emplace(var,temp);
    }
    j+=1;
  } else if(c=="->" || c=="<-" ) {
    j = t->getCommandMap()[d]->execute(str, i+2);
    j+=2;
  }
  return j;
}

int SimCommand::execute(vector<string> &str, int i) {
  int j = 0;
  Singleton* t = t->getInstance();
  string temp = str.at(i+2);
  const char* start = &(temp[0]);
  const char* end = &(temp[temp.size()-1]);
  if(*start != '\"' || *end!= '\"') {
    throw "invalid command format";
  }

  temp = temp.substr(1,temp.size()-2);
  string binding = str.at(i);

  if(binding=="->") {
    j = t->getCommandMap()[binding]->execute(str,i);
  } else if(binding=="<-") {
    j = t->getCommandMap()[binding]->execute(str,i);
  }
  return j;
}
int setToClientCommand::execute(vector<string> &str, int i) {
  Singleton* t = t->getInstance();
  string simpath = str.at(i+2).substr(1,str.at(i+2).size()-2);
  Var_Data* temp = new Var_Data(t->getAllVarsFromXMLMMap()[simpath].get_value(),simpath);
  t->getAllVarsFromXMLMMap()[simpath].set_name(str.at(i-1));
  t->getsymbolTableFromServerMap().emplace(str.at(i-1),temp);
  return 3;
}
int setToSimulatorCommand::execute(vector<string> &str, int i) {
  Singleton* t = t->getInstance();
  string simpath = str.at(i+2).substr(1,str.at(i+2).size()-2);
  Var_Data* temp = new Var_Data{t->getAllVarsFromXMLMMap()[simpath].get_value(),simpath};
  t->getAllVarsFromXMLMMap()[simpath].set_name(str.at(i-1));
  t->getsymbolTableToServerMap().emplace(str.at(i-1),temp);
  return 3;
}
float findValueOfVarInMap(string var) {
  float j = 0;
  Singleton* t = t->getInstance();
  if (t->getsymbolTableToServerMap().find(var) == t->getsymbolTableToServerMap().end()) {
    if (t->getsymbolTableFromServerMap().find(var) == t->getsymbolTableToServerMap().end()) {
      throw "error: variable not found";
    } else {
      j = t->getsymbolTableFromServerMap()[var]->get_value();
    }
  } else {
    j = t->getsymbolTableToServerMap()[var]->get_value();
  }
  return j;
}
int PrintCommand::execute(vector<string> &str, int i) {
  string temp = str.at(i+1);
  string str_val="";
  const char* start = &(temp[0]);
  Singleton* t = t->getInstance();
  const char* end = &(temp[temp.size()-1]);
  if(*start == '\"' && *end== '\"') { //print the exp in quotation marks
    temp = temp.substr(1,temp.size()-2);
    cout << temp << endl;
  } else { //print the variable's value from map
   str_val = to_string(findValueOfVarInMap(str.at(i+1)));
    cout << str_val <<endl;
  }
  return 2;
}
int assignCommand::execute(vector<string> &str, int i) {
  string str_val= "";
  string var="";
  int notavariable = 0;
  Var_Data *ptr = nullptr;
  int whichMap=0;
  Singleton* t = t->getInstance();
  float d = calculateMathExpression(str.at(i+1));
    str_val = to_string(d);
    whichMap=WhichMapToPutVariable(str.at(i-1));
  var = str.at(i-1);
  switch(whichMap) {
    case ISNTINMAPS: {
      if (t->getsymbolTableToServerMap().find(str.at(i + 1)) == t->getsymbolTableToServerMap().end()) {
        notavariable = 1;
        if (t->getsymbolTableFromServerMap().find(str.at(i + 1)) == t->getsymbolTableToServerMap().end()) {
          notavariable = 1;
        } else {
          notavariable = 0;
        }
      } else {
        notavariable = 0;
      }
      if(notavariable==0) {
        t->getsymbolTableFromServerMap().emplace(var, (t->getVar_Data(str.at(i + 1))));
      }
    }
      break;
    case ISINFROMSERVERMAP: {
      t->getsymbolTableFromServerMap()[var]->set_value(d);
      str_val = t->getsymbolTableFromServerMap()[var]->get_sim();
      t->getAllVarsFromXMLMMap()[str_val].set_value(d);
    }
      break;
    case ISINTOSERVERMAP: {
      t->getArrayOfOrdersToServer().emplace(t->getArrayOfOrdersToServer().end(), "set " +
          t->getsymbolTableToServerMap()[str.at(i - 1)]->get_sim().substr(1,t->getsymbolTableToServerMap()[str.at(i - 1)]->get_sim().size() - 1) + " "+ str_val + "\r\n");
      t->getsymbolTableToServerMap()[str.at(i - 1)]->set_value(d);
      string sim_path = t->getsymbolTableToServerMap()[str.at(i - 1)]->get_sim();
      t->getAllVarsFromXMLMMap()[sim_path].set_value(d);
    }
      break;
    default:
      break;
  }
  return 2;
}
int SleepCommand::execute(vector<string> &str, int i) {
  int sleeptime=0;
  try {
    sleeptime = stoi(str.at(i + 1));
    std::thread thread1(SleepFunc,sleeptime);
    thread1.join();
  }
  catch(...) {
    throw "there was a problem with given integer to Sleep command";
  }
  return 2;
}
int WhileCommand::execute(vector<string> &str, int i) {
  Singleton* sin = sin->getInstance();
  int j = i,count=0;
  float operand1,operand2;
  for(; str.at(j)!="{"; j++) {
    count++;
  }
  if(count!=4) {
    throw "invalid if command ";
  }
  j+=1;// now i want to count how many strings i have in cury braces
  count=0;
  for(;str.at(j+count)!="}";) {
    count++;
  }
  operand1 = getFloatValuefromString(sin->getVector(),i+1);
  operand2 = getFloatValuefromString(sin->getVector(),i+3);

  if(str.at(i+2) == ">") {
    while (operand1 > operand2) {
      gothroughloop(j,j+count);
      operand1 = getFloatValuefromString(sin->getVector(),i+1);
      operand2 = getFloatValuefromString(sin->getVector(),i+3);
    }
  } else if(str.at(i+2) == "<") {
    while (operand1 < operand2) {
      gothroughloop(j,j+count);
      operand1 = getFloatValuefromString(sin->getVector(),i+1);
      operand2 = getFloatValuefromString(sin->getVector(),i+3);
    }
  } else if(str.at(i+2) == ">=") {
    while (operand1 >= operand2) {
      gothroughloop(j,j+count);
      operand1 = getFloatValuefromString(sin->getVector(),i+1);
      operand2 = getFloatValuefromString(sin->getVector(),i+3);
    }
  } else if(str.at(i+2) == "<=") {
    while (operand1 <= operand2) {
      gothroughloop(j,j+count);
      operand1 = getFloatValuefromString(sin->getVector(),i+1);
      operand2 = getFloatValuefromString(sin->getVector(),i+3);
    }
  } else if(str.at(i+2) == "==") {
    while (operand1 == operand2) {
      gothroughloop(j,j+count);
      operand1 = getFloatValuefromString(sin->getVector(),i+1);
      operand2 = getFloatValuefromString(sin->getVector(),i+3);
    }
  } else if(str.at(i+2) == "!=") {
    while (operand1 != operand2) {
      gothroughloop(j,j+count);
      operand1 = getFloatValuefromString(sin->getVector(),i+1);
      operand2 = getFloatValuefromString(sin->getVector(),i+3);
    }
  } else {
    throw "math operator invalid";
  }

  return (j+count+1)-i;
}
int IfCommand::execute(vector<string> &str, int i) {
  Singleton* sin = sin->getInstance();
  int j = i,count=0;
  float operand1,operand2;
  for(; str.at(j)!="{"; j++) {
    count++;
  }
  if(count!=4) {
    throw "invalid if command ";
  }
  j+=1;// now i want to count how many strings i have in cury braces
  count=0;
  for(;str.at(j+count)!="}";) {
    count++;
  }
  operand1 = getFloatValuefromString(sin->getVector(),i+1);
  operand2 = getFloatValuefromString(sin->getVector(),i+3);

  if(str.at(i+2) == ">") {
    if (operand1 > operand2) {
      gothroughloop(j,j+count);
    }
  } else if(str.at(i+2) == "<") {
    if (operand1 < operand2) {
      gothroughloop(j,j+count);
    }
  } else if(str.at(i+2) == ">=") {
    if (operand1 >= operand2) {
      gothroughloop(j,j+count);
    }
  } else if(str.at(i+2) == "<=") {
    if (operand1 <= operand2) {
      gothroughloop(j,j+count);
    }

  } else if(str.at(i+2) == "==") {
    if (operand1 == operand2) {
      gothroughloop(j,j+count);
    }
  } else if(str.at(i+2) == "!=") {
    if(operand1!=operand2) {
      gothroughloop(j, j + count);
    }
  } else {
    throw "math operator invalid";
  }

  return (j+count+1)-i;
}
void SleepFunc(int g) {
  Singleton* t = t->getInstance();
  //cout << "encounter sleep command in Fly.txt. sleep for "  << x << " milliseconds" << endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(g));
}
void gothroughloop(int startofloop, int endofloop) { //help to run commands in curky brackets in if\while statement
  Singleton *sin = sin->getInstance();
  while(startofloop<endofloop) {
    Command *c = sin->getCommandMap().find(sin->getVector().at(startofloop))->second;
    if (sin->getCommandMap().find(sin->getVector().at(startofloop)) == sin->getCommandMap().end()) {
      startofloop++;
    } else {
      startofloop += (*c).execute(sin->getVector(), startofloop);
    }
  }
}
float getFloatValuefromString(const vector<string> &str, int i) { //get value from string wheter variable or float value
  float d=0;
  regex r2("^(-?)(0|([1-9][0-9]*))(\\\\.[0-9]+)?$");
  const char* token=&str.at(i)[0];
  const char *start = token;
  while(*token!='\0' && *token!=' ') {
    token++;
  }
  string c(start,token);
  if (regex_match(start, token, r2)) {
    d = stof(str.at(i));
  } else {
    d = findValueOfVarInMap(str.at(i));
  }
  return d;
}
float calculateMathExpression(string str) {//calculate complex math expression in string format
  Interpreter* i2;
  string final_expression="";
  regex r2("^[-+]?[0-9]*\\.?[0-9]+$");
  const char* token=&final_expression[0];
  const char *start = token;
  float result=0,d=0;
  Expression* e5 = nullptr;
  vector<string> Expressions_array;
  if(str[0]=='\"') {
    str = str.substr(1,str.size()-2);
  }
  buildVectorFromString(Expressions_array,str);
  for (const auto &piece : Expressions_array) final_expression += piece;
  token = &final_expression[0];
  start = token;
  while(*token!='\0' && *token!=' ') {
    token++;
  }
  string m(start,token);
  if (regex_match(start, token, r2)) {
   d = stof(final_expression);
    result = d;
  } else {
    i2 = new Interpreter();
    e5 = i2->interpret(final_expression);
    result = e5->calculate();
    delete i2;
    i2 = nullptr;
  }
  return result;
}
void buildVectorFromString(vector<string>& vec, string& str) {
  float value = 0;
  vector<string> array_of_opearators  {"-","+","*","/","(",")"};
  vector<string>::iterator it;
  const char* token = &str[0];
  const char* start = &str[0];
  regex r1("^[a-zA-Z_$][a-zA-Z_$0-9]*$");
  regex r2("[+-]?([0-9]+([.][0-9]*)?)");
  while(*token != '\0' && *token != '\n' ) {
    if(*token == ' ') {
      token++;
      start = token;
    } else if (isalpha(*token)) {
      while(isalpha(*token) || isdigit(*token)) {
        token++;
      }
      if (!regex_match(start, token, r1)) {
        throw "illegal variable assignment!";
      } else {
        string c(start,token);
        value = findValueOfVarInMap(c);
        c = to_string(value);
        vec.emplace(vec.end(),c);
        start=token;
      }
    } else if (isdigit(*token)) {
      while(isdigit(*token) || *token == '.') {
        token++;
      }
      if (!regex_match(start, token, r2)) {
        throw "illegal variable assignment!";
      } else {
        string c(start,token);
        vec.emplace(vec.end(),c);
        start=token;
      }
    } else {
      string e = "";
      e+=(*token);
      it = find(array_of_opearators.begin(),array_of_opearators.end(),e);
      if(it != array_of_opearators.end()) {
        vec.emplace(vec.end(),e);
        token++;
        start=token;
      } else {
          throw "invalid assignment";
        }
      }
    }
}
int WhichMapToPutVariable(string& str) {
  Singleton* t = t->getInstance();
  int whichMap = 0;
  if (t->getsymbolTableToServerMap().find(str) == t->getsymbolTableToServerMap().end()) {
    if (t->getsymbolTableFromServerMap().find(str) == t->getsymbolTableToServerMap().end()) {
      return 0;
    } else {
      return 1;
    }
  } else {
    return 2;
  }
}

