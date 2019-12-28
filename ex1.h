// Copyright 2019 Meni
#ifndef H_EX1_H
#define H_EX1_H
#include "Expression.h"
#include <string>
#include<stack>
#include<queue>
#include <map>
#include <iostream>
#include <regex>
/**
 * Expression Interface
 */
class UnaryOperator : public Expression {
 protected:
  Expression* _expression;
 public:
  explicit UnaryOperator(Expression *expression);
  virtual ~UnaryOperator();
};
class BinaryOperator : public Expression {
 protected:
  Expression* _left, * _right;
 public:
  BinaryOperator(Expression* left, Expression* right);
  virtual ~BinaryOperator();
};
class Minus : public BinaryOperator {
 public:
  Minus(Expression* left, Expression* right);
  double calculate();
  virtual ~Minus();
};
class Mul : public BinaryOperator {
 public:
  Mul(Expression* left, Expression* right);
  double calculate();
  virtual ~Mul();
};
class Plus : public BinaryOperator {
 public:
  Plus(Expression* left, Expression* right);
  double calculate();
  virtual ~Plus();
};
class Div : public BinaryOperator {
 public:
  Div(Expression *left, Expression *right);

  double calculate();
  virtual ~Div();
};


class UMinus : public UnaryOperator {
 public:
  explicit UMinus(Expression* expression);
  double calculate();
  virtual  ~UMinus();
};

class UPlus : public UnaryOperator {
 public:
  explicit UPlus(Expression* expression);
  virtual double calculate();
  virtual ~UPlus();
};

class Variable : public Expression {
 private:
  string _name;
  double _value;

 public:
  Variable(string name, double value);
  Variable& operator++();
  Variable& operator--();
  Variable& operator+=(double val);
  Variable& operator-=(double val);
  Variable& operator++(int);
  Variable& operator--(int);
  virtual double calculate();
  virtual ~Variable();
};

class Value : public Expression {
 private:
  double _value;

 public:
  explicit Value(double value);
  virtual double calculate();
  virtual ~Value();
};

class Interpreter {
  stack <string> operatorStack;
  stack <double> numbersStack;
  queue <string> outputQueue;
  map<string, double> Varmap;

 public:
  Interpreter();
  double performOp(double num1, double num2, string op);
  int getPrecedence(string op);
  int check_parenthesis(const string& str);
  void check_input(const string& str);
  Expression* interpret(const string str);
  void setVariables(const string str);
  void check_strange_letters_setVariables(const string& str);
  virtual ~Interpreter();
  void checksetVariablesinput(const string str);
};
#endif


