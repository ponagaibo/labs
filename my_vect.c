#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_vect.h"

Vector create_vect() {
  Vector out=NULL;
  out=malloc(sizeof(struct vect));
  out->size=VECT_SIZE;
  out->top=0;
  out->first=0;
  out->data=malloc(out->size*sizeof(int));
  return out;
}

void delete_vect(Vector* v) {
  free((*v)->data);
  free(*v);
  *v=NULL;
}

Vector resize_vect(Vector v) {
  v->size*=MULT;
  v->data=realloc(v->data,v->size*sizeof(int));
}

int size_vect(Vector v) {
  return (v->top)-(v->first);
}

void print_vect(Vector v) {
  if(size_vect(v)) {
    for(int i=v->first;i<v->top;i++) printf("%d ",v->data[i]);
    puts("\n");
  }else puts("Vector is empty.\n");
}

void push_vect(Vector v, int el) {
  if(v->top>=(v->size)-1) resize_vect(v);
  v->data[v->top]=el;
  v->top++;
}

int top_vect(Vector v) {
  if (size_vect(v)) return v->data[v->first];
  else puts("Vector is empty.");
}

int pop_vect(Vector v) {
  if(size_vect(v)) {
    el=v->data[v->first];
    v->first++;
    return el;
  }
}
