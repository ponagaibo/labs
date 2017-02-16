#ifndef _DEQ_H_
#define _DEQ_H_

typedef struct Tmd5 {
    char hash[33];
} Tmd5;

struct node {
    Tmd5* data;
    struct node* next;
};

typedef struct node TNode;

TNode* PushFront(TNode* dq, Tmd5 data);
TNode* PushBack(TNode* dq, Tmd5 data);
Tmd5* TopFront(TNode* dq);
Tmd5* TopBack(TNode* dq);
void PrintDeque(TNode* dq);
int DequeSize(TNode* dq);
TNode* PopFront(TNode* dq);
TNode* PopBack(TNode* dq);
TNode* DeleteDeque(TNode* dq);
int CheckMD5(Tmd5* num);

#endif