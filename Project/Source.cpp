#include "Reader.h"
#include "Compiler.h"
#include "Expression.h"
#include "Machine.h"
//#include "Machine.h"

int main()
{
	Compiler compiler;
	compiler.readProgram();
	//compiler.convertToPostfix();

	string s = "2*x^3 + x^5*y^3 + 5";
	//Sector<vector<string>> buu = compiler.convertToPostfix();
	//vector<Expression*>  buu  = compiler.compileProgram();
	//compiler.printExpressionTree(buu[0]);

	compiler.compile();

	Machine machine;
	machine.readImf();
	return 0;
}