#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"my_stack.h"

Stack create_s() {
    Stack out=NULL;
    out=malloc(sizeof(Node_s));
    out->size=STACK_SIZE;
    out->data=malloc(out->size*sizeof(int));
    out->top=0;
    return out;
}

void delete_s(Stack *s) {
    free((*s)->data);
    free(*s);
    *s=NULL;
}

void resize_s(Stack s) {
    s->size*=MULT;
    s->data=realloc(s->data, s->size*sizeof(int));
}

int top_s(Stack s)
{
    if(s->top>0) return s->data[s->top-1];
    else{
        printf("Error! Stack is empty.\n");
        return -111;
    }
}

void push_s(Stack s, int c)
{
    if(s->top>=s->size) resize_s(s);
    s->data[s->top]=c;
    s->top++;
}

int pop_s(Stack s)
{
    if(s->top>0)
    {
        s->top--;
        return s->data[s->top];
    }else{
        printf("Error! Stack is empty.\n");
        return -111;
    }
}

int size_s(Stack s)
{
    return s->top;
}

void print_s(Stack s)
{
    int i=0;
    for(i=(s->top)-1;i>=0;i--)  printf("%d\n",s->data[i]);
}
