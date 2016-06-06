#include <stdio.h>


void menu()
{
    printf("_______________Menu_______________\n");
    printf("1.    Binary search               \n");
    printf("2.    Print keys                  \n");
    printf("3.    Quit                        \n");
    printf("Choose a point: \n");
}

typedef struct a
{
    int numkey;
    char strkey[51];
    char val[51];

}elem;

int comp(char a, char b)
{
    if(a<=b) return 1;
    else return 2;
}
int str_comp(char* a, char*b)
{
    int i=0;
    while(1)
    {
        if(a[i]=='\0' && b[i]=='\0')
        {
            return 1;
        }
        if( (a[i]=='\0' && b[i]!='\0') || (a[i]!='\0' && b[i]=='\0') )
        {
            return 0;
        }
        if(a[i]!=b[i])
        {
            return 0;
        }
        i++;
    }
}

int bin_search(int num, char* str, elem* inp)
{
    int left=0, right=19, mid=(int)((left+right)/2);
    while(1)
    {
        mid=(int)((left+right)/2);
        int a=inp[mid].numkey;
        if(a==num)
        {

            while(1)
            {
                if(a==inp[mid-1].numkey && str_comp(str, inp[mid-1].strkey)) mid--;
                else break;
            }
            while(1)
            {
                if(a!=inp[mid].numkey || str_comp(str, inp[mid].strkey)==0) break;
                printf("%d) %d %s %s\n\n",mid+1, a, inp[mid].strkey,inp[mid].val);
                mid++;
            }
            return 0;

        }
        if(num<a)
        {
            right=mid;
            continue;
        }
        if(a<num)
        {
            left=mid;
            continue;
        }
        if(left==right && a!=num)
        {
            printf("Your number not found");
            return 0;
        }
    }


}


int comparator(char* a, char*b) // 1, если приоритет а больше, чем приоретет б, иначе 0
{
    for(int i=0;i<51;i++)
    {
        if(a[i]!=b[i])
        {
            if(comp(a[i],b[i])==1) return 1;
            if(comp(a[i],b[i])==2) return 0;

            if(a[i]=='\0') return 1;
            if(b[i]=='\0') return 0;
        }
    }
    return 1;
}

elem* merge_sort(elem* up, elem* down, int left, int right)
{
    if (left == right)
    {
        down[left] = up[left];
        return down;
    }

    int middle = (int)((left + right) * 0.5);

    // разделяй и сортируй
    elem *l = merge_sort(up, down, left, middle);
    elem *r = merge_sort(up, down, middle + 1, right);

    // слияние двух отсортированных половин
    elem *res = l == up ? down : up;

    int width = right - left, lcur = left, rcur = middle + 1;
    for (int i = left; i <= right; i++)
    {
        if (lcur <= middle && rcur <= right)
        {int le=l[lcur].numkey, ri=r[rcur].numkey;
            if (le < ri)
            {
                res[i] = l[lcur];
                lcur++;
            }
            /*else*/ if(le > ri)
            {
                res[i] = r[rcur];
                rcur++;
            }
            if ( le == ri)
            {
                if(comparator(l[lcur].strkey,r[rcur].strkey))
                {
                    res[i] = l[lcur];
                    lcur++;
                }
                else
                {
                    res[i] = r[rcur];
                    rcur++;
                }
            }
        }
        else if (lcur <= middle)
        {
            res[i] = l[lcur];
            lcur++;
        }
        else
        {
            res[i] = r[rcur];
            rcur++;
        }
    }
    return res;
}

int main()
{
    elem a[25],b[25];
    for(int i=0;i<20;i++)
    {
        char c;
        int h=0;
        a[i].numkey=0;
        int flag=1;
        while(1)
        {
            scanf("%c",&c);
            if(c==' ') break;
            if(c=='-') {flag=-1; continue;}
            a[i].numkey*=10;
            a[i].numkey+=(c-'0');
        }

        a[i].numkey*=flag;

        while(1)
        { //printf("%d",h)
            scanf("%c",&c);
            if(c==' ') break;
            a[i].strkey[h]=c;
            h++;
        }
        a[i].strkey[h]='\0';

        h=0;
        while(1)
        {
            scanf("%c",&c);
            if(c=='\n') break;
            a[i].val[h]=c;
            h++;
        }
        a[i].val[h]='\0';
    }
    printf("Input:\n");
    for(int i=0;i<20;i++)
    {
        printf("%s\n",a[i].val);
    }
    printf("\n\n\nOutput:\n");

    elem *output=merge_sort(a,b,0,19);

    for(int i=0;i<20;i++)
    {
        printf("%s\n",output[i].val);
    }
    printf("\n\n");


    char act[10];
    for(;;)
    {
        menu();
        scanf("%s",act);
        if(act[0]=='1')
        {int zz;
            printf("Enter number key to search: \n");
            scanf("%d",&zz);
            printf("Enter string key to search: \n");
            char yy[51];
            scanf("%s",yy);
            bin_search(zz,yy,a);
        }

        if(act[0]=='2')
        {
            printf("\nKeys: \n\n");
            for(int i=0;i<20;i++)
            {
                printf("%d %s\n",a[i].numkey,a[i].strkey);
            }
            printf("\n");
        }

        if(act[0]=='3')
        {
            printf("Bye!\n");
            return 0;
        }

    }
}
