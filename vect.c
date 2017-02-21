#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vect.h"

TVector CreateVector() {
    TVector out = NULL;
    out = malloc(sizeof(struct TVector));
    out->size = VECT_SIZE;
    out->top = 0;
    out->first = 0;
    out->data = (TNode)malloc(out->size * sizeof(struct TNode));
    return out;
}

void DeleteVector(TVector* v) {
    if (v == NULL) return;
    free((*v)->data);
    free(*v);
    *v = NULL;
}

TVector ResizeVector(TVector v) {
    v->size *= MULT;
    v->data = realloc(v->data, v->size * sizeof(struct TNode));
}

void PrintVector(TVector v) {
    if (SizeOfVector(v)) {
        int i;
        for (i = v->first; i < v->top; i++) printf("id: %d\tsum: %llu\n", v->data[i].id, v->data[i].sum);
    } else printf("Vector is empty.\n");
}

int SizeOfVector(TVector v) {
    return ((v->top) - (v->first));
}

void PushVector(TVector v, int curID, ull curSum) {
    if (v->top >= (v->size) - 1) ResizeVector(v);
    v->data[v->top].id = curID;
    v->data[v->top].sum = curSum;
    v->top++;
}

TNode TopVector(TVector v) {
    if (SizeOfVector(v)) return &(v->data[v->first]);
    else printf("Vector is empty.\n");
}

TNode PopVector(TVector v) {
    if (SizeOfVector(v)) {
        TNode el;
        el = &(v->data[v->first]);
        v->first++;
        return el;
    } else printf("Vector is empty.\n");
}

TNode FindNode(TVector v, int name) {
    if (SizeOfVector(v)) {
        int i;
        for (i = v->first; i < v->top; i++)
            if (v->data[i].id == name)
                return &v->data[i];
    }
    return NULL;
}