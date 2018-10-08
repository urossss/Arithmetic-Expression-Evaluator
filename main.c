#include "header.h"

int main() {
	Elem *infix = readInfix();
	writeExpression(infix);
	//printf(" = %d\n", evaluatePostfix(infix));

	Elem *postfix = in2Post(infix);
	writeExpression(postfix);
	printf(" = %d\n", evaluatePostfix(postfix));

	deleteExpression(infix);
	deleteExpression(postfix);
}