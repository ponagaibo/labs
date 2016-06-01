#include <stdio.h>
#define STACK_SIZE 30
#define MULT 2

///.................................STACK..................................///

struct node_s
{
    int *data;
    int size;
    int top;
};

typedef struct node_s Node_s;
typedef struct node_s* Stack;

Stack create_s() {
    Stack out=NULL;
    out=malloc(sizeof(Node_s));
    out->size=STACK_SIZE;
    out->data=malloc(out->size*sizeof(int));
    out->top=0;
    return out;
}

void delete_s(Stack *s) {
    free((*s)->data);
    free(*s);
    *s=NULL;
}

void resize(Stack s) {
    s->size*=MULT;
    s->data=realloc(s->data, s->size*sizeof(int));
}

int top_s(Stack s)
{
    if(s->top>0) return s->data[s->top-1];
    else{
        printf("Error! Stack is empty.\n");
        return -111;
    }
}

void push_s(Stack s, int c)
{
    if(s->top>=s->size)
    {
        resize(s);
    }
    s->data[s->top]=c;
    s->top++;
}

int pop_s(Stack s)
{
    if(s->top>0)
    {
        s->top--;
        return s->data[s->top];
    }else{
        printf("Error! Stack is empty.\n");
        return -111;
    }
}

int size_s(Stack s)
{
    return s->top;
}

void print_s(Stack s)
{
    int i=0;
    for(i=(s->top)-1;i>=0;i--)
    {
        printf("%d\n",s->data[i]);
    }
}

//........................................................................//

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
    while((s->top)!=0&&(f->top)!=0)
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
    if((s->top)!=0)
    {
        //printf("s isnt null\n");
        elem=pop_s(s);
        temp[i]=elem;
        i++;
    }
    if((f->top)!=0)
    {
        //printf("f isnt null\n");
        elem=pop_s(f);
        temp[i]=elem;
        i++;
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

Stack merge_sort(Stack orig, int size, Stack res)
{
    printf("in merge sort\n");
    Stack half=create_s();
    Stack temp=create_s();
    Stack temp2=create_s();
    int size_half=size*0.5;
    int size_orig=size-size_half;
    int i,elem,elem2;
    printf("size=%d, size half=%d, size orig=%d\norig:\n",size, size_half, size_orig);
    print_s(orig);
    if(size>=3)
    {
        //printf("size>=3 \n");
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
        printf("orig and half:\n");
        print_s(orig);
        puts("~~~");
        print_s(half);
        puts("----------");
        merge_sort(orig,size_orig,res);
        merge_sort(half,size_half,res);
        res=merge(orig,half);
        print_s(res);
    }else{
        printf("size=2 or 1\n");
        //if(size==2)
        //{
            //printf("size=2\n");
            if(size_s(orig)>0)
            {
                elem=pop_s(orig);
                push_s(half,elem);
                printf("orig and half:\n");
                print_s(orig);
                puts("~~~~~~");
                print_s(half);
                res=merge(orig,half);
                puts("res :\n");
                print_s(res);
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
    print_s(res);
    printf("end merge sort\n");
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

int main()
{
    char c;
    int num;
    int f_size, s_size;
    Stack frst=create_s();
    Stack scnd=create_s();
    ///.......................................///
    /*printf("Enter size of first stack:\n");
    scanf("%d", &f_size);
    printf("Enter elements of first stack:\n");
    int i;
    if(f_size>0)
    {
        for(i=0;i<f_size;i++)
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
        for(i=0;i<s_size;i++)
        {
            scanf("%d",&num);
            push_s(scnd,num);
        }
    }else{
        printf("Wrong size of stack\n");
    }
    print_s(scnd);*/
    ///.......................................///
    //puts("---------------");
    //printf("size of 2 stack %d----------, %d\n",size_s(scnd), scnd->top);
    Stack res=create_s();
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
    puts("end res:\n");
    print_s(res);
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
