#ifndef READER_H
#define READER_H

#include "Program.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;


class Reader
{
public:
	static Reader* getInstance();

	Program readProgram();
	unordered_map<char, double> readConfig();
	int getParallelWrite();
	int isSimpleStrategy();

	void setFilepaths(const string& config_filepath, const string& program_filepath);

private:
	Reader();
	string config_filepath_;
	string program_filepath_;
	int parallel_write_;
	bool simple_strategy_;

};


#endif