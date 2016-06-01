#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>

struct node_s
{
    char value;
    struct node_s* prev;
};

typedef struct node_s Node_s;
typedef struct node_s* Stack;

int empty_s(Stack s)
{
    if (s==NULL) return 0;
    else return 1;
}

char first_s(Stack s)
{
    if(s!=NULL) return s->value;
    else return 0;
}

int count_s(Stack s)
{
    int i=0;
    for(i=0;s!=NULL;i++) s=s->prev;
    return i;
}

Stack in_s(Stack s, char c)
{
    Stack ss;
    ss=malloc(1*sizeof(Node_s));
    ss->value=c;
    ss->prev=s;
    return ss;
}

Stack out_s(Stack s, char* c)
{
    *c=s->value;
    Stack ss=s->prev;
    free(s);
    return ss;
}

Stack del_s(Stack s)
{
    Stack ss;
    while(ss!=NULL)
    {
        ss=s->prev;
        free(s);
        s=ss;
    }
    return s;
}

int count, check;

struct elem{
    int type;// 0 - char, 1 - int, 2 - var, 3 - (, 4 - ).
    int value;
    char symb;
};


struct elem* Dejkstra(struct elem* part, struct elem* res)
{
    extern count;
    int i=0,j=0,state=1;
    char m,c,t;
    Stack temp=NULL;
    //printf("part type0=%d\n",part[0].type);
    //printf("j=%d\n",j);
    for (i=0;i<count;i++)
    {
        if(part[i].type==1||part[i].type==2)
        {
            res[j]=part[i];
            ++j;
            //printf("v chisle,j=%d\n",j);
        }
        /*if(part[i].type==0)
        {
            temp=in_s(temp,part[i].symb);
        }*/
        if (part[i].type==3)
        {
            temp=in_s(temp,part[i].symb);
        }
        if (part[i].type==4)
        {
            while((c=first_s(temp))!='(')
            {
                /*if(!empty_s(temp))
                {
                    printf("Wrong quantity of brackets\n");
                    state=0;
                    return res;
                    break;
                }*/
                temp=out_s(temp,&m);
                res[j].symb=m;
                ++j;
            }
            temp=out_s(temp,&m);
            /*if((c=first_s(temp))== '+' || c=='-' || c=='*' || c=='/' || c=='^')
            {
                temp=out_s(temp,&m);
                res[j]=m;
                j++;
            }*/
        }
        /*if(!state)
        {
            //i=count;
            break;
        }*/
        if(part[i].type==0)
        {
            t=part[i].symb;
            if (temp!=NULL)
            {
                c=first_s(temp);
                while((t=='+'||t=='-')&&(c=='*'||c=='\\'||c=='^')||(t=='*'||t=='\\')&&(c=='^'))
                {
                    temp=out_s(temp,&m);
                    res[j].symb=m;
                    ++j;
                    c=first_s(temp);
                }
                temp=in_s(temp,t);
            } else {
                temp=in_s(temp,t);
            }
            //printf("j=%d\n",j);
        }
    }

    while(empty_s(temp))
    {
        temp=out_s(temp,&m);
        res[j].symb=m;
        ++j;
    }
    //printf("j=%d\n",j);
    count=j;
    return res;
}

int check_expr(char* str)
{
    int i=0,s=0;
    if(str[0]=='+'||str[0]=='-'||str[0]=='/'||str[0]=='*'||str[0]=='^') {
        printf("wrong 0\n");
        return 0;
    }

    for(i=0;i<count;i++){
        if(str[i]=='(')s++;
        if(str[i]==')')s--;
        if(((str[i]>=48&&str[i]<=57)||(str[i]>=65&&str[i]<=90)||(str[i]>=97&&str[i]<=122))&&(str[i+1]=='(')){
            printf("wrong 1\n");
            return 0;
        }
        if((str[i]==')')&&((str[i+1]>=48&&str[i+1]<=57)||(str[i+1]>=65&&str[i+1]<=90)||(str[i+1]>=97&&str[i+1]<=122))){
            printf("wrong 2\n");
            return 0;
        }
        if((str[i]=='(')&&(str[i+1]=='+'||str[i+1]=='*'||str[i+1]=='/'||str[i+1]=='^'||str[i+1]==')')){
            printf("wrong 3\n");
            return 0;
        }
        if((str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='^')&&(str[i+1]==')')){
            printf("wrong 4\n");
            return 0;
        }
        if((str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='^')&&(str[i+1]=='+'||str[i+1]=='-'||str[i+1]=='*'||str[i+1]=='/'||str[i+1]=='^')){
            printf("wrong 5\n");
            return 0;
        }
    }
    if(s!=0){
        printf("wrong 6\n");
        return 0;
    } else{
        printf("right\n");
        return 1;
    }
}

