#include<stdio.h>

struct node
{
    char value;
    struct node* prev;
};

typedef struct node Node;
typedef struct node* Stack;

int empty(Stack s)
{
    return (s==NULL);
}

char first(Stack s)
{
    if(!empty(s)) return s->value;
    else return '0';
}

int count(Stack s)
{
    int i=0;
    for(i=0;s!=NULL;i++)
    {
        s=s->prev;
    }
    return i;
}

Stack ins(Stack s, char c)
{
    Stack ss;
    ss=malloc(1*sizeof(Node));
    ss->value=c;
    ss->prev=s;
    return ss;
}

Stack out_s(Stack s, char* c)
{
    *c=s->value;
    Stack ss=s->prev;
    free(s);
    return ss;
}

Stack del_s(Stack s)
{
    Stack ss;
    while(ss!=NULL)
    {
        ss=s->prev;
        free(s);
        s=ss;
    }
    return s;
}
