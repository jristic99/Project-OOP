#include "Reader.h"

Reader::Reader()
{
	setFilepaths("config.txt", "test.txt");
}

Reader* Reader::getInstance()
{
	static Reader instance;
	return &instance;
}

Program Reader::readProgram()
{
	Program program;

	fstream input_file(program_filepath_, ios::in);

	string line;
	while (input_file.peek() != EOF)
	{
		getline(input_file, line);
		program.addEquation(line);
		program.addVariable(line[0]);
	}

	return program;
}

unordered_map<char, double> Reader::readConfig()
{
	fstream input_file(config_filepath_, ios::in);
	unordered_map<char, double> config;
	int paralel_write = 0;

	string line;
	while (input_file.peek() != 'c')
	{
		getline(input_file, line);
		char op_sign = line[1];
		
		string param_string = line.substr(5, line.length() - 5);
		double parameter = stoi(param_string, nullptr);

		switch (op_sign)
		{
		case 'a':
			config['+'] = parameter;
			break;
		case 'm':
			config['-'] = parameter;
			break;
		case 'e':
			config['^'] = parameter;
			break;
		case 'w':
			if (line[0] == 'T')
				config['='] = parameter;
			else parallel_write_ = parameter;
			break;
		}
	}

	getline(input_file, line);
	if (line.substr(14) == "simple")
		simple_strategy_ = true;


	input_file.close();

	return config;
}

int Reader::getParallelWrite()
{
	return parallel_write_;
}

int Reader::isSimpleStrategy()
{
	return simple_strategy_;
}

void Reader::setFilepaths(const string & config_filepath, const string & program_filepath)
{
	config_filepath_ = config_filepath;
	program_filepath_ = program_filepath;
}
