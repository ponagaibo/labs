#ifndef _my_stack_h_
#define _my_stack_h_
struct node_s {
    char value;
    struct node_s* prev;
};
typedef struct node_s Node_s;
typedef struct node_s* Stack;
int empty_s(Stack s);
char first_s(Stack s);
int count_s(Stack s);
Stack in_s(Stack s, char c);
Stack out_s(Stack s, char* c);
Stack del_s(Stack s);
#endif
