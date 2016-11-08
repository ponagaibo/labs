#include<stdio.h>

struct node
{
    char value;
    struct node* next;
};

typedef struct node Node;
typedef struct node* Queue;

int empty(Queue q)
{
    return (q==NULL);
}

char first(Queue q)
{
    if(!empty(q)) return q->value;
    else return '0';
}

int count(Queue q)
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
    qq=malloc(1*sizeof(Node));
    qq->value=c;
    qq->next=NULL;
    if(!empty(q))
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

