#include "Hardware.h"

Multiply::Multiply()
{
}

Multiply::Multiply(int id, double time, Token * left_op, Token * right_op, Token * result) : Operation(id, time, left_op, right_op, result)
{
}

string Multiply::getString()
{
	return "*";
}

Power::Power()
{
}

Power::Power(int id, double time, Token* left_op, Token* right_op, Token* result) : Operation(id, time,left_op, right_op, result)
{
}

string Power::getString()
{
	return "^";
}

Equals::Equals()
{
}

Equals::Equals(int id, double time, Token* left_op, Token* result) : Operation(id, time, left_op, nullptr, result)
{
}

string Equals::getString()
{
	return "=";
}

Add::Add()
{
}

Add::Add(int id, double time, Token * left_op, Token * right_op, Token * result) : Operation(id, time, left_op, right_op, result)
{
}

string Add::getString()
{
	return "+";
}

int Operation::getId() const
{
	return id_;
}

string Operation::leftOp()
{
	return left_op_->getString();
}

string Operation::rightOp()
{
	if(right_op_) return right_op_->getString();
	else return "";
}

string Operation::tokenName()
{
	return result_->getString();
}

string Operation::time()
{
	return to_string(T_);
}

string Operation::id()
{
	return to_string(id_);
}

Operation::Operation()
{
	static unsigned int count_operations_ = 1;
	id_ = count_operations_;
	count_operations_++;
}

Operation::Operation(int id) : id_(id)
{
}

Operation::Operation(int id, double time, Token* left_op, Token* right_op, Token* result) :
	id_(id), T_(time), left_op_(left_op), right_op_(right_op), result_(result) {}


Token::Token()
{
}

Token::Token(unsigned int operation_id) : operation_id_(operation_id)
{
	static unsigned int count_tokens_ = 1;
	token_id_ = count_tokens_;
	name_ = "t" + to_string(token_id_);
	count_tokens_++;
}

Token::Token(int operation_id, string name) : Token()
{
	operation_id_ = operation_id;
	name_ = name;
}

string Token::getString()
{
	return name_;
}

TokenConstant::TokenConstant(string name) : Token()
{
	value_ = stoi(name, nullptr);
	name_ = name;
}
