#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Hardware.h"

class Expression
{
public:
	Expression();
	Expression(string s);

	Expression* getLeftOperand() const;
	Expression* getRightOperand() const;
	virtual string getString() const;
	unsigned int getOperationId() const;
	string getOperationString() const;

	void setLeftOperand(Expression* left_operand);
	void setRightOperand(Expression* right_operand);


protected:
	Expression* left_operand_;
	Expression* right_operand_;

	Operation *operation_;

	Token* token_;
private:

};

class Constant : public Expression
{
public:
	Constant(const string& constant);

	virtual string getString() const override;

private:
	double value_;
	string constant_;
};

class Variable : public Expression
{
public:
	Variable(string s);

	virtual string getString() const override;
private:
	string name_;
};

#endif