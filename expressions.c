#include "header.h"

Elem *readInfix() {
	Elem *exp = NULL, *last = NULL, *curr = NULL;
	char c = getchar();
	while (1) {
		if (c == ' ') {
			c = getchar();
			continue;
		}
		if (!last) {
			exp = curr;
		}
		else {
			last->next = curr;
		}
		last = curr;
		if (c == '\n' || c == '=') break;

		curr = malloc(sizeof(Elem));
		if (!curr) error(ALLOCATION_FAIL);
		curr->next = NULL;

		if (isdigit(c)) {	// operand
			curr->s = malloc(11 * sizeof(char));
			if (!curr->s) error(ALLOCATION_FAIL);
			int i = 0;
			do {
				if (i >= 10) {
					error(NUMBER_TOO_BIG);
				}
				curr->s[i++] = c;
			} while (isdigit(c = getchar()));
			curr->s[i] = '\0';
			if (i < 10) {
				curr->s = realloc(curr->s, (i + 1) * sizeof(char));
				if (!curr->s) error(ALLOCATION_FAIL);
			}
			continue;
		}
		else {	// operator
			curr->s = malloc(2 * sizeof(char));
			if (!curr->s) error(ALLOCATION_FAIL);
			curr->s[0] = c;
			curr->s[1] = '\0';
		}
		c = getchar();
	}
	return exp;
}

void writeExpression(Elem *exp) {
	while (exp) {
		printf("%s ", exp->s);
		exp = exp->next;
	}
	putchar('\n');
}

void addToPostfix(Elem **postfix, Elem **last, Elem *next) {
	if (!(*last)) {
		*postfix = next;
	}
	else {
		(*last)->next = next;
	}
	*last = next;
}

Elem *in2Post(Elem *infix) {
	Elem *next, *x, *postfix = NULL, *last = NULL;
	Stack s = NULL;
	int rank = 0;
	while (infix) {
		next = copyElemInfo(infix);
		if (!isOperator(next)) {	// operand
			addToPostfix(&postfix, &last, next);
			rank++;
		}
		else {	// operator
			while (!stackEmpty(s) && getInputPriority(next) <= getStackPriority(top(s))) {
				x = pop(&s);
				addToPostfix(&postfix, &last, x);
				rank += getRank(x);
				if (rank < 1) error(INVALID_EXPRESSION);
			}

			if (strcmp(next->s, ")")) {
				push(&s, next);
			}
			else {
				x = pop(&s);
			}
		}
		infix = infix->next;
	}
	while (!stackEmpty(s)) {
		x = pop(&s);
		addToPostfix(&postfix, &last, x);
		rank += getRank(x);
	}
	if (rank != 1) {
		error(INVALID_EXPRESSION);
	}
	return postfix;
}

Elem *calculate(Elem *op1, Elem *op, Elem *op2) {
	Elem *result = malloc(sizeof(Elem));
	if (!result) error(ALLOCATION_FAIL);
	int o1 = atoi(op1->s), o2 = atoi(op2->s), res;
	char c = *op->s;
	switch (c) {
	case '+':
		res = o1 + o2;
		break;
	case '-':
		res = o1 - o2;
		break;
	case '*':
		res = o1 * o2;
		break;
	case '/':
		res = o1 / o2;
		break;
	case '^':
		res = (int)pow(o1, o2);
		break;
	default:
		res = 0;
		break;
	}
	result->next = NULL;
	result->s = malloc(12 * sizeof(char));
	_itoa(res, result->s, 10);
	return result;
}

int evaluatePostfix(Elem *exp) {
	Stack s = NULL;
	Elem *x;
	while (exp) {
		x = copyElemInfo(exp);
		exp = exp->next;
		if (isOperand(x)) {
			push(&s, x);
		}
		else {	// radimo samo sa binarnim operacijama za sad
			Elem *op2 = pop(&s);
			Elem *op1 = pop(&s);
			if (!op1 || !op2) error(INVALID_EXPRESSION);
			push(&s, calculate(op1, x, op2));
			deleteElem(op1);
			deleteElem(op2);
		}
	}
	x = pop(&s);
	if (stackEmpty(s)) {
		return atoi(x->s);
	}
	else {
		error(INVALID_EXPRESSION);
	}
}
