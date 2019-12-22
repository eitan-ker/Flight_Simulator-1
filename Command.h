#ifndef FLIGHTSIMULATOR__COMMAND_H_
#define FLIGHTSIMULATOR__COMMAND_H_
#include <string>

using namespace std;

class Command {
public:
    virtual int execute(string str) = 0;
    virtual ~Command()= default;
};

class ConnectCommand : public Command {
    int execute(string str) override;
    ~ConnectCommand() override;
};

class OpenServerCommand: public Command {
    int execute(string str) override;
    ~OpenServerCommand() override;
};

#endif //FLIGHTSIMULATOR__COMMAND_H_