struct elem* parse(char* ch)
{
    extern count,check;
    struct elem *part;
    part=malloc(30*sizeof(struct elem));
    int i=0,j=0,k=0,b=-1,a=-1,l=0;
    char temp[30];
    for(i=0;i<30;i++)temp[i]=NULL;
    i=0;
    check=check_expr(ch);
    //printf("zawel v parse, check=%d\n",check);
    if(check)
    {
        while(ch[i]!='\0'){//если без ошибок, check
            if (ch[i]=='(')
            {
                part[j].type=3;
                part[j].symb='(';
                ++j;
                ++i;
            }
            if (ch[i]==')')
            {
                part[j].type=4;
                part[j].symb=')';
                ++j;
                ++i;
            }
            if (ch[i]=='+')
            {
                //printf("zawel v plus\n");
                part[j].type=0;
                part[j].symb='+';
                //printf("dobavil plus v res\n");
                ++j;
                ++i;
            }
            if (ch[i]=='-')
            {
                if(ch[i-1]=='(')//унарный минус
                {
                    ++i;
                    part[j].type=1;
                    k=0;
                    while((isdigit(ch[i]))){
                        temp[k]=ch[i];
                        k++;
                        i++;
                    }
                    b=atoi(temp);
                    b=b*(-1);
                    part[j].value=b;
                    ++j;
                    for(a=0;a<10;a++)temp[a]='\0';
                } else {//бинарный минус
                    part[j].type=0;
                    part[j].symb='-';
                    ++j;
                    ++i;
                }
            }
            if (ch[i]=='*')
            {
                part[j].type=0;
                part[j].symb='*';
                ++j;
                ++i;
            }
            if (ch[i]=='/')
            {
                part[j].type=0;
                part[j].symb='/';
                ++j;
                ++i;
            }
            if (ch[i]=='^')
            {
                part[j].type=0;
                part[j].symb='^';
                ++j;
                ++i;
            }
            if((isdigit(ch[i])))
            {
                //printf("zawel v chislo\n");
                part[j].type=1;
                k=0;
                while((isdigit(ch[i]))){
                    //printf("poka chislo\n");
                    temp[k]=ch[i];
                    k++;
                    i++;
                }
                //printf("obrabotal chislo\n");
                b = atoi(temp);
                part[j].value=b;
                ++j;
                //printf("vishel iz chisla\n");
                for(a=0;a<10;a++)temp[a]='\0';
            }
            if(ch[i]>='A'&& ch[i]<='Z' || ch[i]>='a'&& ch[i]<='z')
            {
                part[j].type=2;
                part[j].symb=ch[i];
                ++j;
                ++i;
            }
        }
    }
    count=j;
    //printf("j=%d\n",j);
    return part;
}

void print_pars(struct elem* orig)
{
    int j=0;
    for(j=0;j<count;j++){
        if (orig[j].type!=1) printf("%c ",orig[j].symb);
        else printf("%d ",orig[j].value);
    }
    printf("\n");
}

int main()
{
    int i=0, k, b, j=0,a=0;
    char ch[30],res[30];
    for(i=0;i<30;i++){
        ch[i]=NULL;
        //res[i]=NULL;
    }
    printf("Enter expression:\n");
    scanf("%s",ch);
    //printf("expr is %s\n",ch);
    i=0;
    struct elem *orig;
    struct elem *ress;
    orig=malloc(100*sizeof(struct elem));
    ress=malloc(100*sizeof(struct elem));
    orig=parse(ch);
    for (i=0;i<count;i++){
            //printf("heeeeey\n");
        //printf("type:%d, value:%d, symb:%c\n",orig[i].type, orig[i].value, orig[i].symb);
    }
    print_pars(orig);
    //printf("size is %d, flag is %d, symb is %d\n",count, orig[0].flag, orig[0].el.op);
    //char r='+';
    //int u = 15;
    ress=Dejkstra(orig,ress);
    //printf("expr wrong or right: %d\n count=%d\n",check,count);
    for(i=0;i<count;i++)
    {
        if(ress[i].type==1){
            printf("%d ",ress[i].value);
        } else {
            printf("%c ",ress[i].symb);
        }
    }
    /*char p;
    Stack ress = NULL;
    //ress=Dejkstra(orig, res);
    i=0;
    while(empty_s(ress)){
        //printf("pechatau steck\n");
        ress=out_s(ress,&p);
        printf("%c\t",p);
    }*/
    return 0;
}
//разобраться с интом и чар при хранении, хранить значение как структуру с флагом либо юнион
//разобраться, почему после знача операции еще знак
