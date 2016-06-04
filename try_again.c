#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "my_stack.h"
#include "functs.h"
#include "my_tree.h"
#define N 100

int count_op(struct tree* root)
{
  if(root)
  {
    if(root->item.type==0)  amount++;
    count_op(root->right);
    count_op(root->left);
  }
  return amount;
}

int main()
{
    cnt=0,amount=0;
    lvls=0;
    int i=0, k, b, j=0,a=0;
    char ch[N],res[N];
    for(i=0;i<N;i++){
        ch[i]=NULL;
    }
    printf("Enter expression:\n");
    scanf("%s",ch);
    i=0;
    struct elem *orig;
    struct elem *ress;
    orig=malloc(100*sizeof(struct elem));
    ress=malloc(100*sizeof(struct elem));
    orig=parse(ch);
    //print_pars(orig);
    ress=Dejkstra(orig,ress);
    puts("print postfix;");
    print_pars(ress);

    struct tree* T=NULL;
    T=malloc(sizeof(struct tree));
    T->right=NULL;
    T->left=NULL;
    T->right=malloc(sizeof(struct tree));
    T->left=malloc(sizeof(struct tree));

    cnt=count-1;
    struct tree* tr=NULL;
    tr=malloc(sizeof(struct tree));
    tr->right=NULL;
    tr->left=NULL;

    tr=build_tree(ress,0);
    puts("print tree:");
    print_tree(tr,0);

    puts("print from tree");
    count_br(tr);
    if(lvls<0)
    {
      for(int i=0;i>lvls;i--)
      printf("(");
    }
    lvls=0;
    print_from_tree(tr);

    if(lvls>0)
    {
      for(int i=0;i<lvls;i++)
      printf(")");
    }

    int op=0;
    op=count_op(tr);
    printf("\namount of operations=%d\n", op);

    return 0;
}
