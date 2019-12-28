// Copyright [2019] Meni

#include "ex1.h"
#include "Expression.h"

BinaryOperator::BinaryOperator(Expression* left, Expression* right) :
    _left(left), _right(right) {}
BinaryOperator::~BinaryOperator() {
  delete _left;
  _left = nullptr;
  delete _right;
  _right = nullptr;
}
UnaryOperator::UnaryOperator(Expression *expression) :_expression(expression) {}
UnaryOperator::~UnaryOperator() {
  delete _expression;
  _expression = nullptr;
}
Plus::Plus(Expression* left, Expression* right) : BinaryOperator(left, right) {}

double Plus::calculate() {
  return _left->calculate() + _right->calculate();
}
Plus::~Plus() {}

Minus::Minus(Expression* left, Expression* right) :
    BinaryOperator(left, right) {}
double Minus:: calculate() {
  return _left->calculate() - _right->calculate();
}
Minus:: ~Minus() {}
Mul::Mul(Expression* left, Expression* right) : BinaryOperator(left, right) {}

double  Mul:: calculate() {
  return _left->calculate() * _right->calculate();
}
Mul:: ~Mul() {}
Div::Div(Expression *left, Expression *right) : BinaryOperator(left, right) {}

double Div::calculate() {
  if (_right->calculate() == 0) {
    throw  "cannot divide by zero";
  } else {
    return _left->calculate() / _right->calculate();
  }
}
Div:: ~Div() {}

UMinus::UMinus(Expression* expression) : UnaryOperator(expression) {}
double UMinus:: calculate() {
  return _expression->calculate() * (-1);
}
UMinus::~UMinus() {}

UPlus::UPlus(Expression* expression) : UnaryOperator(expression) {}
double UPlus::calculate() {
  return _expression->calculate();
}
UPlus::~UPlus() {
}

Variable::Variable(string name, double value) : _name(name), _value(value) {}
Variable& Variable:: operator++() {
  ++this->_value;
  return *this;
}

Variable& Variable::operator--() {
  this->_value = this->_value - 1.0;
  return *this;
}
Variable& Variable::operator+=(double val) {
  this->_value = this->_value + val;
  return *this;
}
Variable& Variable::operator-=(double val) {
  this->_value = this->_value - val;
  return *this;
}
Variable&Variable:: operator++(int) {
  this->_value = this->_value + 1.0;
  return *this;
}
Variable& Variable::operator--(int) {
  this->_value = this->_value - 1.0;
  return *this;
}
double Variable::calculate() {
  return this->_value;
}
Variable::~Variable() {}

Value::Value(double value) : Expression(), _value(value) {}
double Value::calculate() {
  return this->_value;
}
Value::~Value() {}

double Interpreter::performOp(double num1, double num2, string op) {
  if (op == "+") {
    return num1 + num2;
  } else if (op == "-") {
    return num1 - num2;
  } else if (op == "*") {
    return num1 * num2;
  } else {
    if (num1 == 0) {
      throw "cannot divide by zero";
    } else {
      return num2 / num1;
    }
  }
}

int Interpreter::getPrecedence(string op) {
  if (op == "*" || op == "/") {
    return 2;
  } else if (op == "-") {
    return 1;
  } else {
    return 0;
  }
}

int Interpreter::check_parenthesis(const string& str) {
  const char* token = &str[0];
  int trigger_left_paren = 0;
  while (*token != '\0') {
    while (*token == ' ') {
      token++;
    }
    if (*token == ')' && trigger_left_paren == 0) {
      return 0;
    } else if (*token == ')') {
      trigger_left_paren--;
    } else if (*token == '(') {
      trigger_left_paren++;
    }
    ++token;
  }
  if (trigger_left_paren > 0) {
    return 0;
  }
  return 1;
}

