#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
using namespace std;

class WrongVariableInput : public exception {
public:
	WrongVariableInput(const char* msg) : exception(msg) {}
};

class WrongOperationInput : public exception {
public:
	WrongOperationInput(const char* msg) : exception(msg) {}
};

#endif