#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*int comp(int a, int b)
{
  if(a==b) return 1;
  else if(a<b) return -1;
  else return 0;
}*/

int compare_str(char* a, char* b)
{
  int state=1;
  for(int i=0; i<7; i++)
  {
    if(a[i]='\0' && b[i]=='\0') return 1;
    if((a[i]=='\0' && b[i]!='\0') || (a[i]!='\0' && b[i]=='\0'))
    {
      printf("one of str ended\n");
      return 0;
    }
    if(a[i]!=b[i])
    {
      printf("chars is not equal\n");
      return 0;
    }
  }
  return 1;
}

int main()
{
  char* aa;
  char* bb;
  printf("enter aa\n");
  scanf("%s", aa);
  printf("enter bb\n");
  scanf("%s", bb);
  int cm=compare_str(aa,bb);
  printf("cm=%d\n",cm);
  printf("aa is %s\n",aa);
  printf("bb is %s\n",bb);

  return 0;
}
