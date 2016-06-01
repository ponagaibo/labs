#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>

struct node_s
{
    char value;
    struct node_s* prev;
};

typedef struct node_s Node_s;
typedef struct node_s* Stack;

int empty_s(Stack s)
{
    if (s==NULL) return 0;
    else return 1;
}

char first_s(Stack s)
{
    if(s!=NULL) return s->value;
    else return 0;
}

int count_s(Stack s)
{
    int i=0;
    for(i=0;s!=NULL;i++) s=s->prev;
    return i;
}

Stack in_s(Stack s, char c)
{
    Stack ss;
    ss=malloc(1*sizeof(Node_s));
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

int count;

struct elem{
    int type;// 0 - char, 1 - int, 2 - var
    int value;
    char symb;
};


struct elem* Dejkstra(struct elem* part, struct elem* res)
{
    int i=0,j=0,state=1;
    char m,c,t;
    Stack temp=NULL;
    for (i=0;i<count;i++)
    {
        if(part[i].type==1||part[i].type==2)
        {
            res[j]=part[i];
            j++;
        }
        /*if(part[i].type==0)
        {
            temp=in_s(temp,part[i].symb);
        }*/
        if (part[i].type==3)
        {
            temp=in_s(temp,part[i].symb);
        }
        if (part[i].type==4)
        {
            while((c=first_s(temp))!='(')
            {
                if(!empty_s(temp))
                {
                    printf("Wrong quantity of brackets\n");
                    state=0;
                    return res;
                    break;
                }
                temp=out_s(temp,&m);
                res[j].symb=m;
                j++;
            }
            temp=out_s(temp,&m);
            /*if((c=first_s(temp))== '+' || c=='-' || c=='*' || c=='/' || c=='^')
            {
                temp=out_s(temp,&m);
                res[j]=m;
                j++;
            }*/
        }
        if(!state)
        {
            //i=count;
            break;
        }
        if(part[i].type==0)
        {
            t=part[i].symb;
            if (temp!=NULL)
            {
                c=first_s(temp);
                while((t=='+'||t=='-')&&(c=='*'||c=='\\'||c=='^')||(t=='*'||t=='\\')&&(c=='^'))
                {
                    temp=out_s(temp,&m);
                    res[j].symb=m;
                    j++;
                    c=first_s(temp);
                }
                temp=in_s(temp,t);
            } else {
                temp=in_s(temp,t);
            }
        }
    }

    while(empty_s(temp))
    {
        temp=out_s(temp,&m);
        res[j].symb=m;
        j++;
    }
    return res;
}

