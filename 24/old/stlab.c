#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>

struct nodes
{
    char value;
    struct nodes* prev;
};

typedef struct nodes Nodes;
typedef struct nodes* Stack;

int emptys(Stack s)
{
    return s;
}

char firsts(Stack s)
{
    if(s!=NULL){
        return s->value;
    }
    else {
        return NULL;
    }
}

int counts(Stack s)
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
    ss=malloc(1*sizeof(Nodes));
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

int main()
{
    Stack s=NULL;
    int u=-1;
    char ch='z';
    s=ins(s,ch);

    u=firsts(s);

    printf("first is %c\n",u);
    return 0;
}
