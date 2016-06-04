#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_vect.h"

int count_cv=0;
int lines, columns;

void interpret(Vector index, Vector clmn, Vector value, FILE* fo)
{
  extern int count_cv, lines, columns;
  int elem;
  int state=1;
  if((fo=fopen("matr.txt","r")) == NULL) {
    printf("Error! Can not open file.\n");
    exit(1);
  }
  for(int i=0;i<lines;i++)
  {
    for(int j=0;j<columns;j++)
    {
      fscanf(fo, "%d", &elem);
      if(elem!=0)
      {
        if (state)
        {
          (index)->data[i]=count_cv;
          index->top++;
          state=0;
        }
        (clmn)->data[count_cv]=j+1;
        clmn->top++;
        (value)->data[count_cv]=elem;
        value->top++;
        count_cv++;
      }
    }
    if(state)
    {
      (index)->data[i]=-1;
      index->top++;
    }
    state=1;
  }
  (clmn)->data[count_cv+1]=0;
  clmn->top++;
  fclose(fo);
}

void print_m(Vector index, Vector clmn, Vector value)
{
  int elem, next, state, l;
  next=-1;
  state=1;
  int t=0;
  for(int i=0; i<columns; i++)
  {
    state=1;
    //while(t!=lines)
    //{
      if(index->data[i]==-1)
      {
        //printf("index is -1\n");
        for(int j=0; j<columns; j++) printf("0 ");
        printf("\n");
      }else{
        //printf("index is not -1\n");
        elem=index->data[i];
        for(int k=i+1; k<columns; k++)
        {
          if(index->data[k]!=-1&&state==1)//state - до конца строки все -1
          {
            next=index->data[k];
            state=0;
          }
        }
        //printf("state=%d, elem=%d, next=%d\n",state, elem, next);
        if(state)
        {
          l=elem;
          for(int num=1; num<=columns; num++)
          {
            //printf("\n\tnum=%d, columns=%d, clmn->data[l]=%d\n", num, columns, clmn->data[l]);
            if(clmn->data[l]==num)
            {
              printf("%d ",value->data[l]);
              l++;
            }else printf("0 ");
          }
          printf("\n");
        }else{
          l=elem;
          for(int num=1; num<=columns; num++)
          {
              if(clmn->data[l]==num&&l!=next)
              {
                printf("%d ",value->data[l]);
                l++;
              }else{
                printf("0 ");
              }
          }
          printf("\n");
        }
      }
      //t++;
    //}
  }
}


int main()
{
  int elem;
  FILE* fo;
  ///..................test file...............///
  fo=fopen("matr.txt","wb");
  if(fo==0) {
    printf("Error! Can not open file.\n");
  }
  puts("Enter size of matrix:\nNumber of lines:\n");
  scanf("%d", &lines);
  puts("Number of column:\n");
  scanf("%d", &columns);
  puts("Enter elements of matrix:\n");

  for(int i=0;i<lines;i++)
  {
    for(int j=0;j<columns;j++)
    {
      fscanf(stdin, "%d", &elem);
      fprintf(fo, "%d", elem);
      fprintf(fo, " ");
    }
    fprintf(fo, "\n");
  }
  fclose(fo);
  if((fo=fopen("matr.txt","r")) == NULL) {
    printf("Error! Can not open file.\n");
  }
  printf("\n");
  for(int i=0;i<lines;i++)
  {
    for(int j=0;j<columns;j++)
    {
      fscanf(fo, "%d", &elem);
      fprintf(stdout, "%d", elem);
      fprintf(stdout, " ");
    }
    fprintf(stdout, "\n");
  }
  fclose(fo);
  printf("\n");
  ///.........................................///
  Vector index=create_vect();
  Vector clmn=create_vect();
  Vector value=create_vect();
  interpret(index, clmn, value, fo);
  printf("vector of index ");
  print_vect(index);
  printf("vector of columns ");
  print_vect(clmn);
  printf("vector of values ");
  print_vect(value);
  //puts("print matrix from vectors");
  //print_m(index, clmn, value);

  return 0;
}
