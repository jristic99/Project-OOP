#ifndef COMPILER_H
#define COMPILER_H

#include "Hardware.h"
#include "Program.h"
#include <iostream> //DELETE
#include <string>
#include <vector>
#include <set>
#include <stack>
#include <unordered_map>
using namespace std;

class CompilationStrategy;

class Compiler
{
public:
	Compiler();
	void readProgram();
	void compile();

private:
	CompilationStrategy *strategy_;
	Program program_;	
	unordered_map<char, double> config_;
	bool simple_strategy_;
	int parallel_write_;
	unordered_map<char, int> precedence_;
};


#endif