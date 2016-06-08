#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"my_stack.h"
#include"stack_s.h"
#include <math.h>

Stack reverse_st(Stack st)
{
  if(st->size<=1)
  {
      return st;
  }else{
    Stack temp=create_s();
    while(st->size>0) push_s(temp, pop_s(st));
    delete_s(st);
    return temp;
  }
}

Stack merge(Stack f, Stack s)
{
    Stack res;
    int f_size,s_size;
    f_size=size_s(f);
    s_size=size_s(s);
    int k=f_size+s_size;
    int temp[f_size+s_size];
    int i=0,elem,j,g=0;
    res=create_s();
    while(((s->top)!=NULL)&&((f->top)!=NULL))
    {
        if(top_s(f)<=top_s(s))
        {
            elem=pop_s(f);
            temp[i]=elem;//!!
        }else{
            elem=pop_s(s);
            temp[i]=elem;
        }
        i++;
    }
    if((s->top)!=NULL)
    {
      while((s->top)!=NULL)
      {
        elem=pop_s(s);
        temp[i]=elem;
        i++;
      }
    }
    if((f->top)!=NULL)
    {
      while((f->top)!=NULL)
      {
        elem=pop_s(f);
        temp[i]=elem;
        i++;
      }
    }
    for(j=i-1;j>=0;j--)  push_s(res,temp[j]);
    return res;
}

Stack merge_sort(Stack stck)
{
  int times,sz;
  float lg;
  sz=size_s(stck);
  lg=log2(sz);
  times=ceil(lg);

  Stack orig=create_s();
  Stack_st res=create_st();
  Stack_st temp=create_st();
  Stack mrg=create_s();
  Stack a=create_s();
  Stack b=create_s();

  if(sz==1) return stck;
  else{
    orig=stck;
    while(orig->top>0)
    {
      mrg=create_s();
      push_s(mrg,pop_s(orig));
      push_st(res,mrg);
    }
    while(res->topst>0) push_st(temp,pop_st(res));
    for(int i=0; i<times; i++)
    {
      while(temp->topst>0)
      {
        mrg==create_s();
        a=create_s();
        b=create_s();
        if (temp->topst>0) a=pop_st(temp);
        if (temp->topst>0) b=pop_st(temp);
        mrg=merge(a,b);
        push_st(res,mrg);
      }
      temp=create_st();
      while(res->topst>0) push_st(temp,pop_st(res));
    }
    if(temp->topst!=1)
    {
      printf("Error!\n");
      return NULL;
    }else{
      orig=create_s();
      orig=pop_st(temp);
      return orig;
    }
  }
  delete_s(&a);
  delete_s(&b);
  delete_s(&mrg);
  delete_st(&res);
  delete_st(&temp);
}
