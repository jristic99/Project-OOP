#include "Machine.h"

Machine::Machine()
{
	input_filepath_ = "test.imf";
}

void Machine::setConfig()
{
	config_ = Reader::getInstance()->readConfig();
}

void Machine::readImf()
{
	setConfig();
	fstream input_file(input_filepath_, ios::in);

	while (input_file.peek() != EOF)
	{
		int operation_id;
		char operation;
		string second = "", third = "", operation_id_string = "";
		string first = "";

		char temp = input_file.get();
		while (input_file.peek() != ']')
		{
			temp = input_file.get();
			operation_id_string += temp;
		}
		operation_id = stoi(operation_id_string, nullptr);

		temp = input_file.get();
		temp = input_file.get();
		operation = input_file.get();
		temp = input_file.get();

		while (input_file.peek() != ' ')
		{
			temp = input_file.get();
			first += temp;
		}

		temp = input_file.get();

		while (input_file.peek() != ' ' && input_file.peek() != '\n')
		{
			temp = input_file.get();
			second += temp;
		}

		if (input_file.peek() != '\n' && operation != '=')
		{
			temp = input_file.get();
			while (input_file.peek() != ' ' && input_file.peek() != '\n')
			{
				temp = input_file.get();
				third += temp;
			}
		}
		temp = input_file.get();

		createOperation(operation_id, operation, first, second, third);
		
	}

	/*for (auto op : operations_)
	{
		cout << op->id() << " "<<op->time() << " " << op->getString() << " " << op->tokenName() << " " << op->leftOp() << " " << op->rightOp() << endl;
	}
	int a = 5;*/
}

void Machine::createOperation(int operation_id, char operation, string first, string second, string third)
{
	var_names_.insert(first);

	Token *left_op = nullptr, *right_op = nullptr;

	if (var_names_.find(second) == var_names_.end()) //first time to see left operand token
	{
		if (isConstant(second))
		{
			left_op = new TokenConstant(second);
			tokens_.push_back(left_op);
		}
		else throw WrongVariableInput("Variable not seen before");

	}
	else
	{
		for (auto t : tokens_)
		{
			if (t->getString() == second)
				left_op = t;
		}
	}

	if (third != "" && var_names_.find(third) == var_names_.end()) //first time to see right operand token
	{
		if (isConstant(third))
		{
			right_op = new TokenConstant(third);
			tokens_.push_back(right_op);
		}
		else throw WrongVariableInput("Variable not seen before");
	}
	else if (third != "")
	{
		for (auto t : tokens_)
		{
			if (t->getString() == third)
				right_op = t;
		}
	}

	Token* new_token = new Token(operation_id, first);
	tokens_.push_back(new_token);

	Operation *new_op;
	double time = config_[operation];
	switch (operation)
	{
	case '+':
		new_op = new Add(operation_id, time, left_op, right_op, new_token);
		break;
	case '*':
		new_op = new Multiply(operation_id, time, left_op, right_op, new_token);
		break;
	case '^':
		new_op = new Power(operation_id, time, left_op, right_op, new_token);
		break;
	case '=':
		new_op = new Equals(operation_id, time, left_op, new_token);
		break;
	default:
		throw WrongOperationInput("Operation not identified");
		break;
	}
	operations_.push_back(new_op);
}

bool Machine::isConstant(string s)
{
	bool result = true;
	for (int i = 0; i < s.length(); i++)
	{
		result = result && (('1' <= s[i]) && (s[i] <= '9') || s[i] == '.' || s[i] == '-');
	}
	return result;
}
