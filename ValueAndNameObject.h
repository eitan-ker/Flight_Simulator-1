//
// Created by meni on 28/12/2019.
//

#ifndef FLIGHTSIMULATOR__VALUEANDNAMEOBJECT_H_
#define FLIGHTSIMULATOR__VALUEANDNAMEOBJECT_H_
//
// Created by meni on 22/12/2019.

#include <string>
using namespace std;
class ValueAndNameObject {

 private:
  float _value;
  string _name;

 public:
  ValueAndNameObject(){};
  ValueAndNameObject(float value, string name) :
      _value(value), _name(name) {};
  ValueAndNameObject(const ValueAndNameObject& deepcopy) {
    this->set_value(deepcopy.get_value());
    this->set_name(deepcopy.get_name());
  }
  string get_name() const {
    return this->_name;
  }
  void set_name(string name) {
    this->_name = name;
  }
  float get_value() const {
    return this->_value;
  }
  void set_value(float value) {
    this->_value = value;
  }

  ~ValueAndNameObject(){}
};

#endif //FLIGHTSIMULATOR__VALUEANDNAMEOBJECT_H_
