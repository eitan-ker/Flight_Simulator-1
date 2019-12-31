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
#include <arpa/inet.h>
#include "ex1.h"
#include "Client.h"

/*
 * open server command execute function
 */
int OpenServerCommand::execute(vector<string> &str, int i) {

    // if there is a problem with the connection what do we return?
    // if we connect and run the infinit loop how will it return 2 for the next command?

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

    // how will i return 2 to parser for the next command if there is a thread running?
    // works as expected - runs the thread separately and it;s ok. will it always works

    // will open thread to run infinite loop of recieving data from game
    thread ods(&OpenServerCommand::executeServer, this, client_socket);
    ods.detach();
    return 2;
//    close(socketfd); //closing the listening socket
}


void OpenServerCommand::executeServer(int client_socket) {
    Server *server = new Server();
    server->runServer(client_socket);
}

int ConnectCommand::execute(vector<string> &str, int i) {
  Singleton *t = t->getInstance();
  t->getArrayOfOrdersToServer(); ///in this case, the getArrayOfOrdersToServer function will have to wait till the Mutex is unlocked
    string ip_to_connect = str[i + 1];
    const char *token = &(ip_to_connect[0]);
    stringstream strng(str[i + 2]);
    int port = 0;
    strng >> port;

    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket"<<std::endl;
        //return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
    address.sin_port = htons(port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server"<<std::endl;
      //  return -2;
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }

    // thread maker
    thread cc(&ConnectCommand::executeConnect, this, client_socket);
    cc.detach();


    return 3;
}

void ConnectCommand::executeConnect(int client_socket) {
    Client *client = new Client();
    client->runClient(client_socket);
}

int DefineVarCommand::execute(vector<string> &str, int i) {
  int j = 0;
  Singleton* t = t->getInstance(); //get instance of the database first
  t->setMutexLocked();//first of all, lock the DB until the command is finished
  string c = str.at(i+2); //get the sign in var command in fly.txt
  string d = str.at(i+3);//get the sim word from vector
  string var = str.at(i+1); //get the name of the new variable in fly.txt
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
  } else if(c=="->" || c=="<-" ) { //move to relevent command and keep it from there
    j = t->getCommandMap()[d]->execute(str, i+2);
    j+=2;
  }
  t->setMutexUnlocked();
  return j;
}

int SimCommand::execute(vector<string> &str, int i) {
  int j = 0;
  Singleton* t = t->getInstance();//get instance of DB
  string temp = str.at(i+2);//get the string which is the path of sim
  const char* start = &(temp[0]);
  const char* end = &(temp[temp.size()-1]);
  if(*start != '\"' || *end!= '\"') {
    throw "invalid command format";
  }

  temp = temp.substr(1,temp.size()-2);
  string binding = str.at(i);

  if(binding=="->") { //call to setToClientCommand which stores new var in the symbolTableToServer map
    j = t->getCommandMap()[binding]->execute(str,i);
  } else if(binding=="<-") { //call to setToClientCommand which stores new var in the symbolTableFromServer map
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
  Var_Data* temp = new Var_Data{t->getAllVarsFromXMLMMap()[simpath].get_value(),simpath};//create new float,sim object in the heap
  t->getAllVarsFromXMLMMap()[simpath].set_name(str.at(i-1));/*set the name of the variable in the main getAllVarsFromXMLMMap according to given name in fly.txt
  from now on we can access the variable using this name*/
  t->getsymbolTableToServerMap().emplace(str.at(i-1),temp);//insert the new name,(float,sim) object pair to symbolTableToServer map
  return 3;
}
/*
 * helper function to get value of vairable from DB
 */
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
/*
 * print command, find the variable name at the DB and print its value
 */
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
  t->setMutexLocked();//lock the DB while update is in proccess
  float d = calculateMathExpression(str.at(i+1)); //get value from coplex expression
    str_val = to_string(d);//cast value to string
    whichMap=WhichMapToPutVariable(str.at(i-1));//decide in which map in DB to store the new value\variable
  var = str.at(i-1); //name of the new variable in fly.txt
  switch(whichMap) {
    case ISNTINMAPS: {//the variable doesnt exist in the maps yet
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
    case ISINFROMSERVERMAP: { // the variable exists in the symbolTableFromServer map
      t->getsymbolTableFromServerMap()[var]->set_value(d);//update the variable pair in map
      str_val = t->getsymbolTableFromServerMap()[var]->get_sim();//update the variable pair in map
      t->getAllVarsFromXMLMMap()[str_val].set_value(d);//update the variable pair in AllVarsFromXMLMMap
    }
      break;
    case ISINTOSERVERMAP: {// the variable exists in the symbolTableToServer map
      //send order to game to update the value of the variable according to its sim stored in the DB
      t->getArrayOfOrdersToServer().emplace(t->getArrayOfOrdersToServer().end(), "set " +
          t->getsymbolTableToServerMap()[str.at(i - 1)]->get_sim().substr(1,t->getsymbolTableToServerMap()[str.at(i - 1)]->get_sim().size() - 1) + " "+ str_val+"\r\n" );
      t->getsymbolTableToServerMap()[str.at(i - 1)]->set_value(d);//update the variable pair in map
      string sim_path = t->getsymbolTableToServerMap()[str.at(i - 1)]->get_sim();//update the variable pair in map
      t->getAllVarsFromXMLMMap()[sim_path].set_value(d);//update the variable pair in AllVarsFromXMLMMap
    }
      break;
    default:
      break;
  }
  t->setMutexUnlocked();//finished working on DB, unlock Mutex
  return 2;
}
int SleepCommand::execute(vector<string> &str, int i) {
  int sleeptime=0;
  try {
    sleeptime = stoi(str.at(i + 1));
    std::this_thread::sleep_for(std::chrono::milliseconds(sleeptime));
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
  while(checkCondition(operand1,operand2,str.at(i+2)) == 1) {
    gothroughloop(j, j + count);
    operand1 = getFloatValuefromString(sin->getVector(),i+1);
    operand2 = getFloatValuefromString(sin->getVector(),i+3);
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

  if(checkCondition(operand1,operand2,str.at(i+2)) == 1) {
    gothroughloop(j, j + count);
  }
  return (j+count+1)-i;
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
/*
 * create vector which consists the string given as a parameter seperated according to regex criteria
 */
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
    } else {//encoutered operator
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
/*
 * helper function to tell where in the DB i can find\update variable's value
 */
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

