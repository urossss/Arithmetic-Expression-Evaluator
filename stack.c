#include "header.h"

int stackEmpty(Stack s) {
	if (s == NULL)
		return 1;
	else
		return 0;
}

void push(Stack *s, Elem *e) {
	e->next = *s;
	*s = e;
}

Elem* pop(Stack *s) {	// da vrati double
	if (stackEmpty(*s)) {
		return NULL;
	} 
	else {
		Elem* e = *s;
		*s = (*s)->next;
		//e->next = NULL;
		return e;
	}
}

Elem* top(Stack s) {
	if (stackEmpty(s)) {
		return NULL;
	}
	else {
		return s;
	}
}