void Interpreter::check_input(const string& str) {
  const char* token = &str[0];
  int trigger_encounter_var = 0;
  int trigger_encounter_equal = 0;
  int trigger_encounter_operator = 0;
  int trigger_started_line = 0;
  int trigger_fraction = 0;
  while (*token != '\0') {
    if (*token == '=' && trigger_encounter_equal == 1) {
      throw "bad input";
    }
    if (trigger_started_line == 0) {
      trigger_started_line = 1;
      if (*token == '-' || *token == '+') {
        token++;
      } else if (isalpha(*token)) {
        trigger_encounter_var = 1;
        trigger_encounter_operator = 0;
        token++;
        if (isalpha(*token)) {
          throw "bad input";
        }
      } else if (isdigit(*token)) {
        token++;
        trigger_encounter_var = 0;
        trigger_encounter_equal = 0;
        trigger_encounter_operator = 0;
        if (*token == '_') {
          token++;
          if (isdigit(*token)) {
            token++;
          }
        }
        if (*token == '.') {
          if (trigger_fraction == 1) {
            throw "bad input";
          }
          trigger_fraction = 1;
          token++;
          if (isdigit(*token)) {
            trigger_fraction = 0;
            while (*token != '\0' && isdigit(*token)) {
              token++;
            }
          }
        }
      } else if (*token == '(') {
        token++;
      } else {
        throw "bad input";
      }
    }
    if ((*token == '*' || *token == '/' || *token == '-' || *token == '+')) {
      if (trigger_encounter_operator == 1) {
        throw "illegal math expression";
      } else {
        trigger_encounter_operator++;
        trigger_encounter_var = 0;
        token++;
      }
    }
    if (isdigit(*token)) {
      token++;
      trigger_encounter_var = 0;
      trigger_encounter_equal = 0;
      trigger_encounter_operator = 0;
      if (*token == '.') {
        if (trigger_fraction == 1) {
          throw "bad input";
        }
        trigger_fraction = 1;
        token++;
        if (isdigit(*token)) {
          trigger_fraction = 0;
          while (*token != '\0' && isdigit(*token)) {
            token++;
          }
        }
      }
    }
    if (isalpha(*token) && trigger_encounter_var == 1) {
      throw "bad input";
    }
    if (isalpha(*token) && trigger_encounter_var == 0) {
      trigger_encounter_var = 1;
      trigger_encounter_operator = 0;
      token++;
      if (isdigit(*token)) {
        trigger_encounter_var = 0;
        ++token;
        if (*token == '_') {
          token++;
          if (isdigit(*token)) {
            token++;
          }
        }
      } else if (*token == '=') {
        trigger_encounter_equal = 1;
        ++token;
        token++;
        if (*token == '\0') {
          throw "bad input";
        }
      }
    }
    if (isdigit(*token) && trigger_encounter_var == 1 &&
        trigger_encounter_equal == 1) {
      trigger_encounter_var = 0;
      trigger_encounter_equal = 0;
      trigger_encounter_operator = 0;
      token++;
      if (*token == '.') {
        if (trigger_fraction == 1) {
          throw "bad input";
        }
        trigger_fraction = 1;
        token++;
        if (isdigit(*token)) {
          trigger_fraction = 0;
          while (*token != '\0' && isdigit(*token)) {
            token++;
          }
        }
      }
    }
    if (*token == '(') {
      token++;
      trigger_encounter_operator = 0;
      trigger_encounter_var = 0;
      if (*token == '\0') {
        throw "bad input";
      } else {
        if (isalpha(*token) && trigger_encounter_var == 0) {
          trigger_encounter_var = 1;
          token++;
        }
        if (isdigit(*token)) {
          token++;
          trigger_encounter_var = 0;
          trigger_encounter_equal = 0;
          trigger_encounter_operator = 0;
          if (*token == '_') {
            token++;
            if (isdigit(*token)) {
              token++;
              if (*token == '=') {
                token++;
              }
            }
          }
          if (*token == '.') {
            if (trigger_fraction == 1) {
              throw "bad input";
            }
            trigger_fraction = 1;
            token++;
            if (isdigit(*token)) {
              trigger_fraction = 0;
              while (*token != '\0' && isdigit(*token)) {
                token++;
              }
            }
          }
        } else if (*token == '-' || *token == '+') {
          trigger_encounter_var = 0;
          token++;
        } else if (*token == '(') {
          trigger_encounter_var = 0;
          token++;
        } else {
          throw "bad input";
        }
      }
    }
    if (*token == ')') {
      token++;
    }
    trigger_started_line = 1;
  }
}

void Interpreter::check_strange_letters_setVariables(const string& str) {
  const char* token = &str[0];
  while (*token != '\0') {
    if (*token == ' ') {
      throw "cant have spaces";
    }
    if (isalpha(*token)) {
      token++;
      if (isdigit(*token)) {
        token++;
        if (*token == '_') {
          token++;
          if (isdigit(*token)) {
            token++;
            if (isdigit(*token)) {
              throw "invalid variable declaration";
            }
          }
        }
      }
      if (*token != '=') {
        throw "invalid variable declaration";
      } else {
        token++;
        if (isdigit(*token)) {
          while (isdigit(*token)) {
            token++;
          }
          if (*token == '.') {
            token++;
            if (!isdigit((*token))) {
              throw "invalid variable declaration";
            }
            else {
              while (isdigit(*token)) {
                token++;
              }
            }
          }
          if (*token != '\0' && *token !=';') {
            throw "invalid variable declaration";
          } else {
            if (*token == ';') {
              token++;
            }
          }
        } else {
          throw "invalid variable declaration";
        }
      }

    } else if (*token == ')'
        || *token == '(' || *token == '=' || *token == '.' || *token == ';' ||
        *token == '-' || *token == '+' || *token == '/' || *token == '*') {
      ++token;
    } else if(isdigit(*token)) {
      token++;
    } else {
      throw "illegal variable assignment!";
    }
  }
  return;
}
Interpreter::Interpreter() {}

