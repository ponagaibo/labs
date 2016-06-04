#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"my_stack.h"
#include"stack_s.h"

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
    //printf("in merge\n");
    while(((s->top)!=NULL)&&((f->top)!=NULL))
    {
        //printf("f and s isnt null\n");
        if(top_s(f)<=top_s(s))
        {
            //printf("f<s\n");
            elem=pop_s(f);
            temp[i]=elem;
        }else{
            //printf("f>s\n");
            elem=pop_s(s);
            temp[i]=elem;
        }
        i++;
    }
    if((s->top)!=NULL)
    {
        //printf("s isnt null\n");
      while((s->top)!=NULL)
      {
        elem=pop_s(s);
        temp[i]=elem;
        i++;
      }
    }
    if((f->top)!=NULL)
    {
        //printf("f isnt null\n");
        while((f->top)!=NULL)
        {
        elem=pop_s(f);
        temp[i]=elem;
        i++;
        }
    }
    //printf("i=%d, total size=%d\n",i,k);
    for(j=i-1;j>=0;j--)
    {
        //printf("res in stack, j=%d, size of res=%d\n",j, size_s(res));
        //printf("add elem=%d\n",temp[j]);
        push_s(res,temp[j]);
    }
    //printf("end merge, size of res=%d\n", size_s(res));
    return res;
}

Stack r,p;
int bb=0;

