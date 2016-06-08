#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"my_stack.h"
#include"stack_s.h"
#include <math.h>

Stack merge(Stack f, Stack s);
Stack merge_sort(Stack stck);

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
