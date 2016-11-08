#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void print_menu();
tree* create_random_tree(tree* root, int count);
tree* add_node(tree* root, tree* r, int key);
void print_tree(tree* root, int i);
int count_pow(tree* root);
tree* remove_node(tree* root, int key);
tree* remove_tree(tree* root);
#endif
