#ifndef MACHINE_H
#define MACHINE_H

#include "Expression.h"
#include "Reader.h"
#include "Exceptions.h"
#include "Hardware.h"
#include <set>
#include <string>
#include <fstream>
#include <iostream> //!!!
using namespace std;

class Machine
{
public:
	Machine();

	void setConfig();
	void readImf();
private:
	void createOperation(int operation_id, char operation, string first, string second, string third);
	bool isConstant(string s);

	unordered_map<char, double> config_;
	string input_filepath_;
	vector<Token*> tokens_;
	vector<Operation*> operations_;
	set<string> var_names_;


};

#endif