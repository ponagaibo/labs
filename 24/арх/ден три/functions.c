#include "stdio.h"
#include "stdlib.h"
#include "tree.h"
#include "errno.h"
#include "functions.h"
#pragma warning(disable: 4996)

void line(int n, char lc[], char v[], char g[], char rc[])
{
	printf(lc);
	int i;
	for (i = 0; i < 35; i++)
	{
		if (i == n) printf(v);
		else printf(g);
	}
	printf(rc);
}

void print_menu()
{
	char menu[8][32] = {"Random tree", "Add node", "Print tree", "Count node(pow = value)",
		"Remove node", "Remove all", "Clear console", "Exit" };
	line(3, "\xC9", "\xCB", "\xCD", "\xBB\n");
	printf("\xBA 0 \xBA % -30s\xBA\n", "Print menu");
	int i;
	for (i = 0; i < 8; i++)
	{
		line(3, "\xCC", "\xCE", "\xCD", "\xB9\n");
		printf("\xBA %d \xBA % -30s\xBA\n", i+1, menu[i]);

	}
	line(3, "\xC8", "\xCA", "\xCD", "\xBC\n\n");
}

tree* create_random_tree(tree* root, int count)
{
	srand(time(0));
	for (; count > 0; count--)
		root = add_node(root, root, rand() % 4);
	printf(" ***Successful!***\n\n");
	return root;
}

tree* add_node(tree* root, tree* r, int key)
{
	if (!r)
	{
		r = (tree*)malloc(sizeof(tree));
		if (!r)
		{
			printf(" ***Memory error!***\n");
			exit(0);
		}
		r->l = NULL;
		r->r = NULL;
		r->value = key;
		if (!root) return r;
		if (key < root->value) root->l = r;
		else root->r = r;
		return r;
	}
	if (key < root->value)
		add_node(r, r->l, key);
	else
		add_node(r, r->r, key);
	return root;
}

void print_tree(tree* root, int i)
{
	if (root)
	{
		print_tree(root->r, i+1);
		printf(" %*s%d\n", 4*i," ",root->value);
		print_tree(root->l, i+1);
	}
}

int count_pow(tree* root)
{
	if (!root) return 0;
	int i = 1;
	while (root)
	{
		if ((!root->l && !root->r) && !i) return 0;
		if (root->l && root->r) return 2;
		if (root->l) root = root->l;
		else root = root->r;
	}
	return i;
}

tree* remove_node(tree* root, int key)
{
	tree *p, *p2;

	if (!root) return root;

	if (root->value == key)
	{
		if (root->l == root->r)
		{
			free(root);
			return NULL;
		}
		else if (root->l == NULL)
		{
			p = root->r;
			free(root);
			return p;
		}
		else if (root->r == NULL)
		{
			p = root->l;
			free(root);
			return p;
		}
		else
		{
			p2 = root->r;
			p = root->r;
			while (p->l) p = p->l;
			p->l = root->l;
			free(root);
			return p2;
		}
	}
	if (key < root->value) root->l = remove_node(root->l, key);
	else  root->r = remove_node(root->r, key);
	return root;
}

tree* remove_tree(tree* root)
{
	tree* p;
	if (!root)
		return root;
	if (root->l == root->r)
		free(root);
	else if (root->l = NULL)
	{
		p = root->r;
		free(root);
		remove_tree(p);
	}
	else
	{
		p = root->l;
		free(root);
		remove_tree(p);
	}
}
