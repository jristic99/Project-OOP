#ifndef HARDWARE_H 
#define HARDWARE_H

#include<string>
#include<vector>
#include <unordered_map>
using namespace std;


class Token //samo ne diraj funkciju string Operation::getString()
{
public:
	Token();
	Token(unsigned int operation_id);
	Token(int operation_id, string name);

	string getString();

protected:
	string name_;
	double value_;
	unsigned int operation_id_;
	unsigned int token_id_;
};

class TokenConstant : public Token
{
public:
	TokenConstant(string name);
};

class TokenVariable : public Token
{

};

class Operation
{
public:
	Operation();
	Operation(int id);
	Operation(int id, double time, Token* left_op, Token* right_op, Token* result);

	virtual string getString() = 0;
	int getId() const;

	string leftOp(); //!!!
	string rightOp();
	string tokenName();
	string time();
	string id(); //!!!

protected:
	Token* left_op_;
	Token* right_op_;
	Token* result_;
	double T_;

private:
	int id_;


};


class Add : public Operation
{
public:
	Add();
	Add(int id, double time, Token* left_op, Token* right_op, Token* result);

	virtual string getString() override;

protected:

private:

};

class Multiply : public Operation
{
public:
	Multiply();
	Multiply(int id, double time, Token* left_op, Token* right_op, Token* result);

	virtual string getString() override;

protected:

private:

};

class Power : public Operation
{
public:
	Power();
	Power(int id, double time, Token* left_op, Token* right_op, Token* result);

	virtual string getString() override;

protected:

private:

};

class Equals : public Operation
{
public:
	Equals();
	Equals(int id, double time, Token* left_op, Token* result_); //result_ = right_op, right_op_ = nullptr

	virtual string getString() override;

protected:

private:

};


#endif