#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "deq.h"

int main() {
    printf("It is a programm for linking with a shared library.\n");
    TNode* myDeque = NULL;
    Tmd5* myMd = malloc(sizeof(Tmd5));

    printf("\n1. Push front \"123abc456def7890123abc456def7890\", print deq:\n");
    strcpy(myMd->hash, "123abc456def7890123abc456def7890");
    myDeque = PushFront(myDeque, *myMd);
    PrintDeque(myDeque);

    printf("\n2. Push back  \"987def654abc3210987def654abc3210\", print deq:\n");
    strcpy(myMd->hash, "987def654abc3210987def654abc3210");
    myDeque = PushBack(myDeque, *myMd);
    PrintDeque(myDeque);

    printf("\n3. Push front \"a1b3c5d7e9f2a4b6c8d0e2f3a4b5c6d\", print deq:\n");
    strcpy(myMd->hash, "a1b3c5d7e9f2a4b6c8d0e2f3a4b5c6d");
    myDeque = PushFront(myDeque, *myMd);
    PrintDeque(myDeque);

    printf("\n4. Pop back, print deq:\n");
    myDeque = PopBack(myDeque);
    PrintDeque(myDeque);

    printf("\n5. Top back, print element:\n");
    myMd = TopFront(myDeque);
    if (myMd != NULL) printf("%s\n", myMd->hash);

    printf("\n6. Pop front, print deq:\n");
    myDeque = PopFront(myDeque);
    PrintDeque(myDeque);

    printf("\n7. Pop back, print deq:\n");
    myDeque = PopBack(myDeque);
    PrintDeque(myDeque);

    printf("\n8. Top front, print element:\n");
    myMd = TopFront(myDeque);
    if (myMd != NULL) printf("%s\n", myMd->hash);

    DeleteDeque(myDeque);
    return 0;
}