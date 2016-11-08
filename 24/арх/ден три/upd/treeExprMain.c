#include "stdio.h"
#include "stdlib.h"
#include "stack.h"
#include "functions.h"
#pragma warning(disable: 4996)

int main(int argc, char * argv[])
{
	char expr[128];
	int answer;
	struct tree* root = NULL;
	stack* stree = malloc(sizeof(stack));
	if (!stree) { printf(" ***Memory error!***"); return 0; }
	Create(stree);
	if(argc > 1) load_expr(root, argv[1]);
	print_menu();
	while(1)
	{
		printf(" Enter the menu number: ");
		scanf("%d", &answer);
		switch (answer)
		{
			case 0:
				print_menu();
				break;
			case 1:
				printf(" Enter expression: ");
				scanf("%s", expr);
				if(load_expr(stree, expr))
					root = make_tree(root, stree);
				break;
			case 2:
				printf(" ");
				if (root) print_expr(root, root->data->var);
				printf("\n\n");
				break;
			case 3:
				printf("\n");
				print_tree(root, 0);
				printf("\n");
				break;
			case 4:
				root = remove_fact(root);
				printf(" ***Successful***\n\n");
				break;
			case 5:
				system("cls");
				print_menu();
				break;
			case 6:
				return 0;
				break;
			default:
				printf(" ***Wrong key!***\n");
				break;
		}
	}
	return 0;
}
