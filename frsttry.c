#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"my_stack.h"
#include"stack_s.h"
#include <math.h>

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
            temp[i]=elem;
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

Stack cat(Stack f, Stack s)
{
    int fsize=size_s(f);
    int ssize=size_s(s);
    int i,elem,j, elem2;
    Stack res=create_s();
    Stack temp=create_s();
    for(i=0;i<fsize;i++)
    {
        elem=pop_s(f);
        push_s(temp,elem);
    }
    for(i=0;i<fsize;i++)
    {
        elem=pop_s(temp);
        push_s(res,elem);
    }
    if(size_s(temp)!=0)
    {
        temp->top=0;
    }
    for(i=0;i<ssize;i++)
    {
        elem=pop_s(s);
        push_s(temp,elem);
    }
    for(i=0;i<ssize;i++)
    {
        elem=pop_s(temp);
        push_s(res,elem);
    }
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

int main()
{
    int num;
    int st_size;
    Stack st=create_s();
    Stack res=create_s();
    printf("Enter size of stack:\n");
    scanf("%d", &st_size);
    if(st_size>0)
    {
      printf("Enter elements of stack:\n");
        for(int i=0; i<st_size;i++)
        {
          scanf("%d",&num);
          push_s(st,num);
        }
    }else{
        printf("Wrong size of stack\n");
    }
    if(st->top>0) res=merge_sort(st);
    puts("sorted stack:");
    print_s(res);
    return 0;
}
