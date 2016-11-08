#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_vect.h"

int count_cv=0;
int lines, columns;

void interpret(Vector index, Vector clmn, Vector value, FILE* fo) {
  int elem, state=1;
  if((fo=fopen("matr.txt","r")) == NULL) printf("Error! Can not open file.\n");
  for(int i=0;i<lines;i++) {
    for(int j=0;j<columns;j++) {
      fscanf(fo, "%d", &elem);
      if(elem!=0) {
        if (state) { push_vect(index, count_cv); state=0; }
        push_vect(clmn, j+1);
        push_vect(value, elem);
        count_cv++;
      }
    }
    if(state) push_vect(index, -1);
    state=1;
  }
  push_vect(clmn, 0);
  fclose(fo);
}

void print_m(Vector index, Vector clmn, Vector value, int lines_m, int columns_m) {
  int state_cl, next_line, this_line;
  for(int i=0; i<lines_m; i++) {
    next_line=-1, state_cl=1;
    if(index->data[i]==-1) {
      for(int j=0; j<columns_m; j++) printf("0 ");
      printf("\n");
    } else {
      this_line=index->data[i];
      for(int j=i+1; j<lines_m; j++) {
        if(index->data[j]!=-1) next_line=index->data[j];
      }
        for(int j=1; j<=columns_m; j++) {
          if(clmn->data[this_line]==j && state_cl) {
            printf("%d ", value->data[this_line]);
            this_line++;
          }else printf("0 ");
          if(this_line==next_line || clmn->data[this_line]==0) state_cl=0;
        }
        printf("\n");
    }
  }
}

int mult_vect(const Vector cl_vc, const Vector index, const Vector clmn, const Vector value, Vector* index_res, Vector* clmn_res, Vector* value_res) {
  int this_line, next_line, state, el_m, el_v, el_res, ml, l=0;
  for(int i=0; i<lines; i++) {
    state=1, next_line=-1, el_res=0;
    if(index->data[i]==-1) push_vect(*index_res, -1);
    else {
      this_line=index->data[i];
      for(int j=i+1; j<lines; j++) {
        if(index->data[j]!=-1) next_line=index->data[j];
      }
      for(int j=1; j<=columns; j++) {
        if(clmn->data[this_line]==j && state) {
          el_m=value->data[this_line];
          el_v=cl_vc->data[j-1];
          ml=el_m * el_v;
          el_res+=ml;
          this_line++;
        }
        if(this_line==next_line || clmn->data[this_line]==0) state=0;
      }
      if(el_res!=0) {
        push_vect(*index_res, l);
        push_vect(*clmn_res, 1);
        push_vect(*value_res, el_res);
        l++;
      }else push_vect(*index_res, -1);
    }
  }
  push_vect(*clmn_res, 0);
  return l;
}

int main()
{
  int elem;
  FILE* fo;
  fo=fopen("matr.txt","wb");
  if(fo==0) printf("Error! Can not open file.\n");
  puts("Enter size of matrix:\nNumber of lines:");
  scanf("%d", &lines);
  puts("Number of columns:");
  scanf("%d", &columns);
  if(lines && columns) {
    puts("Enter elements of matrix:");
    for(int i=0;i<lines;i++) {
      for(int j=0;j<columns;j++) {
        fscanf(stdin, "%d", &elem);
        fprintf(fo, "%d", elem);
        fprintf(fo, " ");
      }
      fprintf(fo, "\n");
    }
    fclose(fo);
    if((fo=fopen("matr.txt","r")) == NULL) printf("Error! Can not open file.\n");
    printf("\n");
    puts("Entered matrix:");
    for(int i=0;i<lines;i++) {
      for(int j=0;j<columns;j++) {
        fscanf(fo, "%d", &elem);
        fprintf(stdout, "%d", elem);
        fprintf(stdout, " ");
      }
      fprintf(stdout, "\n");
    }
    fclose(fo);
    printf("\n");
    Vector index=create_vect();
    Vector clmn=create_vect();
    Vector value=create_vect();
    interpret(index, clmn, value, fo);
    printf("Vector of indexes: ");
    print_vect(index);
    printf("Vector of columns: ");
    print_vect(clmn);
    printf("Vector of values: ");
    print_vect(value);
    puts("Print matrix from vectors: ");
    print_m(index, clmn, value, lines, columns);
    printf("Enter column-vector, size %d x 1:\n", columns);
    Vector cl_vc=create_vect();
    for(int i=0; i<columns; i++) {
      scanf("%d", &elem);
      push_vect(cl_vc, elem);
    }
    printf("Column-vector: ");
    print_vect(cl_vc);
    Vector index_res=create_vect();
    Vector clmn_res=create_vect();
    Vector value_res=create_vect();
    elem=mult_vect(cl_vc, index, clmn, value, &index_res, &clmn_res, &value_res);
    printf("Result vector of index: ");
    print_vect(index_res);
    printf("Result vector of columns: ");
    print_vect(clmn_res);
    printf("Result vector of values: ");
    print_vect(value_res);
    puts("Print result matrix from vectors: ");
    print_m(index_res, clmn_res, value_res, lines, 1);
    printf("Number of nonzero elements: %d\n",elem);
  } else printf("Wrong size of matrix.\n");
  return 0;
}
