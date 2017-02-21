#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vect.h"

int main() {
    TVector myVect = CreateVector();
    TNode el = (TNode)malloc(sizeof(struct TNode));
    PushVector(myVect, 13, 500);
    PushVector(myVect, 69, 1488);
    /*
    el->id = 228;
    el->sum = 300;
    PushVect(myVect, el);
    */
    PrintVector(myVect);
    int sz = SizeOfVector(myVect);
    printf("Vector size is %d\n", sz);
    el = FindNode(myVect, 66);
    if (el) printf("sum of found node: %llu\n", el->sum);
    else puts("Can not find this node.");
    return 0;
}