#ifndef HARDWARE_H
#define HARDWARE_H

#include<string>
#include<vector>
using namespace std;


class Token
{
public:
	Token(unsigned int operation_id);
	//Token(int op_id, char op, string first, string second, string third);

	string getString();
	/*string getStringLeftOp();
	string getStringRightOp();

	void setLeftOp(Token *left);
	void setRightOp(Token *right);*/

private:
	string name_;
	double value_;
	unsigned int operation_id_;
	unsigned int token_id_;
	//Operation* operation_;
	//Token *left_op_, *right_op_;
	//string left_op_s_, right_op_s_;
};

//class Variable : public Token
//{
//	Variable(int op_id, char op, string first, string second);
//};
//
//class Constant : public Token
//{
//	Constant(int op_id, char op, string first, string second);
//};

class Operation
{
public:
	Operation();
	virtual string getString() = 0;
	unsigned int getId() const;

private:
	int id_;
	double T_;
	Token* left_op_;
	Token* right_op_;
	Token* result_;
	int num_of_inputs_;
};


class ArithmeticOperation : public Operation
{


};

class Add : public ArithmeticOperation
{
public:
	virtual string getString() override;

protected:

private:

};

class Multiply : public ArithmeticOperation
{
public:
	virtual string getString() override;

protected:

private:

};

class Power : public ArithmeticOperation
{
public:
	virtual string getString() override;

protected:

private:

};

class Equals : public ArithmeticOperation
{
public:
	virtual string getString() override;

protected:

private:

};


#endif