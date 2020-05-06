link to git repo :https://github.com/menimen/Flight_Simulator
# Flight_Simulator
project given in c++ in "Advenced_programming" course in Sophmore year. 
the project is about learning how to connect to flight simulator application as a client and open local host server so that the simulator can connect to local host in order to exchange data between the host and the simulator and practice working in multithreading environment so that eventually with the right data combined togheter, the plane will fly.
the project is split to milesstones:
I. build a lexer to parse data from text and send the data to the simulator

## **Getting Started**
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### **Prerequisites**

What things you need to install the software and how to install them
* flightgear app to linux
* telnet for linux

#### **about our work**

Commands .cpp
in this file we wrote all logic related on how each command will act on the DB.

Singleton .cpp
in this file we wrote all logic to how to interact with DB elements and how to update them. the singleton has only one static instance and no possibility to create another instance. inspired by Singletone Design patten.

Client.cpp
in this file we wrote all logic related to connect to simulator as a client and send "set" commands

Server.cpp
in this file we wrote all logic on how to open localhost connection for the simulator to connect to the localhost.


ex1.cpp
this file is the file which consists the logic of calculating complex expressions. took the file from exercise 1 we got in class and upgraded it a bit to fit to our mission. the calculation proccess is based on shunting yard algorithm

### **Built With**
Clion IDE

#### **Authors**

Eitan kerzhner, Meni Ashurov

## **license**
This project is licensed under the Bar-Ilan University license
## **Acknowledgments**
stackoverflow which inspired where we encountered a problem in code and used code from there


