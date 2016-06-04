#ifndef _my_stack_h_
#define _my_stack_h_

#define STACK_SIZE 30
#define MULT 2

struct node_s
{
    int *data;
    int size;
    int top;
};

typedef struct node_s Node_s;
typedef struct node_s* Stack;

Stack create_s();
void delete_s(Stack *s);
void resize_s(Stack s);
int top_s(Stack s);
void push_s(Stack s, int c);
int pop_s(Stack s);
int size_s(Stack s);
void print_s(Stack s);

#endif
