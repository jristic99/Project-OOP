#ifndef COMPILATION_STRATEGY_H
#define COMPILATION_STRATEGY_H

#include "Program.h"
#include "Expression.h"

#include <stack>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
using namespace std;

class CompilationStrategy
{
public:
	CompilationStrategy(unordered_map<char, int>  precedence, Program program);

	virtual vector<Expression*> compileProgram() = 0;
	
protected:
	bool isOperator(string s);
	bool isVariable(string s);
	bool isConst(string s);
	bool isOperator(char c);
	bool isVariable(char c);
	bool isConst(char c);

	unordered_map<char, int>  precedence_;
	Program program_;
	vector<string> variables_;

	string output_filepath_;
	fstream output_stream_;
};

class SimpleCompilation : public CompilationStrategy
{
public:
	SimpleCompilation(unordered_map<char, int>  precedence, Program program);
	vector<Expression*> compileProgram() override;

private:
	Expression* compileOneEq(const vector<string>& s, fstream& f);
	vector<vector<string>> convertToPostfix();
	vector<string> convertToPostfix(const string& s);
	void printExpressionTree(Expression* root); //delete
	void printLine(Expression* ex, fstream& f);
	void printEqualsLine(Expression* ex, Expression* result, string variable, fstream& f);

};

class AdvancedCompilation : public CompilationStrategy
{
public:
	AdvancedCompilation(unordered_map<char, int>  precedence, Program program);

	vector<Expression*> compileProgram() override;
private:

};

#endif