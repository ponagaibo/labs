#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>

int count, check;

struct val{
    int type_t;// 0 - char, 1 - int, 2 - var, 3 - (, 4 - ).
    int value_t;
    char symb_t;
};

struct node_t{
    struct val* val_tree;
    struct node_t* right;
    struct node_t* left;
};

typedef struct elem{
    int type;// 0 - char, 1 - int, 2 - var, 3 - (, 4 - ).
    int value;
    char symb;
}elem;

typedef struct node_t Node_t;
typedef struct node_t* tree;

tree remove_tree(tree root)
{
	if (root)
	{
		remove_tree(root->right);
		remove_tree(root->left);
		free(root->val_tree);
		free(root);
	}
	return NULL;
}

tree find_tree(tree root)
{
    //int i=0;
    //char s='!';
    //int d=-111;
    printf("in make_tree at %d\n",c);
    //if (root) root = remove_tree(root);
	if (c>=0)
	{
	    //printf("root is null\n");
	    d=postfix[c].type;
	    printf("type=%d\n",d);
		tree root2=malloc(sizeof(Node_t));
		root=root2;
		root->right=NULL;
		root->left=NULL;
		if(d==0){
		    printf("in op\n");
			root->val_tree->symb_t=postfix[c].symb;
			root->val_tree->type_t=0;
			root->right=make_tree(root->right, postfix, c-1);
			//root->left=make_tree(root->left, postfix, c-1);
		}else if(d==1){
		    printf("in int\n");
			root->val_tree->value_t=postfix[c].value;
			root->val_tree->type_t=1;
		}else{
		    printf("in var\n");
		    root->val_tree->symb_t=postfix[c].symb;
		    root->val_tree->type_t=2;
		}
	}
	printf("end make_tree\n");
	return root;
}

void print_tree(tree root, int i)
{
    printf("in print_tree\n");
    int k;
	if (root)
	{
		print_tree(root->right, i+1);
		for (k=0;k<=i;k++)
			printf("  ");
		if(root->val_tree->type_t==1)
			printf("%d\n", root->val_tree->value_t);
		else
			printf("%c\n", root->val_tree->symb_t);
		print_tree(root->left, i+1);
	}
	printf("end print_tree\n");
}

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

elem* Dejkstra(elem* part, elem* res)
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
                while(((t=='+')&&(c=='+'||c=='-'||c=='*'||c=='/'||c=='^'))||((t=='-'||t=='*')&&(c=='*'||c=='/'||c=='^'))||((t=='/')&&(c=='^')))
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

int size_of_str(char* str)
{
    int i=0;
    while(str[i]!='\0') i++;
    return i;
}

int check_expr(char* str)
{
    int i=0,s=0;
    if(str[0]=='+'||str[0]=='-'||str[0]=='/'||str[0]=='*'||str[0]=='^') {
        printf("wrong 0\n");
        return 0;
    }
    extern count;
    count = size_of_str(str);
    printf("count=%d\n",count);
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
        if((str[i]=='+'||str[i]=='-'||str[i]=='*'||str[i]=='/'||str[i]=='^')&&(str[i-1]=='+'||str[i-1]=='-'||str[i-1]=='*'||str[i-1]=='/'||str[i-1]=='^')){
            printf("wrong 5\n");
            return 0;
        }
    }
    if(s!=0){
        printf("wrong 6\n");
        return 0;
    }
    return 1;
}

elem* parse(char* ch)
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
        while(ch[i]!='\0'){//���� ��� ������, check
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
                if(ch[i-1]=='(')//������� �����
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
                } else {//�������� �����
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

void print_pars(elem* orig)
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
    print_pars(orig);
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
    printf("\n");
    //printf("symb ress[0]=%c\t",ress[0].symb);
    //printf("int ress[0]=%d\n",ress[0].value);
    //printf("\nsize of ress is %d\n",count);
    tree T=NULL, t2=NULL;
    if (T) T = remove_tree(T);
    for(i=count-1;i>=0;i--)
    {
        t2=find_tree(T);
        t2=malloc(sizeof(Node_t));
        t2->right=NULL;
        t2->left=NULL;

        t2->val_tree.value_t=ress[i].value;
        t2->val_tree.type_t=ress[i].type;
        t2->val_tree.symb_t=ress[i].symb;
    }
    printf("%c\n %d\t%d\n",T->val_tree->symb_t,(T->right)->val_tree->symb_t, (T->left)->val_tree->symb_t);
    //print_tree(T,0);

    return 0;
}
