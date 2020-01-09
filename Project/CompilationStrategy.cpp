#include "CompilationStrategy.h"

vector<string> SimpleCompilation::convertToPostfix(const string & s)
{
	vector<string> postfix;
	stack<string> stack;

	int j = 0;
	while (j < s.length())
	{
		string curr = "";

		if (isOperator(s[j]) || isVariable(s[j])) curr += s[j++];
		else
		{
			while ((isConst(s[j]) || s[j] == '.' || s[j] == '-') && j < s.length())
				curr += s[j++];
		}

		if (curr == "")
		{
			j++;
			continue;
		}

		if (isVariable(curr) || isConst(curr))
			postfix.push_back(curr);
		else
			if (stack.empty() || precedence_[curr[0]] > precedence_[stack.top()[0]])
				stack.push(curr);
			else
			{
				while (!stack.empty() && precedence_[curr[0]] <= precedence_[stack.top()[0]])
				{
					if (precedence_[curr[0]] == precedence_[stack.top()[0]] && curr[0] == '^') 
						break;
					string top = stack.top();
					stack.pop();
					postfix.push_back(top);
				}
				stack.push(curr);
			}
	}
	while (!stack.empty())
	{
		postfix.push_back(stack.top());
		stack.pop();
	}

	return postfix;
}

void SimpleCompilation::printExpressionTree(Expression * root)
{
	if (!root) return;
	printExpressionTree(root->getLeftOperand());
	printExpressionTree(root->getRightOperand());
	cout << root->getString() << " ";
}

void SimpleCompilation::printLine(Expression* ex, fstream& f)
{
	f << "[" << ex->getOperationId() << "] " << ex->getOperationString() << " " << ex->getString() << " ";
	f << ex->getLeftOperand()->getString() << " ";
	f << ex->getRightOperand()->getString() << endl;
}

void SimpleCompilation::printEqualsLine(Expression* ex, Expression* result, string variable, fstream& f)
{
	f << "[" << ex->getOperationId() << "]" << " " << ex->getOperationString() << " ";
	f << variable << " " << result->getString() << endl;
}

vector<vector<string>> SimpleCompilation::convertToPostfix()
{
	vector<vector<string>> program_to_postfix;
	for (int i = 0; i < program_.getNumEquations(); i++)
	{
		vector<string>  postfix_eq = convertToPostfix(program_.getEquation(i));
		program_to_postfix.push_back(postfix_eq);
	}
	return program_to_postfix;
}

SimpleCompilation::SimpleCompilation(unordered_map<char, int> precedence, Program program) : CompilationStrategy(precedence, program) {}

vector<Expression*> SimpleCompilation::compileProgram()
{
	fstream output_stream(output_filepath_, ios::out);

	vector<Expression*> expression_trees;
	vector<vector<string>> prefix_form = convertToPostfix();
	for (int i = 0; i < program_.getNumEquations(); i++)
	{
		vector<string> equation = prefix_form[i];
		expression_trees.push_back(compileOneEq(equation, output_stream));
	}

	output_stream.close();
	return expression_trees;
}

Expression* SimpleCompilation::compileOneEq(const vector<string>& s, fstream& f)
{
	stack<Expression*> stack;
	Expression *e1, *e2;
	variables_.push_back(s[0]);

	int i;
	for (i = 1; i < s.size() - 1; i++) //ignores variable name and '='
	{
		string curr = s[i];
		if (isConst(curr))
		{
			Expression *ex = new Constant(curr);
			stack.push(ex);
		}
		else if (isVariable(curr))
		{
			Expression *ex = new Variable(curr);
			stack.push(ex);
		}
		else
		{
			Expression *ex = new Expression(curr);

			e1 = stack.top();
			stack.pop();
			e2 = stack.top();
			stack.pop();

			ex->setRightOperand(e1);
			ex->setLeftOperand(e2);

			printLine(ex, f);

			stack.push(ex);
		}
	}
	Expression *result = stack.top();
	stack.pop();

	Expression *ex = new Expression(s[i]);
	printEqualsLine(ex, result, s[0], f);

	return result;
}

CompilationStrategy::CompilationStrategy(unordered_map<char, int> precedence, Program program) : precedence_(precedence), program_(program) 
{
	output_filepath_ = "test.imf";
}

bool CompilationStrategy::isOperator(string s)
{
	return (s.length() == 1) && (s[0] == '+' || s[0] == '*' || s[0] == '^' || s[0] == '=');
}

bool CompilationStrategy::isVariable(string s)
{
	return (s.length() == 1) && ('a' <= s[0]) && (s[0] <= 'z');
}

bool CompilationStrategy::isConst(string s)
{
	bool result = true;
	for (int i = 0; i < s.length(); i++)
	{
		result = result && (('1' <= s[i]) && (s[i] <= '9') || s[i] == '.' || s[i] == '-');
	}
	return result;
}

bool CompilationStrategy::isOperator(char c)
{
	return c == '+' || c == '*' || c == '^' || c == '=';
}

bool CompilationStrategy::isVariable(char c)
{
	return ('a' <= c) && (c <= 'z');
}

bool CompilationStrategy::isConst(char c)
{
	return ('1' <= c) && (c <= '9');
}

AdvancedCompilation::AdvancedCompilation(unordered_map<char, int> precedence, Program program) : CompilationStrategy(precedence, program) {}

vector<Expression*> AdvancedCompilation::compileProgram()
{
	return {};
}