Stack merge_sort(Stack orig, int size, Stack res)
{
    //printf("in merge sort\n");
    Stack half=create_s();
    Stack temp=create_s();
    Stack temp2=create_s();
    r=create_s();
    p=create_s();
    Stack t=create_s();
    int size_half=size*0.5;
    int size_orig=size-size_half;
    int i,elem,elem2;
    printf("size=%d, size half=%d, size orig=%d\n~~~~~~~~orig:~~~~~~~~\n",size, size_half, size_orig);
    print_s(orig);
    puts("~~~~~~~~~~~~~~~~~~~~~");
    printf("***now res is:***\n");
    print_s(res);
    puts("*****************");
    if(size>=3)
    {
        printf("size>=3 \n");
        for(i=0;i<size_half;i++)
        {
            if(size_s(orig)>0)
            {
                elem=pop_s(orig);
                push_s(temp,elem);
            }
        }
        for(i=0;i<size_half;i++)
        {
            if(size_s(temp)>0)
            {
                elem=pop_s(temp);
                push_s(half,elem);
            }

        }
        printf("---orig and half:---\n");
        print_s(orig);
        puts("~~~");
        print_s(half);
        puts("----------");
        merge_sort(orig,size_orig,res);
        res=merge(orig,half);
        t=r;
        r=merge(res,t);
        res=r;
        merge_sort(half,size_half,res);
        puts("_______after rec r:_______\n");
        print_s(r);
        puts("__________________________");
    }else{
        printf("size=2 or 1\n");
        //if(size==2)
        //{
            //printf("size=2\n");
            ++bb;
            printf("\tbb=%d\n\n",bb);
            push_s(p,bb);
            puts("test stack");
            print_s(p);
            if(size_s(orig)>0)
            {
                elem=pop_s(orig);
                push_s(half,elem);
                printf("---orig and half:---\n");
                print_s(orig);
                puts("~~~~~~");
                print_s(half);
                puts("----------");
                res=merge(orig,half);
                t=r;
                r=merge(res,t);
                puts("============== r: ============");
                print_s(r);
                puts("==============================");
                //puts("res :\n");
                //print_s(res);
                /*if(top_s(orig)>=elem)
                {
                    push_s(orig,elem);
                }else{
                    if(size_s(orig)>0)
                    {
                        elem2=pop_s(orig);
                        push_s(orig,elem);
                        push_s(orig,elem2);
                        //print_s(orig);
                    }
                }*/
            }
        //}
    }
    printf("res:\n");
    res=r;
    print_s(r);
    //printf("end merge sort\n");
    return r;
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

int main()
{
    char c;
    int num;
    int f_size, s_size;
    Stack frst=create_s();
    Stack scnd=create_s();
    ///.......................................///

    printf("Enter size of first stack:\n");
    scanf("%d", &f_size);
    printf("Enter elements of first stack:\n");
    if(f_size>0)
    {
        for(int i=0;i<f_size;i++)
        {
            scanf("%d",&num);
            push_s(frst,num);
        }
    }else{
        printf("Wrong size of stack\n");
    }
    print_s(frst);
    //printf("size of 1 stack %d----------, %d\n",size_s(frst), frst->top);

    printf("Enter size of second stack:\n");
    scanf("%d", &s_size);
    printf("Enter elements of second stack:\n");
    if(s_size>0)
    {
        for(int i=0;i<s_size;i++)
        {
            scanf("%d",&num);
            push_s(scnd,num);
        }
    }else{
        printf("Wrong size of stack\n");
    }
    print_s(scnd);

    /*
    Stack a=create_s();
    a=merge(frst,scnd);
    puts("merged stack:\n");
    print_s(a);*/
    ///.......................................///

    //puts("---------------");
    //printf("size of 2 stack %d----------, %d\n",size_s(scnd), scnd->top);
    Stack_st res=create_st();
    Stack_st temp=create_st();
    //push_st(temp, frst);
    //push_st(temp,scnd);
    Stack tt=cat(frst, scnd);
    puts("~~~~~~~");
    print_s(tt);
    int el;
    Stack ell=create_s();
    while(tt->top>0)
    {
      //el=pop_s(tt);
      ell=create_s();
      push_s(ell,pop_s(tt));
      push_st(res,ell);
    }
    while(res->topst>0)
    {
      push_st(temp,pop_st(res));
    }
    //print_s(tt);
    //tt=pop_st(temp);
    //push_st(res,tt);
    //tt=pop_st(temp);
    //push_st(res,tt);
    printf("size of st_st=%d\n", size_st(temp));
    print_st(temp);

    Stack swap=create_s();
    Stack a=create_s();
    Stack b=create_s();
    a=pop_st(temp);
    b=pop_st(temp);
    swap=merge(a,b);
    push_st(res,swap);

    swap=create_s();
    a=create_s();
    b=create_s();
    a=pop_st(temp);
    b=pop_st(temp);
    swap=merge(a,b);
    push_st(res,swap);
    temp=create_st();
    while(res->topst>0)
    {
      push_st(temp,pop_st(res));
    }

    printf("first step\n");
    print_st(temp);

    swap=create_s();
    a=create_s();
    b=create_s();
    a=pop_st(temp);
    b=pop_st(temp);
    swap=merge(a,b);
    push_st(res,swap);
    temp=create_st();
    while(res->topst>0)
    {
      push_st(temp,pop_st(res));
    }

    printf("second step\n");
    print_st(temp);

/*
    printf("Enter size of stack:\n");
    scanf("%d", &f_size);
    printf("Enter elements of stack:\n");
    int i;
    if(f_size>0)
    {
        for(i=0;i<f_size;i++)
        {
            scanf("%d",&num);
            push_s(res,num);
        }
    }else{
        printf("Wrong size of stack\n");
    }
    print_s(res);
    //res=cat(frst,scnd);
    //printf("size of res is %d\n",size_s(res));
    puts("------------------------------------");
    int orsize=size_s(res);
    Stack tm=create_s();
    Stack end=create_s();
    tm=res;
    res=merge_sort(tm,orsize,end);
    puts("after merge sort end res:");
    print_s(res);
    puts("test stack:");
    print_s(p);
*/

    //int a,b,x,y,z=-1,j=1;

    /*while(frst!=NULL)
    {
        frst=pop_s(frst,&z);
        printf("%d: %d\n",j,z);
        ++j;
    }
    printf("\n");
    j=1;
    while(scnd!=NULL)
    {
        scnd=pop_s(scnd,&z);
        printf("%d: %d\n",j,z);
        ++j;
    }*/

    return 0;
}
