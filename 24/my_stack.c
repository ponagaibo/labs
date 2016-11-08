#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "my_stack.h"

int empty_s(Stack s){
    if (s==NULL) return 0;
    else return 1;
}

char first_s(Stack s){
    if(s!=NULL) return s->value;
    else return 0;
}

int count_s(Stack s){
    int i;
    for(int i=0;s!=NULL;i++) s=s->prev;
    return i;
}

Stack in_s(Stack s, char c){
    Stack ss;
    ss=malloc(1*sizeof(Node_s));
    ss->value=c;
    ss->prev=s;
    return ss;
}

Stack out_s(Stack s, char* c){
    *c=s->value;
    Stack ss=s->prev;
    free(s);
    return ss;
}

Stack del_s(Stack s){
    Stack ss;
    while(ss!=NULL) {
        ss=s->prev;
        free(s);
        s=ss;
    }
    return s;
}
