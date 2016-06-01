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

int count,size;

enum brackets{
    obr=0,
    cbr
};

enum operations{
    plus=0,
    minus,
    multip,
    dev,
    pw
};

union symb{
    int value;//0
    char var;//1
    enum brackets br;//2
    enum operations op;//3
};

struct elem{
    int flag;
    int type;// 0 - char, 1 - int
    union symb el;
};


struct elem* Dejkstra(struct elem* part, struct elem* res)
{
    int i=0,j=0,state=1;
    char m,c,t;
    Stack temp=NULL;
    for (i=0;i<count;i++)
    {
        if(part[i].flag==0)
        {
            res[j]=part[i];
            j++;
        }
        if(part[i].flag==3)
        {
            if(part[i].el.op==0)
            {
                temp=in_s(temp,'+');
            } else if(part[i].el.op==1)
            {
                temp=in_s(temp,'-');
            } else if(part[i].el.op==2)
            {
                temp=in_s(temp,'*');
            } else if(part[i].el.op==3)
            {
                temp=in_s(temp,'/');
            } else if(part[i].el.op==4)
            {
                temp=in_s(temp,'^');
            }
        }

        if (part[i].flag==2 && part[i].el.br==0)
        {
            temp=in_s(temp,'(');
        }
        if (part[i].flag==2 && part[i].el.br==1)
        {
            while((c=first_s(temp))!='(')
            {
                if(!empty_s(temp))
                {
                    printf("Wrong quantity of brackets\n");
                    state=0;
                    return res;
                    break;
                }
                temp=out_s(temp,&m);

                res[j].flag=2;
                res[j].type=0;
                res[j].el.value=part[i].el.value;
                j++;


                res[i]=m;
            }
            temp=out_s(temp,&m);
            if((c=first_s(temp))== '+' || c=='-' || c=='*' || c=='/' || c=='^')
            {
                temp=out_s(temp,&m);
                res[i]=m;
            }
        }
        if(!state)
        {
            i=count;
            break;
        }
        if(part[i].flag==3)
        {
            switch(part[i].el.op)
            {
                case 0:
                    t='+';
                case 1:
                    t='-';
                case 2:
                    t='*';
                case 3:
                    t='/';
                case 4:
                    t='^';
            }
            if (temp!=NULL)
            {
                while(((t==0||t==1)&&((c=first_s(temp))=='+'||c=='-'||c=='*'||c=='/'||c=='^'))||((t==2||t==3)&&(c=='*'||c=='/'||c=='^'))||((t==5)&&(c=='^')))
                {
                    temp=out_s(temp,&m);
                    res[i]=m;
                }
                temp=in_s(temp,t);
            } else {
                temp=in_s(temp,t);
            }
        }
    }

    while(empty_s(temp))
    {
        temp=out_s(temp,&m);
        res[i]=m;
    }
    return res;
}

int check_expr(char* str)
{
    int i=0;
    if(str[0]=='+'||str[0]=='-'||str[0]=='/'||str[0]=='*'||str[0]=='^') return 0;

    for(i=0;i<count;i++){
        if(((str[i]>=48&&str[i]<=57)||(str[i]>=65&&str[i]<=90)||(str[i]>=97&&str[i]<=122))&&(str[i+1]=='(')) return 0;
        if((str[i]==')')&&((str[i+1]>=48&&str[i+1]<=57)||(str[i+1]>=65&&str[i+1]<=90)||(str[i+1]>=97&&str[i+1]<=122))) return 0;
        if((str[i]=='(')&&(str[i+1]=='+'||str[i+1]=='*'||str[i+1]=='/'||str[i+1]=='^'||str[i+1]==')')) return 0;
        if((str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='^')&&(str[i+1]==')')) return 0;
        if((str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='^')&&(str[i+1]=='+'||str[i+1]=='-'||str[i+1]=='*'||str[i+1]=='/'||str[i+1]=='^')) return 0;
    }
    return 1;
}

