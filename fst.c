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

/*
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
*/

/*                     ~~~~ it works, don't delete ~~~~


void print_m(Vector index, Vector clmn, Vector value)
{
  //state_ind - 1, если есть следующая строка, иначе 0
  //state_cl - 1, если еще есть ненулевыt элементы в строке, иначе 0
  //begin_cl - номер столбца с первым ненулевым элементом строки
  //end_cl - номер столбца с последним ненулевым элементом строки
  //this_line-next_line - индексы стобцов с ненулевыми элементами данной строки
  int state_ind, state_cl, next_line, this_line;
  for(int i=0; i<lines; i++)
  {
    next_line=-1, state_ind=0, state_cl=1;
    //printf("index is %d\t", index->data[i]);
    if(index->data[i]==-1)
    {
      for(int j=0; j<columns; j++) printf("0 ");
      printf("\n");
    }else{
      this_line=index->data[i];
      for(int j=i+1; j<lines; j++)
      {
        if(index->data[j]!=-1)
        {
          next_line=index->data[j];
          state_ind=1;
        }
      }
      //printf("this line is %d, next line is %d, state ind is %d\n", this_line, next_line, state_ind);
      if(state_ind)
      {
        for(int j=1; j<=columns; j++)
        {
          if(clmn->data[this_line]==j && state_cl)
          {
            printf("%d ", value->data[this_line]);
            this_line++;
          }else printf("0 ");
          if(this_line==next_line) state_cl=0;
        }
        printf("\n");
      }else{
        for(int j=1; j<=columns; j++)
        {
          if(clmn->data[this_line]==j && state_cl)
          {
            printf("%d ", value->data[this_line]);
            this_line++;
          }else printf("0 ");
          if(clmn->data[this_line]==0) state_cl=0;
        }
        printf("\n");
      }
    }
  }
}
*/

void print_m(Vector index, Vector clmn, Vector value, int lines_m, int columns_m)
{
  int state_cl, next_line, this_line;
  for(int i=0; i<lines_m; i++)
  {
    next_line=-1, state_cl=1;
    //printf("index is %d\t", index->data[i]);
    if(index->data[i]==-1)
    {
      for(int j=0; j<columns_m; j++) printf("0 ");
      printf("\n");
    }else{
      this_line=index->data[i];
      for(int j=i+1; j<lines; j++)
      {
        if(index->data[j]!=-1)
        {
          next_line=index->data[j];
        }
      }
      //printf("this line is %d, next line is %d, state ind is %d\n", this_line, next_line, state_ind);
        for(int j=1; j<=columns_m; j++)
        {
          if(clmn->data[this_line]==j && state_cl)
          {
            printf("%d ", value->data[this_line]);
            this_line++;
          }else printf("0 ");
          if(this_line==next_line || clmn->data[this_line]==0) state_cl=0;
        }
        printf("\n");
    }
  }
}

void mult_vect(const Vector cl_vc, const Vector index, const Vector clmn, const Vector value, Vector* index_res, Vector* clmn_res, Vector* value_res)
{
  int this_line, next_line, state, el_m, el_v, el_res, ml, l=0;
  for(int i=0; i<lines; i++)
  {
    state=1, next_line=-1, el_res=0;
    if(index->data[i]==-1) push_vect(*index_res, -1);
    else{
      this_line=index->data[i];
      for(int j=i+1; j<lines; j++)
      {
        if(index->data[j]!=-1) next_line=index->data[j];
      }
      for(int j=1; j<=columns; j++)
      {
        if(clmn->data[this_line]==j && state)
        {
          el_m=value->data[this_line];
          el_v=cl_vc->data[j-1];
          ml=el_m * el_v;
          el_res+=ml;
          this_line++;
        }
        if(this_line==next_line || clmn->data[this_line]==0) state=0;
      }
      if(el_res!=0)
      {
        push_vect(*index_res, l);
        push_vect(*clmn_res, 1);
        push_vect(*value_res, el_res);
        l++;
      }else push_vect(*index_res, -1);
    }
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

  /*                  *** print entered matrix ***
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
  */
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
  puts("print matrix from vectors");
  print_m(index, clmn, value, lines, columns);
  printf("Enter column-vector, size %d x 1:\n", columns);
  Vector cl_vc=create_vect();
  int el;
  for(int i=0; i<columns; i++){
    scanf("%d", &el);
    push_vect(cl_vc, el);
  }
  print_vect(cl_vc);
  Vector index_res=create_vect();
  Vector clmn_res=create_vect();
  Vector value_res=create_vect();
  mult_vect(cl_vc, index, clmn, value, &index_res, &clmn_res, &value_res);
  printf("vector res of index ");
  print_vect(index_res);
  printf("vector res of columns ");
  print_vect(clmn_res);
  printf("vector res of values ");
  print_vect(value_res);
  puts("print res matrix from vectors");
  print_m(index_res, clmn_res, value_res, lines, 1);
  return 0;
}
