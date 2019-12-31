//
// Created by meni on 22/12/2019.
//

#ifndef FLIGHTSIMULATOR__VAR_DATA_H_
#define FLIGHTSIMULATOR__VAR_DATA_H_
#include <string>
using namespace std;
/*
	* class of te object which stores float value and sim path, attach to variable's name in pair
	*
*/
class Var_Data {

private:
    float _value;
    string _sim;

public:
  Var_Data(){};
    Var_Data(float value, string sim) :
            _value(value), _sim(sim) {};
  Var_Data(const Var_Data& deepcopy) {
    this->set_value(deepcopy.get_value());
    this->set_sim(deepcopy.get_sim());
  }
    string get_sim() const {
        return this->_sim;
    }
    void set_sim(string sim) {
        this->_sim = sim;
    }
    float get_value() const {
        return this->_value;
    }
    void set_value(float value) {
        this->_value = value;
    }

    ~Var_Data(){}
};
#endif //FLIGHTSIMULATOR__VAR_DATA_H_