struct elem* parse(char* ch)
{
    extern count,size;
    struct elem *part;
    part=malloc(30*sizeof(struct elem));
    int i=0,j=0,k=0,b=-1,a=-1;
    char temp[10];
    for(i=0;i<10;i++)temp[i]=NULL;
    i=0;
    if(check_expr(ch))
    {
        while(ch[i]!='\0'){
            if (ch[i]=='(')
            {
                part[j].flag=2;
                part[j].type=0;
                part[j].el.br=0;
                i++;
                j++;
            }
            if (ch[i]==')')
            {
                part[j].flag=2;
                part[j].type=0;
                part[j].el.br=1;
                i++;
                j++;
            }
            if (ch[i]=='+')
            {
                part[j].flag=3;
                part[j].type=0;
                part[j].el.op=0;
                i++;
                j++;
            }
            if (ch[i]=='-')
            {
                if(ch[i-1]=='(')//������� �����
                {
                    ++i;
                    part[j].flag=0;
                    part[j].type=1;
                    k=0;
                    while((isdigit(ch[i]))){
                        temp[k]=ch[i];
                        k++;
                        i++;
                    }
                    b=atoi(temp);
                    b=b*(-1);
                    part[j].el.value=b;
                    j++;
                    for(a=0;a<10;a++)temp[a]='\0';
                } else {//�������� �����
                    part[j].flag=3;
                    part[j].type=0;
                    part[j].el.op=1;
                    i++;
                    j++;
                }
            }
            if (ch[i]=='*')
            {
                part[j].flag=3;
                part[j].type=0;
                part[j].el.op=2;
                i++;
                j++;
            }
            if (ch[i]=='/')
            {
                part[j].flag=3;
                part[j].type=0;
                part[j].el.op=3;
                i++;
                j++;
            }
            if (ch[i]=='^')
            {
                part[j].flag=3;
                part[j].type=0;
                part[j].el.op=4;
                i++;
                j++;
            }
            if((isdigit(ch[i])))
            {
                part[j].flag=0;
                part[j].type=1;
                k=0;
                while((isdigit(ch[i]))){
                    temp[k]=ch[i];
                    k++;
                    i++;
                }
                b = atoi(temp);
                part[j].el.value=b;
                j++;
                for(a=0;a<10;a++)temp[a]='\0';
            }
            if(ch[i]>='A'&& ch[i]<='Z' || ch[i]>='a'&& ch[i]<='z')
            {
                part[j].flag=1;
                part[j].type=0;
                part[j].el.var=ch[i];
                i++;
                j++;
            }
            size=j;
        }
    } else printf("Wrong expression\n");
    return part;
}

void print_pars(struct elem* orig)
{
    int j=0;
    for(j=0;j<count;j++){

        if (orig[j].flag==0)
        {
            printf("%d ",orig[j].el.value);

        }else if (orig[j].flag==1)
        {
            printf("%c ",orig[j].el.var);
        }else if (orig[j].flag==2)
        {
            if(orig[j].el.br==0){
                printf("( ");
            } else {
                printf(") ");
            }
        }else if (orig[j].flag==3)
        {
            if(orig[j].el.op==0){
                printf("+ ");
            }else if(orig[j].el.op==1) {
                printf("- ");
            }else if(orig[j].el.op==2) {
                printf("* ");
            }else if(orig[j].el.op==3) {
                printf("'\'");
            }else if(orig[j].el.op==4) {
                printf("^ ");
            }
        }
    }
    printf("\n");
}

int main()
{
    int i=0, k, b, j=0,a=0;
    char ch[30];
    for(i=0;i<30;i++)ch[i]=NULL;
    struct elem *res;
    part=malloc(30*sizeof(struct elem));

    printf("Enter expression:\n");
    scanf("%s",ch);

    i=0;
    struct elem *orig;
    orig=malloc(30*sizeof(struct elem));
    orig=parse(ch);
    print_pars(orig);
    printf("size is %d, flag is %d, symb is %d\n",count, orig[0].flag, orig[0].el.op);
    //char r='+';
    //int u = 15;

    res=Dejkstra(orig, res);
    i=0;
    for(i=0;i<count;i++){
        printf("")
    }
    return 0;
}
//����������� � ����� � ��� ��� ��������, ������� �������� ��� ��������� � ������ ���� �����
//�����������, ������ ����� ����� �������� ��� ����
