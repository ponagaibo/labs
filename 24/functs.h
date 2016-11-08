#ifndef _functs_h_
#define _functs_h_
#include "my_stack.h"
int count, check, tree_size,st;
struct elem{
    int type;
    int value;
    char symb;
};
struct elem* Dejkstra(struct elem* part, struct elem* res);
int size_of_str(char* str);
int check_expr(char* str);
struct elem* parse(char* ch);
void print_pars(struct elem* orig);
#endif
