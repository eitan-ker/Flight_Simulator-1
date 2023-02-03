# Flight Simulator
A project in C++ given in the "Advanced Programming" course during the Sophomore year. The project is about learning how to connect to a flight simulator application as a client and open a local host server so that the simulator can connect to the local host to exchange data. This helps in practicing working in a multithreading environment to make the plane fly. The project is split into milestones:
1. Build a lexer to parse data from text and send the data to the simulator.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites
- Flightgear app for Linux
- Telnet for Linux

#### About Our Work
- `Commands.cpp` - Contains the logic for each command to act on the database.
- `Singleton.cpp` - Contains the logic to interact with database elements and update them. The singleton has only one static instance, based on the Singleton Design Pattern.
- `Client.cpp` - Contains the logic for connecting to the simulator as a client and sending "set" commands.
- `Server.cpp` - Contains the logic for opening a localhost connection for the simulator to connect to.
- `ex1.cpp` - Contains the logic for calculating complex expressions using the shunting yard algorithm.

### Built With
- Clion IDE

#### Authors
- Eitan Kerzhner
- Meni Ashurov

## License
This project is licensed under the Bar-Ilan University license.

## Acknowledgments
- StackOverflow, which was a source of inspiration when encountering problems in code and used code from there.
