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

int count,size;

enum brackets{
    obr=0,
    cbr
};

enum operations{
    plus=0,
    minus,
    multip,
    dev,
    pw
};

union symb{
    int value;//0
    char var;//1
    enum brackets br;//2
    enum operations op;//3
};

struct elem{
    int flag;
    int type;// 0 - char, 1 - int
    char sgn;
    union symb el;
};

int main()
{
    struct elem orig;
    orig.flag=2;
    orig.type=1;
    orig.sgn='=';
    struct elem cop;
    cop=orig;
    printf("Orig: flag=%d, type=%d, sgn=%c\n",orig.flag, orig.type, orig.sgn);
    printf("Copy: flag=%d, type=%d, sgn=%c\n",cop.flag, cop.type, cop.sgn);

    return 0;
}
//разобраться с интом и чар при хранении, хранить значение как структуру с флагом либо юнион
//разобраться, почему после знача операции еще знак