Expression* Interpreter::interpret(const string str) {
  const char* input = &str[0];
  int trigger_start_char = 0;
  string operators("+-*/");
  while (*input != '\0') {
    if (trigger_start_char == 0 && (*input == '-' || *input =='+')) {
      operatorStack.push("-");
      outputQueue.emplace("0");
      ++input;
    }
    /*if (isalpha(*input)) {
      const char* star = input;
      input++;
      if (isdigit(*input)) {
        ++input;
        if (*input == '_') {
          input++;
          if (isdigit(*input)) {
            input++;
          } else {
            throw "bad input";
          }
        }
        string str_key(star, input);
        if (Varmap.find(str_key) == Varmap.end()) {
          throw "error: variable not found";
        } else {
          string str_val = to_string(Varmap[str_key]);
          outputQueue.emplace(str_val);
        }
      } else {
        string str_key(star, input);
        string str_val = to_string(Varmap[str_key]);
        outputQueue.emplace(str_val);
        if (*input != '\0' && *input != '+' && *input != '*' &&
        *input != '/' && *input != '-' && *input != ')') {
          ++input;
        }
      }
    }*/
    if (isdigit(*input)) {
      const char* start = input;
      while (isdigit(*input) || *input == '.') {
        ++input;
      }
      string numberSubstring(start, input);
      outputQueue.emplace(numberSubstring);
    } else if (operators.find(*input) != std::string::npos) {
      string operatorString(input, input + 1);
      ++input;

      // operator
      while (!operatorStack.empty()
          && (getPrecedence(operatorStack.top()) >=
              getPrecedence(operatorString)
          )
          && operatorStack.top() != "("
          ) {
        string stackOperatorString = operatorStack.top();
        operatorStack.pop();
        outputQueue.emplace(stackOperatorString);
      }

      operatorStack.push(operatorString);
    } else if (*input == '(') {
      string paraString(input, input + 1);
      operatorStack.push(paraString);
      ++input;
      if (*input == '-') {
        operatorStack.push("-");
        outputQueue.emplace("0");
        ++input;
      } else if (*input == '+') {
        operatorStack.push("+");
        outputQueue.emplace("0");
        ++input;
      }
    } else if (*input == ')') {
      while (!operatorStack.empty() && operatorStack.top() != "(") {
        outputQueue.emplace(operatorStack.top());
        operatorStack.pop();
      }
      if (!operatorStack.empty() && operatorStack.top() == "(") {
        operatorStack.pop();
      }
      ++input;
    }
    trigger_start_char = 1;
  }

  while (!operatorStack.empty()) {
    if (operatorStack.top() != "(") {
      outputQueue.emplace(operatorStack.top());
    }
    operatorStack.pop();
  }
  while (!outputQueue.empty()) {
    string elemString = outputQueue.front();
    outputQueue.pop();
    if (operators.find(elemString) != std::string::npos &&
        outputQueue.empty()) {
      Expression *v1 = new Value(numbersStack.top());
      numbersStack.pop();
      Expression*v2 = new Value(numbersStack.top());
      numbersStack.pop();
      if (elemString =="*") {
        Mul *m = new Mul(v1, v2);
        return m;
      } else if (elemString == "/") {
        Div *d = new Div(v2, v1);
        return d;
      } else if (elemString == "+") {
        Plus *p = new Plus(v1, v2);
        return p;
      } else if (elemString == "-") {
        Minus *n = new Minus(v2, v1);
        return n;
      }
    }
    if (operators.find(elemString) != std::string::npos) {
      // operator
      double num1 = (numbersStack.top());
      numbersStack.pop();
      double num2 = (numbersStack.top());
      numbersStack.pop();
      double res = performOp(num1, num2, elemString);
      numbersStack.push(res);
    } else {
      // number
      double num = stod(elemString);
      numbersStack.push(num);
    }
  }
  return nullptr;
}

void Interpreter::checksetVariablesinput(const string str) {
  const char* token = &str[0];
  const char* start = token;
  regex r("[a-z][1-9]{0,1}[_]{0,1}[1-9]{0,1}=[1-9]{0,1}[.[1-9]+]{0,1}");
  while (*token != '\0') {
    token++;
    if (*token == ';') {
      if (!regex_match(start, token, r)) {
        throw "illegal variable assignment!";
      }
      token++;
      start = token;
    }
  }
  string c = start;
  if (!regex_match(c.begin(), c.end(), r)) {
    throw "illegal variable assignment!";
  }
}

void Interpreter::setVariables(const string str) {
  checksetVariablesinput(str);
  const char* token = &str[0];
  const char* start = nullptr;
  string c;
  double val;
  while (*token != '\0') {
    if (isalpha(*token)) {
      start = token;
      token++;
      if (isdigit(*token)) {
        token++;
        if (*token == '_') {
          token++;
          token++;
        }
        string key_str(start, token);
        c = key_str;
      } else {
        string key_str(start, token);
        c = key_str;
      }
    }
    if (*token == '=') {
      ++token;
      start = token;
      while (isdigit(*token) || *token == '.') {
        token++;
      }
      string val_to_string(start, token);
      val = stod(val_to_string);
      if (Varmap.find(c) == Varmap.end()) {
        Varmap.insert(std::make_pair(c, val));
      } else {
        Varmap[c] = val;
      }
    }
    if (*token != '\0') {
      token++;
    }
  }
}

Interpreter::~Interpreter() {}
