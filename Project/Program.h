#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>
#include <set>
using namespace std;

class Program
{
public:

	int getNumEquations();
	string getEquation(int i);

	void addEquation(const string& eq);
	void addVariable(char c);
	void updateEquation(const string& new_equation, int i);

private:
	vector<string> equations_;
	set<char> variables_;

};

#endif