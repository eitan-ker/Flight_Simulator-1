#ifndef FLIGHTSIMULATOR__COMMAND_H_
#define FLIGHTSIMULATOR__COMMAND_H_
class Command {
 public:
  virtual int execute(string str) = 0;
  virtual ~Command();
};

#endif //FLIGHTSIMULATOR__COMMAND_H_
