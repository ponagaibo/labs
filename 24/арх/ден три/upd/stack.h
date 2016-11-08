#ifndef _stack_h_
#define _stack_h_

struct it//эл-т выражения
{
	int cod;//0-переменная,операция, 1-константа
	char var;
	int val;
};

struct item//эл-т стека ,состоящего из эл-тов выражения
{
	struct item *prev;
	struct it *data;
};

typedef struct
{
	struct item *top;
	int size;
}stack;

void Create(stack *s);
int Empty(stack *s);
int Push(stack *s,struct it *t);
int Pop(stack *s);
struct it* Top(stack *s);
void Destroy(stack *s);

#endif
