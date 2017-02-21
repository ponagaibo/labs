#ifndef _VECT_H
#define _VECT_H
#define VECT_SIZE 20;
#define MULT 2;
typedef unsigned long long ull;

struct TNode {
    int id;
    ull sum;
};
typedef struct TNode* TNode;

struct TVector {
    int size;
    int top;
    TNode data;
    int first;
};
typedef struct TVector* TVector;

TVector CreateVector();
void DeleteVector(TVector* v);
TVector ResizeVector(TVector v);
int SizeOfVector(TVector v);
void PrintVector(TVector v);
void PushVector(TVector v, int curID, ull curSum);
TNode TopVector(TVector v);
TNode PopVector(TVector v);
TNode FindNode(TVector v, int name);
#endif