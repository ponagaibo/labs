#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"my_stack.h"
#include"stack_s.h"

Stack_st create_st() {
    Stack_st out=NULL;
    out=malloc(sizeof(Node_st));
    out->sizest=STACK_SIZE;
    out->datast=malloc(out->sizest*sizeof(Stack));
    out->topst=0;
    return out;
}

void delete_st(Stack_st *s) {
    free((*s)->datast);
    free(*s);
    *s=NULL;
}

void resize_st(Stack_st s) {
    s->sizest*=MULT;
    s->datast=realloc(s->datast, s->sizest*sizeof(Stack));
}

Stack top_st(Stack_st s)
{
    if(s->topst>0) return s->datast[s->topst-1];
    else{
        printf("Error! Stack is empty.\n");
        return NULL;
    }
}

void push_st(Stack_st s, Stack c)
{
    if(s->topst>=s->sizest)
    {
        resize_st(s);
    }
    s->datast[s->topst]=c;
    s->topst++;
}

Stack pop_st(Stack_st s)
{
    if(s->topst>0)
    {
        s->topst--;
        return s->datast[s->topst];
    }else{
        printf("Error! Stack is empty.\n");
        return NULL;
    }
}

int size_st(Stack_st s)
{
    return s->topst;
}

void print_st(Stack_st s)
{
    int i=0;
    for(i=(s->topst)-1;i>=0;i--)
    {
      Stack ss=s->datast[i];
      for(int j=(ss->top)-1; j>=0; j--)
      {
        printf("%d\n", ss->data[j]);
      }
      printf("\n");
    }
}
