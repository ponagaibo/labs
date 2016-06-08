#ifndef MY_VECT_H
#define MY_VECT_H

#define VECT_SIZE 20;
#define MULT 2;

struct vect{
  int size;
  int top;
  int* data;
  int first;
};
typedef struct vect* Vector;

Vector create_vect();
void delete_vect(Vector* v);
Vector resize_vect(Vector v);
int size_vect(Vector v);
void print_vect(Vector v);
void push_vect(Vector v, int el);
int top_vect(Vector v);
int pop_vect(Vector v);

#endif
