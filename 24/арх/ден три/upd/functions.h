#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct tree
{
	struct it* data;
	struct tree *l;
	struct tree *r;
};

void print_menu();
int load_expr(struct stack* stree, char* expr);
struct tree* make_tree(struct tree* root, struct stack* stree);
void print_tree(struct tree* root, int i);
struct tree* remove_fact(struct tree* root);
void print_expr(struct tree* root, int i);
#endif
