#ifndef _HEADER_
#define _HEADER_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef enum { ALLOCATION_FAIL = 1, NUMBER_TOO_BIG, INVALID_EXPRESSION } Error;

typedef enum { ADD = 1, SUB, MUL, DIV, POW, PAR_OPEN, PAR_CLOSED } Operator;

typedef struct elem {
	char *s;
	struct elem *next;
} Elem;

typedef Elem *Stack;

// expression
Elem *readInfix();
void writeExpression(Elem *);
void addToPostfix(Elem **, Elem **, Elem *);
Elem *in2Post(Elem *);
int evaluatePostfix(Elem *);

// operators
int isOperand(Elem *);
int isOperator(Elem *);
int getInputPriority(Elem *);
int getStackPriority(Elem *);
int getRank(Elem *);

// stack
int stackEmpty(Stack);
void push(Stack*, Elem*);
Elem* pop(Stack*);
Elem* top(Stack);

// helper
void error(Error);
Elem *copyElemInfo(Elem *);
void deleteElem(Elem *);
void deleteExpression(Elem *);

#endif