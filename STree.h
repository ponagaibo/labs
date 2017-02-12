#ifndef SUFF_TREE_H
#define SUFF_TREE_H
#include <string>
#include <iostream>

const int MAX_CHAR = 28;
 
struct TTreeNode {
    struct TTreeNode *child[MAX_CHAR];
    struct TTreeNode *suffLink;
    int start;
    int* end;
    int suffIndex;
};
typedef struct TTreeNode TNode;

std::string patt;
std::string text;
TNode* root = NULL;
TNode* lastNewNode = NULL;
TNode* curNode = NULL;
int curEdge = -1;
int curLength = 0;
int suffCount = 0;
int leafEnd = -1;
int* rootEnd = NULL;
int* splitEnd = NULL;
int patSize = -1;

#endif