#include "Hardware.h"

string Multiply::getString()
{
	return "*";
}

string Power::getString()
{
	return "^";
}

string Equals::getString()
{
	return "=";
}

string Add::getString()
{
	return "+";
}

unsigned int Operation::getId() const
{
	return id_;
}

Operation::Operation()
{
	static unsigned int count_operations_ = 1;
	id_ = count_operations_;
	count_operations_++;
}

Token::Token(unsigned int operation_id) : operation_id_(operation_id)
{
	static unsigned int count_tokens_ = 1;
	token_id_ = count_tokens_;
	name_ = "t" + to_string(token_id_);
	count_tokens_++;
}

//Token::Token(int operation_id, char op, string first, string second, string third) : operation_id_(operation_id)
//{
//	switch (op)
//	{
//	case '=':
//		operation_ = new Equals();
//		name_ = first;
//		left_op_s_ = second;
//		break;
//	case '*':
//		operation_ = new Multiply();
//		name_ = first;
//		left_op_s_ = first;
//		right_op_s_ = second;
//		break;
//	case '+':
//		operation_ = new Add();
//		name_ = first;
//		left_op_s_ = first;
//		right_op_s_ = second;
//		break;
//	case '^':
//		operation_ = new Power();
//		name_ = first;
//		left_op_s_ = first;
//		right_op_s_ = second;
//		break;
//
//	}
//}

string Token::getString()
{
	return name_;
}

//string Token::getStringLeftOp()
//{
//	return right_op_s_;
//}
//
//string Token::getStringRightOp()
//{
//	return left_op_s_;
//}
//
//void Token::setLeftOp(Token* left)
//{
//	left_op_ = left;
//}
//
//void Token::setRightOp(Token* right)
//{
//	right_op_ = right;
//}
