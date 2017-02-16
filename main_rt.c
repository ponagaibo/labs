#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "deq.h"

int main() {
    printf("It is a programm for loading a shared library at runtime.\n");
    void* handle = dlopen("./libdeq.so", RTLD_LAZY);
    if (handle == NULL) {
        printf("Can not open library.\n");
        return 1;
    }
    void (*PrintDeque)(TNode*) = dlsym(handle,"PrintDeque");
    TNode* myDeque = NULL;
    Tmd5* myMd = malloc(sizeof(Tmd5));

    TNode* (*PushF)(TNode*, Tmd5) = dlsym(handle,"PushFront");
    printf("\n1. Push front \"123abc456def7890123abc456def7890\", print deq:\n");
    strcpy(myMd->hash, "123abc456def7890123abc456def7890");
    myDeque = (*PushF)(myDeque, *myMd);
    PrintDeque(myDeque);

    TNode* (*PushB)(TNode*, Tmd5) = dlsym(handle,"PushBack");
    printf("\n2. Push back  \"987def654abc3210987def654abc3210\", print deq:\n");
    strcpy(myMd->hash, "987def654abc3210987def654abc3210");
    myDeque = (*PushB)(myDeque, *myMd);
    PrintDeque(myDeque);

    printf("\n3. Push front \"a1b3c5d7e9f2a4b6c8d0e2f3a4b5c6d\", print deq:\n");
    strcpy(myMd->hash, "a1b3c5d7e9f2a4b6c8d0e2f3a4b5c6d");
    myDeque = (*PushF)(myDeque, *myMd);
    PrintDeque(myDeque);

    TNode* (*PopB)(TNode*) = dlsym(handle,"PopBack");
    printf("\n4. Pop back, print deq:\n");
    myDeque = (*PopB)(myDeque);
    PrintDeque(myDeque);

    Tmd5* (*TopB)(TNode*) = dlsym(handle,"TopBack");
    printf("\n5. Top back, print element:\n");
    myMd = (*TopB)(myDeque);
    if (myMd != NULL) printf("%s\n", myMd->hash);

    TNode* (*PopF)(TNode*) = dlsym(handle,"PopFront");
    printf("\n6. Pop front, print deq:\n");
    myDeque = (*PopF)(myDeque);
    PrintDeque(myDeque);

    printf("\n7. Pop back, print deq:\n");
    myDeque = (*PopB)(myDeque);
    PrintDeque(myDeque);

    Tmd5* (*TopF)(TNode*) = dlsym(handle,"TopFront");
    printf("\n8. Top front, print element:\n");
    myMd = (*TopF)(myDeque);
    if (myMd != NULL) printf("%s\n", myMd->hash);
    
    TNode* (*Del)(TNode*) = dlsym(handle,"DeleteDeque");
    (*Del)(myDeque);
    dlclose(handle);
    return 0;
}