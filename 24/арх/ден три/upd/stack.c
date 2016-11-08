#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void Create(stack* s)
{
	s->top = NULL;
	s->size = 0;
}
	
int Empty(stack* s)
{
	if(!s->top) return 1;
	return 0;
}

int Push(stack* s,struct it* t)
{
	struct item* i = malloc(sizeof(struct item));
	if (!i) {printf(" ***Memory error!***"); return 0;}
	i->data=t;
	i->prev=s->top;
	s->top=i;
	s->size++;
	return 1;
}

int Pop(stack* s)
{
	if(!s->size) return 0;
	struct Item* i=s->top;
	s->top=s->top->prev;
	s->size--;
	free(i);
	return 1;
}

struct it* Top(stack* s)
{
	if (s->top)
		return s->top->data;
}

void Destroy(stack* s)
{	
	while (s->top)
	{
		struct Item* i=s->top;
		s->top=s->top->prev;
		free(i);
	}
	s->top = NULL;
	s->size = 0;
}