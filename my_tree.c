#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "my_stack.h"
#include "functs.h"
#include "my_tree.h"

struct tree* remove_tree(struct tree* root)
{
	if (root)
	{
		remove_tree(root->right);
		remove_tree(root->left);
		free(root);
	}
	return NULL;
}

struct tree* build_tree(struct elem* ar, int br){
  struct tree* res=malloc(sizeof(struct tree));
  if(cnt!=-1) {
    if(ar[cnt].type==0) {
      res->item.type=ar[cnt].type;
      res->item.value=ar[cnt].value;
      res->item.symb=ar[cnt].symb;
      res->bracket=br;
      cnt--;
      res->right=build_tree(ar,2);
      res->left=build_tree(ar,1);
    }else if (ar[cnt].type==1||ar[cnt].type==2){
      res->item.type=ar[cnt].type;
      res->item.value=ar[cnt].value;
      res->item.symb=ar[cnt].symb;
      res->bracket=br;
      cnt--;
    }
  }
  return res;
}

void print_tree(struct tree* root, int i)
{
	if (root)
	{
    print_tree(root->right, i+1);
		for(int k=0; k<=i; k++)
      printf("  ");
    if ((root->item.type==0)||(root->item.type==2))
    {
      printf("%c\n",root->item.symb);
    }else{
      printf("%d\n", root->item.value);
    }
		print_tree(root->left, i+1);
	}
}

void print_from_tree(struct tree* root)
{
  if(root->left) print_from_tree(root->left);

  if(root->item.type==1)
  {
    if(root->bracket==1)
    {
      printf("(%d", root->item.value);
      lvls++;
    }else if(root->bracket==2)
    {
      if(root->item.value<0) printf("(%d))", root->item.value);
      else printf("%d)",root->item.value);
      lvls--;
    }else printf("%d", root->item.value);
  }

  if(root->item.type==2)
  {
    if(root->bracket==1)
    {
      printf("(%c", root->item.symb);
      lvls++;
    }else if(root->bracket==2){
      printf("%c)", root->item.symb);
      lvls--;
    }else printf("%c", root->item.symb);
  }
  if(root->item.type==0) printf("%c", root->item.symb);

  if(root->right) print_from_tree(root->right);
}


void count_br(struct tree* root)
{
  if(root->left) count_br(root->left);

  if(root->item.type==1)
  {
    if(root->bracket==1) lvls++;
    else if(root->bracket==2) lvls--;
  }

  if(root->item.type==2)
  {
    if(root->bracket==1) lvls++;
    else if(root->bracket==2) lvls--;
  }
  if(root->right) count_br(root->right);
}
