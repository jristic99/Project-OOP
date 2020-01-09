#include "Compiler.h"
#include "Hardware.h"
#include "Reader.h"
#include "CompilationStrategy.h"

int Program::getNumEquations()
{
	return equations_.size();
}

string Program::getEquation(int i)
{
	return equations_[i];
}

void Program::addEquation(const string & eq)
{
	equations_.push_back(eq);
}

void Program::addVariable(char c)
{
	variables_.insert(c);
}

void Program::updateEquation(const string& new_equation, int i)
{
	equations_[i] = new_equation;
}

Compiler::Compiler()
{
	unordered_map<char, int> precedence({
										{ '=', 0 },
										{ '+', 1 },
										{ '*', 2 },
										{ '^', 3 }
										});
	precedence_ = precedence;
}

void Compiler::readProgram()
{
	Reader* reader = Reader::getInstance();

	program_ = reader->readProgram();
	config_ = reader->readConfig();

	if (reader->isSimpleStrategy())
		strategy_ = new SimpleCompilation(precedence_, program_);
	else
		strategy_ = new AdvancedCompilation(precedence_, program_);

	parallel_write_ = reader->getParallelWrite();
}

void Compiler::compile()
{
	strategy_->compileProgram(); //TODO
}


Constant::Constant(const string& constant) : constant_(constant) 
{
	value_ = stod(constant_);
}

string Constant::getString() const
{
	return constant_;
}

Variable::Variable(string s)
{
	name_ = s;
}

string Variable::getString() const
{
	return name_;
}

Expression::Expression() : operation_(nullptr), token_(nullptr) {}

Expression::Expression(string s)
{
	char operation = s[0];
	switch (operation)
	{
	case '+':
		operation_ = new Add();
		token_ = new Token(operation_->getId());
		break;
	case '*':
		operation_ = new Multiply();
		token_ = new Token(operation_->getId());
		break;
	case '^':
		operation_ = new Power();
		token_ = new Token(operation_->getId());
		break;
	case '=':
		operation_ = new Equals();
		break;
	}

}

Expression* Expression::getLeftOperand() const
{
	return left_operand_;
}

Expression* Expression::getRightOperand() const
{
	return right_operand_;
}

unsigned int Expression::getOperationId() const
{
	return operation_->getId();
}

string Expression::getOperationString() const
{
	if (operation_) return operation_->getString();
	else return "";
}

string Expression::getString() const
{
	return token_->getString();
}

void Expression::setLeftOperand(Expression* left_operand)
{
	left_operand_ = left_operand;
}

void Expression::setRightOperand(Expression* right_operand)
{
	right_operand_ = right_operand;
}
