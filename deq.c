#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "deq.h"

TNode* PushFront(TNode* dq, Tmd5 data) {
    TNode* tmp = (TNode*)malloc(sizeof(TNode));
    tmp->data = (Tmd5*)malloc(sizeof(Tmd5));
    strcpy(tmp->data->hash, data.hash);
    tmp->next = dq;
    return tmp;
}

TNode* PushBack(TNode* dq, Tmd5 data) {
    TNode* tmp = (TNode*)malloc(sizeof(TNode));
    tmp->data = (Tmd5*)malloc(sizeof(Tmd5));
    strcpy(tmp->data->hash, data.hash);
    TNode* last = dq;
    while (last->next != NULL) last = last->next;
    last->next = tmp;
    return dq;
}

Tmd5* TopFront(TNode* dq) {
    if (DequeSize(dq) == 0) {
        printf("Deque is empty!\n");
        return NULL;
    }
    return dq->data;
}

Tmd5* TopBack(TNode* dq) {
    if (DequeSize(dq) == 0) {
        printf("Deque is empty!\n");
        return NULL;
    }
    TNode* last = dq;
    while (last->next != NULL) last = last->next;
    return last->data;
}

void PrintDeque(TNode* dq) {
    if (DequeSize(dq) == 0) {
        printf("Deque is empty!\n");
        return;
    }
    TNode* tmp = dq;
    while (tmp != NULL) {
        printf("%s\n", tmp->data->hash);
        tmp = tmp->next;
    }
}

int DequeSize(TNode* dq) {
    TNode* tmp = dq;
    int sz = 0;
    while (tmp != NULL) {
        sz++;
        tmp = tmp->next;
    }
    return sz;
}

TNode* PopFront(TNode* dq) {
    if (DequeSize(dq) == 0) {
        printf("Deque is empty!\n");
        return NULL;
    }
    TNode* tmp = dq->next;
    free(dq);
    return tmp;
}

TNode* PopBack(TNode* dq) {
    if (DequeSize(dq) == 0) {
        printf("Deque is empty!\n");
        return NULL;
    }
    if (DequeSize(dq) == 1) {
        free(dq);
        return NULL;
    }
    TNode* last = dq;
    while (last->next->next != NULL) last = last->next;
    free(last->next);
    last->next = NULL;
    return dq;
}

TNode* DeleteDeque(TNode* dq) {
    TNode* tmp;
    while (dq != NULL) {
        tmp = dq;
        dq = dq->next;
        free(dq);
    }
    return NULL;
}

int CheckMD5(Tmd5* num) {
    int sz;
    int len = strlen(num->hash);
    char c;
    for (sz = 0; sz < len; sz++) {
        c = num->hash[sz];
        if (c >= 48 && c <= 57 || c >= 65 && c <= 70 || c >= 97 && c <= 102) {
            continue;
        } else {
            return 0;
        }
    }
    return 1;
}
