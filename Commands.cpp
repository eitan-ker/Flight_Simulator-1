//file to write all Commands implementation
#include "Command.h"
#include "Singleton.h"
#include "Server.h"
#include <string>
#include <thread>
#include <float.h>

double findValueOfVarInMap(string var);
void SleepFunc(int x);
int OpenServerCommand::execute(vector<string> &str, int i) {
    thread *ods = new thread(&OpenServerCommand::executeServer, this, 2);
    ods->detach();

    //
    executeServer(2);
    for (int i = 0; i < 2; i++) {
        cout << "thread OSD runs 2 times" << endl;
    }
    return 2;
}

void OpenServerCommand::executeServer(int port) {
    Server *server = new Server();
    server->runServer(port);
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
  if(c=="=") {
    j = t->getCommandMap()[c]->execute(str, i);
  } else if(c=="->" || c=="<-" ) {
    j = t->getCommandMap()[d]->execute(str, i+2);
    j+=2;
  }
  return j;
  }

int SimCommand::execute(vector<string> &str, int i) {
  int j = i;
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
  Var_Data temp(0,simpath);
  t->getsymbolTableFromServerMap().emplace(str.at(i-1),temp);
  return 3;
}
int setToSimulatorCommand::execute(vector<string> &str, int i) {
  Singleton* t = t->getInstance();
  string simpath = str.at(i+2).substr(1,str.at(i+2).size()-2);
  Var_Data temp(0,simpath);
  t->getsymbolTableToServerMap().emplace(str.at(i-1),temp);
  /*float c = t->getsymbolTableToServerMap()[str.at(i-1)].get_value();
  string temp1 = to_string(c);*/
  return 3;
}
double findValueOfVarInMap(string var) {
  double j = 0;
  Singleton* t = t->getInstance();
  if (t->getsymbolTableToServerMap().find(var) == t->getsymbolTableToServerMap().end()) {
    if (t->getsymbolTableFromServerMap().find(var) == t->getsymbolTableToServerMap().end()) {
      throw "error: variable not found";
    } else {
      j = t->getsymbolTableFromServerMap()[var].get_value();
    }
  } else {
    j = t->getsymbolTableToServerMap()[var].get_value();
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
  Singleton* t = t->getInstance();
  float d = stod(str.at(i+1));
  if ((d > 0 && (d > FLT_MAX || d < FLT_MIN))
      || (d < 0 && (d < -FLT_MAX || d > -FLT_MIN))) {
    str_val = to_string(findValueOfVarInMap(str.at(i+1)));
    t->getArrayOfOrdersToServer().emplace(t->getArrayOfOrdersToServer().end(), "set " + t->getsymbolTableToServerMap()[str.at(i-1)].get_sim() +" "+ str_val + "/n");

  } else {
    if (t->getsymbolTableToServerMap().find(str.at(i-1)) == t->getsymbolTableToServerMap().end()) {
    throw "variable not found";
    } else {
      t->getsymbolTableToServerMap()[str.at(i-1)].set_value(d);
      string floatTostring = to_string(d);
      t->getArrayOfOrdersToServer().emplace(t->getArrayOfOrdersToServer().end(), "set " + t->getsymbolTableToServerMap()[str.at(i-1)].get_sim() +" "+ floatTostring+ "/n");
    }
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
  int j = i,count=0;
  for(; str.at(j)!="{"; j++) {
    j++;
    count++;
  }
  if(count!=3) {
    throw "invalid while command ";
  }
  j+=2;
}
void SleepFunc(int g) {
  Singleton* t = t->getInstance();
  //cout << "encounter sleep command in Fly.txt. sleep for "  << x << " milliseconds" << endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(g));
}