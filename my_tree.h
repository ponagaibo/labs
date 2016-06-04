#ifndef _my_tree_h_
#define _my_tree_h_

#include "my_stack.h"
#include "functs.h"

int cnt,amount,lvls;

struct tree{
  struct elem item;
  struct tree* right;
  struct tree* left;
  int bracket;
};

struct tree* remove_tree(struct tree* root);
struct tree* build_tree(struct elem* ar, int br);
void print_tree(struct tree* root, int i);
void print_from_tree(struct tree* root);
void count_br(struct tree* root);

#endif
