#include "header.h"

int isOperand(Elem *e) {
	return !isOperator(e);
}

int isOperator(Elem *e) {
	char *s = e->s;
	if (!strcmp(s, "+") || !strcmp(s, "-") || !strcmp(s, "*") || !strcmp(s, "/") || !strcmp(s, "^") || !strcmp(s, "(") || !strcmp(s, ")"))
		return 1;
	else
		return 0;
}

int getInputPriority(Elem *e) {
	char c = *e->s;
	switch (c) {
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	case '^':
		return 5;
	case '(':
		return 6;
	case ')':
		return 1;
	default:
		return -1;
	}
}

int getStackPriority(Elem *e) {
	char c = *e->s;
	switch (c) {
	case '+':
		return 2;
	case '-':
		return 2;
	case '*':
		return 3;
	case '/':
		return 3;
	case '^':
		return 4;
	case '(':
		return 0;
	case ')':
		return -1;
	default:
		return -1;
	}
}

int getRank(Elem *e) {
	char c = *e->s;
	switch (c) {
	case '+':
		return -1;
	case '-':
		return -1;
	case '*':
		return -1;
	case '/':
		return -1;
	case '^':
		return -1;
	default:
		return 0;
	}
}