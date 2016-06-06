#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define KEY_SIZE 8
#define STR_SIZE 60
#define PIC_SIZE 15

typedef struct el{
  char key[KEY_SIZE];
  char str_pic[STR_SIZE];
} elem;

/*
struct elem* create_elem()
{
  struct elem* out = NULL;
  out=malloc(PIC_SIZE*sizeof(struct elem));
  printf("size out=%d\n", sizeof(out));
  for (int i=0; i<PIC_SIZE; i++)
  {
    out[i].key = malloc(KEY_SIZE*sizeof(char));
    out[i].str_pic = malloc(STR_SIZE*sizeof(char));
  }
  return out;
}
*/

int compare_char(char a, char b)
{
  if(a<b) return -1;
  else if(a==b) return 1;
  else return 0;//a>b
}

char* copy_str(char* a, char* b)
{
  for (int i=0; i<sizeof(b); i++)
  {
    a[i]=b[i];
  }
  return a;
}

/*
int compare_str(char* a, char* b)
{
  int state=1;
  if(a[0]='\0' && b[0]=='\0') return 1;
  for(int i=0; i<KEY_SIZE; i++)
  {
    if((a[i]=='\0' && b[i]!='\0') || (a[i]!='\0' && b[i]=='\0')) return 0;
    if(a[i]!=b[i]) return 0;
  }
  return 1;
}

int search(struct elem* tabl, char* obj)
{
  int first=0, last=PIC_SIZE, mid;
  if (tabl[first]>obj || tabl[last-1]<obj) {printf("Element is not found\n"); return NULL}
  if (tabl[first]>obj || tabl[last-1]<obj) {printf("Element is not found\n"); return NULL}
}
*/

int main()
{

  /*                   из ввода
  for(int i=0; i<PIC_SIZE; i++)
  {
    int count=0;
    char c;
    count=0;
    while(1)
    {
      scanf("%c", &c);
      if(c==' ') break;
      pict[i].key[count]=c;
      count++;
    }
    pict[i].key[count]='\0';
    count=0;
    while(1)
    {
      scanf("%c", &c);
      if(c=='\n') break;
      pict[i].str_pic[count]=c;
      count++;
    }
    pict[i].str_pic[count]='\0';
  }
  for(int i=0; i<PIC_SIZE; i++)
  {
    printf("%s\n", pict[i].str_pic);
  }
*/

  //char str[STR_SIZE];
  elem pict[PIC_SIZE];
  FILE* fo=fopen("pic.txt", "r");
  if(fo==0) {
    printf("Error! Can not open file.\n");
  }
  char* estr;
  int j=0;

  char sym;
  while(1)
  {
    //estr=NULL;
    //estr=fgets (pict[j].str_pic,STR_SIZE,fo);
    sym=getc(fo);
    if (sym==EOF || sym==' ' || sym=='\n') break;
    printf("sym=%c\n",sym);
    pict[0].key[j]=sym;
    printf("key[j]=%c\n",pict[0].key[j]);
    //printf("here, j=%d\n", j);
    /*
    if (estr == NULL)
    {
        if (feof(fo)!=0) break;
        else {
          printf ("Error! Can not read from file.\n");
          break;
        }
    }*/
    //printf("%s", str);
    //pict[j].str_pic=estr;
    j++;
    //printf("%s", pict[j].str_pic);
  }
  pict[0].key[j]='\0';
  //puts("key:");
  printf("key: %s\n", pict[0].key);
  fclose(fo);


  /*
  for(int i=0; i<PIC_SIZE; i++)
  {
    printf("%s\n", pict[i]->str_pic);
  }*/
}
