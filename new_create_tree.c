#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>

int count, check, st=0, tree_size;

struct val{
    int type_t;// 0 - char, 1 - int, 2 - var, 3 - (, 4 - ).
    int value_t;
    char symb_t;
};

struct node_t{
    struct val val_tree;
    struct node_t* right;
    struct node_t* left;
};

/*typedef struct elem{
    int type;// 0 - char, 1 - int, 2 - var, 3 - (, 4 - ).
    int value;
    char symb;
}elem;*/

typedef struct node_t Node_t;
typedef struct node_t* tree;

tree remove_tree(tree root)
{
	if (root)
	{
		remove_tree(root->right);
		remove_tree(root->left);
		//free(root->val_tree);
		free(root);
	}
	return NULL;
}

tree create_tree(tree root, struct val *ress)
{
	struct val* s=NULL;
	printf("in create tree\n");
	int j=count-1;
	//if (root) root=remove_tree(root);
	if (root==NULL)
	{
	    printf("root is null\n");
		root=malloc(sizeof(Node_t));
		root->right=NULL;
		root->left=NULL;
		*s=ress[j];
		printf("what is it\n");
		if (s->type_t==0)
		{
		    printf("it is option\n");
			root->val_tree=ress[j];
			j--;
			root->right=create_tree(root->right, ress);
			root->left=create_tree(root->left, ress);
		}else{
		    printf("it is var\n");
			root->val_tree=ress[j];
			j--;
		}
	}
	return root;
}

void lRr(tree root, int l)
{
    if(root){
        if((root->val_tree.type_t==0)||(root->val_tree.type_t==2)) printf("%*s%c\n", 4*l, " ", root->val_tree.symb_t);
        else if(root->val_tree.type_t==1) printf("%*s%d\n", 4*l, " ", root->val_tree.value_t);
        lRr(root->left, l+1);
        lRr(root->right,l);
    }
}

void print_tree(tree t)
{
    if(t){
        printf("Дерево:\n");
        lRr(t,0);
        printf("\n");
    }else{
        printf("Дерево пусто\n");
    }

}

//.....................................STACK..........................................//
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

//....................................................................................//

struct val* Dejkstra(struct val* part, struct val* res)
{
    extern count;
    int i=0,j=0,state=1;
    char m,c,t;
    Stack temp=NULL;
    //printf("part type0=%d\n",part[0].type);
    //printf("j=%d\n",j);
    for (i=0;i<count;i++)
    {
        if(part[i].type_t==1||part[i].type_t==2)
        {
            res[j]=part[i];
            ++j;
            //printf("v chisle,j=%d\n",j);
        }
        /*if(part[i].type==0)
        {
            temp=in_s(temp,part[i].symb);
        }*/
        if (part[i].type_t==3)
        {
            temp=in_s(temp,part[i].symb_t);
        }
        if (part[i].type_t==4)
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
                res[j].symb_t=m;
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
        if(part[i].type_t==0)
        {
            t=part[i].symb_t;
            if (temp!=NULL)
            {
                c=first_s(temp);
                while(((t=='+')&&(c=='+'||c=='-'||c=='*'||c=='/'||c=='^'))||((t=='-'||t=='*')&&(c=='*'||c=='/'||c=='^'))||((t=='/')&&(c=='^')))
                {
                    temp=out_s(temp,&m);
                    res[j].symb_t=m;
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
        res[j].symb_t=m;
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

struct val* parse(char* ch)
{
    extern count,check;
    struct val *part;
    part=malloc(30*sizeof(struct val));
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
                part[j].type_t=3;
                part[j].symb_t='(';
                ++j;
                ++i;
            }
            if (ch[i]==')')
            {
                part[j].type_t=4;
                part[j].symb_t=')';
                ++j;
                ++i;
            }
            if (ch[i]=='+')
            {
                //printf("zawel v plus\n");
                part[j].type_t=0;
                part[j].symb_t='+';
                //printf("dobavil plus v res\n");
                ++j;
                ++i;
            }
            if (ch[i]=='-')
            {
                if(ch[i-1]=='(')//унарный минус
                {
                    ++i;
                    part[j].type_t=1;
                    k=0;
                    while((isdigit(ch[i]))){
                        temp[k]=ch[i];
                        k++;
                        i++;
                    }
                    b=atoi(temp);
                    b=b*(-1);
                    part[j].value_t=b;
                    ++j;
                    for(a=0;a<10;a++)temp[a]='\0';
                } else {//бинарный минус
                    part[j].type_t=0;
                    part[j].symb_t='-';
                    ++j;
                    ++i;
                }
            }
            if (ch[i]=='*')
            {
                part[j].type_t=0;
                part[j].symb_t='*';
                ++j;
                ++i;
            }
            if (ch[i]=='/')
            {
                part[j].type_t=0;
                part[j].symb_t='/';
                ++j;
                ++i;
            }
            if (ch[i]=='^')
            {
                part[j].type_t=0;
                part[j].symb_t='^';
                ++j;
                ++i;
            }
            if((isdigit(ch[i])))
            {
                //printf("zawel v chislo\n");
                part[j].type_t=1;
                k=0;
                while((isdigit(ch[i]))){
                    //printf("poka chislo\n");
                    temp[k]=ch[i];
                    k++;
                    i++;
                }
                //printf("obrabotal chislo\n");
                b = atoi(temp);
                part[j].value_t=b;
                ++j;
                //printf("vishel iz chisla\n");
                for(a=0;a<10;a++)temp[a]='\0';
            }
            if(ch[i]>='A'&& ch[i]<='Z' || ch[i]>='a'&& ch[i]<='z')
            {
                part[j].type_t=2;
                part[j].symb_t=ch[i];
                ++j;
                ++i;
            }
        }
    }
    count=j;
    //printf("j=%d\n",j);
    return part;
}

void print_pars(struct val* orig)
{
    int j=0;
    for(j=0;j<count;j++){
        if (orig[j].type_t!=1) printf("%c ",orig[j].symb_t);
        else printf("%d ",orig[j].value_t);
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
    struct val *orig;
    struct val *ress;
    orig=malloc(100*sizeof(struct val));
    ress=malloc(100*sizeof(struct val));
    orig=parse(ch);
    print_pars(orig);
    ress=Dejkstra(orig,ress);
    //printf("expr wrong or right: %d\n count=%d\n",check,count);
    for(i=0;i<count;i++)
    {
        if(ress[i].type_t==1){
            printf("%d ",ress[i].value_t);
        } else {
            printf("%c ",ress[i].symb_t);
        }
    }
    printf("\n");
    tree T=NULL;
    //T=malloc(sizeof(Node_t));
    //T->right=NULL;
    //T->left=NULL;
    T=create_tree(T, ress);
    printf("type %d, int %d, symb %c\n",T->val_tree.type_t, T->val_tree.value_t, T->val_tree.symb_t);
    //print_tree(T);
    return 0;
}
