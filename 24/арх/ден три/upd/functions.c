#include "stdio.h"
#include "stdlib.h"
#include "stack.h"
#include "functions.h"
#pragma warning(disable: 4996)

void line(int n, char lc[], char v[], char g[], char rc[])
{
	printf(lc);
	for (int i = 0; i < 35; i++)
	{
		if (i == n) printf(v);
		else printf(g);
	}
	printf(rc);
}

void print_menu()
{
	char menu[6][32] = {"Enter expression", "Print expression" , "Print tree", "Remove divider equal 1",
						"Clear console", "Exit" };
	line(3, "\xC9", "\xCB", "\xCD", "\xBB\n");
	printf("\xBA 0 \xBA % -30s\xBA\n", "Print menu");
	for (int i = 0; i < 6; i++)
	{
		line(3, "\xCC", "\xCE", "\xCD", "\xB9\n");
		printf("\xBA %d \xBA % -30s\xBA\n", i+1, menu[i]);

	}
	line(3, "\xC8", "\xCA", "\xCD", "\xBC\n\n");
}

int isNum(char c)
{
	if (c >= '0' && c <= '9') return 1;
	return 0;
}

int isSign(char c)
{
	if (c == '^' || c == '/' || c == '*' || c == '-' || c == '+') return 1;
	return 0;
}

int isChar(char c)
{
	if (c <= 'z' && c >= 'a') return 1;
	return 0;
}

int prior(char c)
{
	switch (c)
	{
		case '^':
			return 3;
			break;
		case '*': case '/':
			return 2;
			break;
		case '-': case '+':
			return 1;
		case '(':
			return 0;
	}
}

struct tree* remove_tree(struct tree* root)
{
	if (root)
	{
		remove_tree(root->l);
		remove_tree(root->r);
		free(root->data);
		free(root);
	}
	return NULL;
}

int load_expr(stack* stree, char* expr)
{
	struct it* s = NULL;
	char prev = '(';
	stack* st = malloc(sizeof(stack));
	if (!st) { printf(" ***Memory error!***"); return 0; }
	Create(st);
	if (!Empty(stree)) Destroy(stree);
	for (; *expr != '\0' && *expr != -52; expr++)
	{
		if (isChar(*expr))
		{
			if (prev == 'c' || prev == ')' || prev == 'i'){	printf(" ***Wrong expression!***\n\n"); return 0; }
			s = malloc(sizeof(struct it));
			if (!s) { printf(" ***Memory error!***"); return 0; }
			s->cod = 0;
			s->var = *expr;
			Push(stree, s);
			s = NULL;
			prev = 'c';
		}
		else if (isNum(*expr))
		{
			if (prev == 'c' || prev == ')' || prev == 'i') { printf(" ***Wrong expression!***\n\n"); return 0; }
			s = malloc(sizeof(struct it));
			if (!s) { printf(" ***Memory error!***"); return 0; }
			s->cod = 1;
			s->val = (int)(*expr - '0');
			expr++;
			while (isNum(*expr))
			{
				s->val = s->val * 10 + (int)(*expr - '0');
				expr++;
			}
			Push(stree, s);
			s = NULL;
			expr--;
			prev = 'i';
		}
		else if (*expr == '(')
		{
			if (prev == 'c' || prev == ')' || prev == 'i') { printf(" ***Wrong expressions!***\n\n"); return 0; }
			s = malloc(sizeof(struct it));
			if (!s) { printf(" ***Memory error!***"); return 0; }
			s->cod = 0;
			s->var = *expr;
			Push(st, s);
			s = NULL;
			prev = '(';
		}

		else if (*expr == ')')
		{
			if (prev == '(' || prev == 'o') { printf(" ***Wrong expressions!***\n\n"); return 0; }
			if (Empty(st))
			{
				printf(" ***Missed '(' ***\n\n");
				return 0;
			}
			s = Top(st);
			while (s->var != '(')
			{
				Push(stree, s);
				Pop(st);
				s = Top(st);
				if (Empty(st))
				{
					printf(" ***Missed '(' ***\n\n");
					return 0;
				}
			}
			Pop(st);
			prev = ')';
		}
		else if (isSign)
		{
			if (prev == 'o' || prev == '(') { printf(" ***Wrong expressions!***\n\n"); return 0; }
			s = Top(st);
			while (!Empty(st) && prior(*expr) <= prior(s->var))
			{
				Push(stree, s);
				Pop(st);
				s = Top(st);
			}
			s = malloc(sizeof(struct it));
			if (!s) { printf(" ***Memory error!***"); return 0; }
			s->cod = 0;
			s->var = *expr;
			Push(st, s);
			s = NULL;
			prev = 'o';
		}
		else
		{
			printf(" ***Unknown symbol: %s ***\n\n", *expr);
			return 0;
		}
	}
	while (!Empty(st))
	{
		s = Top(st);
		if (s->var == '(')
		{
			printf(" ***Missed ')' ***\n\n");
			return 0;
		}
		Push(stree, Top(st));
		Pop(st);
	}
	printf(" ***Successful***\n\n");
	return 1;
}

int parOpen = 0;
int parClose = 0;

void print_expr(struct tree* root, char c)
{
	if (root)
	{
		char c2;
		if (isSign(root->data->var))
		{
			c2 = root->data->var;
			if (prior(c) > prior(c2) )
			{
				parOpen++;
				parClose++;
			}
			print_expr(root->l, c2);
			printf("%c", c2);
			print_expr(root->r, c2);
			if (prior(c) > prior(c2) )
			{
				printf(")");
				parClose--;
			}
		}
		else
		{
			for (parOpen; parOpen>0; parOpen--)
				printf("(");
			if (root->data->cod)
				printf("%d", root->data->val);
			else
				printf("%c", root->data->var);
		}
	}
}


void print_tree(struct tree* root, int i)
{
	if (root)
	{
		print_tree(root->r, i+1);
		for (int k = 0; k <= i; k++)
			printf("  ");
		if(root->data->cod)
			printf("%d\n", root->data->val);
		else
			printf("%c\n", root->data->var);
		print_tree(root->l, i+1);
	}
}

struct tree* make_tree(struct tree* root, struct stack* stree)
{
	struct it *s = NULL;
	if (root) root = remove_tree(root);
	if (!root)
	{
		root = malloc(sizeof(struct tree));
		if (!root) { printf(" ***Memory error!***"); return 0; }
		root->l = NULL;
		root->r = NULL;
		s = Top(stree);
		if (isSign(s->var))
		{
			root->data = Top(stree);
			Pop(stree);
			root->r = make_tree(root->r, stree);
			root->l = make_tree(root->l, stree);
		}
		else
		{
			root->data = Top(stree);
			Pop(stree);
		}
	}
	return root;
}

struct tree* remove_fact(struct tree* root)
{
	struct tree* root2;
	if (root)
	{
		root->r = remove_fact(root->r);
		if (root->data->var == '/' && (root->r->data->val == 1))
		{
			root2 = root->l;
			free(root->r->data);
			free(root->r);
			free(root->data);
			free(root);
			return root2;

		}
		root->l = remove_fact(root->l);
	}
	return root;
}
