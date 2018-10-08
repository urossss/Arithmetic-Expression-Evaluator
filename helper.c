#include "header.h"

void error(Error e) {
	switch (e) {
	case ALLOCATION_FAIL:
		fprintf(stderr, "Allocation failed!\n");
		break;
	case NUMBER_TOO_BIG:
		fprintf(stderr, "Numbers can have up to 10 digits!\n");
		break;
	case INVALID_EXPRESSION:
		fprintf(stderr, "Expression is not valid!\n");
		break;
	}
	exit(e);
}

Elem *copyElemInfo(Elem *e) {
	Elem *copy = malloc(sizeof(Elem));
	if (!copy) error(ALLOCATION_FAIL);
	copy->next = NULL;
	copy->s = malloc((strlen(e->s) + 1) * sizeof(char));
	strcpy(copy->s, e->s);
	return copy;
}

void deleteElem(Elem *e) {
	free(e->s);
	free(e);
}

void deleteExpression(Elem *exp) {
	Elem *temp;
	while (exp) {
		temp = exp;
		exp = exp->next;
		deleteElem(temp);
	}
}