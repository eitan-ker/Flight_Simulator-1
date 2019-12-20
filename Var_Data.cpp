class Var_Data {

 private:
  double _value;
  string _sim;

 public:
  Var_Data(double value, string sim) :
    _value(value), _sim(sim) {}
  string get_sim() {
    return this->_sim;
  }
  void set_sim(string sim) {
    this->_sim = sim;
  }
  double get_value() {
    return this->_value;
  }
  void set_value(double value) {
    this->_value = value;
  }

  ~Var_Data(){}
};
