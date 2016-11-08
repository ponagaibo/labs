#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "tree.h"
#include "functions.h"
#pragma warning(disable: 4996)

tree* root;

int main(int argc, char * argv[])
{
	int count;
	root = NULL;

	if(argc > 1) root = create_random_tree(root, 10);
	print_menu();
	while(1)
	{
		printf(" Enter the menu number: ");
		scanf("%d", &count);
		switch (count)
		{
			case 0:
				print_menu();
				break;
			case 1:
				printf(" Enter node count: ");
				scanf("%d", &count);
				root = create_random_tree(root, count);
				break;
			case 2:
				printf(" Enter node value: ");
				scanf("%d", &count);
				root = add_node(root, root, count);
				printf("\n");
				break;
			case 3:
				printf("\n");
				print_tree(root, 0);
				printf("\n");
				break;
			case 4:
				printf(" Power tree: %d\n\n", count_pow(root));
				break;
			case 5:
				printf(" Enter node value: ");
				scanf("%d", &count);
				root = remove_node(root, count);
				break;
			case 6:
				root = remove_tree(root);
				printf(" ***Successful!***\n\n");
				break;
			case 7:
				system("cls");
				print_menu();
				break;
			case 8:
				return 0;
				break;
			default:
				printf("Wrong key!\n");
				break;
		}
	}
	return 0;
}
