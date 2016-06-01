#include<stdio.h>
int main()
{
  int lines, columns;
  int elem;
  FILE* fo;
  fo=fopen("matr.txt","wb");
  if(fo==0) {
    printf("Error! Can not open file\n");
  }
  puts("Enter size of matrix:\nNumber of lines:\n");
  scanf("%d", &lines);
  puts("Number of column:\n");
  scanf("%d", &columns);
  puts("Enter elements of matrix:\n");
  int index[lines];
  
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
    printf("Error! Can not open file\n");
  }
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
  return 0;
}
