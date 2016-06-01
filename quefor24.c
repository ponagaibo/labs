#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>

struct nodeq
{
    char value;
    struct nodeq* next;
};

typedef struct nodeq Nodeq;
typedef struct nodeq* Queue;

int emptyq(Queue q)
{
    return (q==NULL);
}

char firstq(Queue q)
{
    if(!emptyq(q)) return q->value;
    else return '0';
}

int countq(Queue q)
{
    int i=0;
    for(i=0;q!=NULL;i++)
    {
        q=q->next;
    }
    return i;
}

Queue inq(Queue q, char c)
{
    Queue qq, q1=q;
    qq=malloc(1*sizeof(Nodeq));
    qq->value=c;
    qq->next=NULL;
    if(!emptyq(q))
    {
        while(q->next!=NULL)
        {
            q=q->next;
        }
        q->next=qq;
    }else
    {
        return qq;
    }
    return q1;
}

Queue out_q(Queue q, char* c)
{
    *c=q->value;
    Queue qq=q->next;
    free(q);
    return qq;
}

Queue del_q(Queue q)
{
    Queue qq;
    while(qq!=NULL)
    {
        qq=q->next;
        free(q);
        q=qq;
    }
    return q;
}

