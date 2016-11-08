#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "my_stack.h"
#include "functs.h"
#define N 100

int is_var(char k) {
  if((k>=65&&k<=90) || (k>=97&&k<=122)) return 1;
  else return 0;
}

struct elem* Dejkstra(struct elem* part, struct elem* res){
  int i=0,j=0,state=1;
  char m,c,t;
  Stack temp=NULL;
  for (i=0;i<count;i++) {
    if(part[i].type==1||part[i].type==2) { res[j]=part[i]; ++j; }
    if (part[i].type==3) temp=in_s(temp,part[i].symb);
    if (part[i].type==4) {
      while((c=first_s(temp))!='(') {
        temp=out_s(temp,&m);
        res[j].symb=m;
        ++j;
      }
      temp=out_s(temp,&m);
    }
    if(part[i].type==0){
      t=part[i].symb;
      if(temp!=NULL){
        c=first_s(temp);
        while(((t=='+'||t=='-')&&(c=='+'||c=='-'||c=='*'||c=='/'||c=='^'))||((t=='*')&&(c=='*'||c=='/'||c=='^'))||((t=='/')&&(c=='^'||c=='*'||c=='/'))){
          temp=out_s(temp,&m);
          res[j].symb=m;
          ++j;
          c=first_s(temp);
        }
        temp=in_s(temp,t);
      }else temp=in_s(temp,t); }
  }
  while(empty_s(temp)) {
    temp=out_s(temp,&m);
    res[j].symb=m;
    ++j;
  }
  count=j;
  return res;
}

int size_of_str(char* str) {
    int i=0;
    while(str[i]!='\0') i++;
    return i;
}

int check_expr(char* str) {
  int i=0,s=0;
  if(str[0]=='/'||str[0]=='*'||str[0]=='^') return 0;
  count = size_of_str(str);
  for(i=0;i<count;i++){
    if( str[i]<=39 || str[i]==44 || str[i]==46 || (str[i]>=58&&str[i]<=64) || (str[i]>=91&&str[i]<=93) || str[i]==95 || str[i]==96 || (str[i]>=123&&str[i]<=127) )return 0;
    if(str[i]=='(') s++;
    if(str[i]==')') s--;
    if(((str[i]>=48&&str[i]<=57)||is_var(str[i]))&&(str[i+1]=='(')) return 0;
    if((str[i]==')')&&((str[i+1]>=48&&str[i+1]<=57)||(str[i+1]>=65&&str[i+1]<=90)||(str[i+1]>=97&&str[i+1]<=122))) return 0;
    if((str[i]=='(')&&(str[i+1]=='*'||str[i+1]=='/'||str[i+1]=='^'||str[i+1]==')')) return 0;
    if((str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='^')&&(str[i+1]==')')) return 0;
    if((str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='^')&&(str[i-1]=='+'||str[i-1]=='-'||str[i-1]=='*'||str[i-1]=='/'||str[i-1]=='^'))return 0;
  }
  if(s!=0)return 0;
  return 1;
}

struct elem* parse(char* ch) {
    struct elem *part;
    part=malloc(N*sizeof(struct elem));
    int i=0,j=0,k=0,b=-1,a=-1,l=0;
    char temp[N];
    for(int i=0;i<N;i++)temp[i]=0;
    i=0;
    if((ch[0]=='-'||ch[0]=='+')&&(isdigit(ch[1]))){
      i++;
      part[j].type=1;
      k=0;
      while((isdigit(ch[i]))){
          temp[k]=ch[i];
          k++;
          i++;
      }
      b=atoi(temp);
      if(ch[0]=='-') b=b*(-1);
      part[j].value=b;
      ++j;
      for(a=0;a<N;a++)temp[a]='\0';
    }
    if( (ch[0]=='-'||ch[0]=='+') && ( is_var(ch[1]) || ch[1]=='(' ) ){
      if(is_var(ch[1])){ part[j].type=3; part[j].symb='('; j++; }
      part[j].type=1;
      part[j].value=0;
      j++;
      part[j].type=0;
      if(ch[0]=='-') part[j].symb='-';
      else part[j].symb='+';
      j++;
      i++;
      if(is_var(ch[1])){
        part[j].type=2;
        part[j].symb=ch[i];
        j++;
        i++;
        part[j].type=4;
        part[j].symb=')';
        j++;
      }
    }
    while(ch[i]!='\0'){
      if (ch[i]=='(') {
          part[j].type=3;
          part[j].symb='(';
          ++j;
          ++i;
          if((ch[i]=='-'||ch[i]=='+') && ( is_var(ch[i+1]) || ch[i+1]=='(' )) {
            part[j].type=1;
            part[j].value=0;
            j++;
            part[j].type=0;
            if(ch[i]=='-') part[j].symb='-';
            else part[j].symb='+';
            j++;
            i++;
          }
      }
      if (ch[i]==')'){ part[j].type=4; part[j].symb=')'; ++j; ++i; }
      if (ch[i]=='+'){
        if(ch[i-1]=='('){
          ++i;
          part[j].type=1;
          k=0;
          while((isdigit(ch[i]))){
              temp[k]=ch[i];
              k++;
              i++;
          }
          b=atoi(temp);
          part[j].value=b;
          ++j;
          for(a=0;a<N;a++)temp[a]='\0';
        }else{ part[j].type=0; part[j].symb='+'; ++j; ++i; }
      }
      if (ch[i]=='-'){
          if(ch[i-1]=='('){
              ++i;
              part[j].type=1;
              k=0;
              while((isdigit(ch[i]))){
                  temp[k]=ch[i];
                  k++;
                  i++;
              }
              b=atoi(temp);
              b=b*(-1);
              part[j].value=b;
              ++j;
              for(a=0;a<N;a++)temp[a]='\0';
          }else{ part[j].type=0; part[j].symb='-'; ++j; ++i; }
      }
      if (ch[i]=='*'){ part[j].type=0; part[j].symb='*'; ++j; ++i; }
      if (ch[i]=='/'){ part[j].type=0; part[j].symb='/'; ++j; ++i; }
      if (ch[i]=='^'){ part[j].type=0; part[j].symb='^'; ++j; ++i; }
      if((isdigit(ch[i]))){
          part[j].type=1;
          k=0;
          while((isdigit(ch[i]))){
              temp[k]=ch[i];
              k++;
              i++;
          }
          b = atoi(temp);
          part[j].value=b;
          ++j;
          for(a=0;a<N;a++)temp[a]='\0';
      }
      if(ch[i]>='A'&& ch[i]<='Z' || ch[i]>='a'&& ch[i]<='z'){ part[j].type=2; part[j].symb=ch[i]; ++j; ++i; }
    }
    count=j;
    return part;
}

void print_pars(struct elem* orig) {
    for(int j=0;j<count;j++){
        if (orig[j].type!=1) printf("%c ",orig[j].symb);
        else printf("%d ",orig[j].value);
    }
    printf("\n");
}
