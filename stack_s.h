#ifndef _stack_s_h_
#define _stack_s_h_
#include"my_stack.h"

#define STACK_SIZE 30
#define MULT 2

struct st_st
{
    Stack *datast;
    int sizest;
    int topst;
};

typedef struct st_st Node_st;
typedef struct st_st* Stack_st;

Stack_st create_st();
void delete_st(Stack_st *s);
void resize_st(Stack_st s);
Stack top_st(Stack_st s);
void push_st(Stack_st s, Stack c);
Stack pop_st(Stack_st s);
int size_st(Stack_st s);
void print_st(Stack_st s);

#endif
