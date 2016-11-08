#ifndef __tree_h__
#define __tree_h__

typedef struct
{
	int value;
	struct tree *l;
    struct tree *r;
} tree;

#endif
