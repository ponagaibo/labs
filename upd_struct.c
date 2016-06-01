#include<stdio.h>
#include <stdlib.h>
#include<ctype.h>

int count, check, st=0, tree_size;

struct node_t{
    struct elem* val_t;
    struct node_t* right;
    struct node_t* left;
};

struct elem{
    int type;// 0 - char, 1 - int, 2 - var, 3 - (, 4 - ).
    int value;
    char symb;
};

//typedef struct node_t Node_t;
//typedef struct node_t* tree;

///.................................TREE................................///
struct node_t* remove_tree(struct node_t* root)
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

void find_tree(struct node_t* root, struct node_t** r)
{

    if (root->right!=NULL) {
        r=&(root->right);
        find_tree(root->right,r);
    }
    if (root->left!=NULL) find_tree(root->left,r);
    //if((root->val_tree.type==0)||(root->val_tree.type==2)) printf("in tree at %c\n",root->val_tree.symb);
    //else if(root->val_tree.type==1) printf("in tree at %d\n",root->val_tree.value);
}

struct node_t** search_tree (struct node_t* t, struct node_t* *r)
{
    extern st;
    st=0;
    //printf("in search\n");
    if (t->right!=NULL)
    {
        //printf("right isnt null\n");
        search_tree(t->right, r);
    } //else printf("right is null\n");

    if (t->left!=NULL)
    {
        //printf("left isnt null\n");
        search_tree(t->left, r);
    }//else printf("left is null\n");
    //printf("type is %d, st=%d\n",t->val_tree.type_t, st);
    if (t->val_t->type==0 && (t->right==NULL || t->left==NULL) && (st==0))
    {
        printf("found node\n");
        r=&t;
        st++;
        return *r;
    }
    //printf("end search\n");
    if(st==0) printf("Node is not found\n");
}

void print_tree(struct node_t* root, int* i)
{
    //extern tree_size;
    //tree_size=1;
    if((root->val_t->type==0)||(root->val_t->type==2)) printf("in tree at %c\n",root->val_t->symb);
    else if(root->val_t->type==1) printf("in tree at %d\n",root->val_t->value);
    (*i)++;
    //tree_size++;
    if (root->right!=NULL) print_tree(root->right,i);
    if (root->left!=NULL) print_tree(root->left,i);
    //printf("size of tree is %d\n", tree_size);

}
///..................................................................................///

///.....................................STACK........................................///
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

///....................................................................................///

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

    struct node_t* T=NULL;
    struct node_t* R=NULL;
    struct node_t* t2=NULL;
    struct node_t* tt=NULL;
    struct node_t** t1;
    //if (T) T = remove_tree(T);
    T=(struct node_t*)malloc(sizeof(struct node_t));
    T->right=NULL;
    T->left=NULL;
    int q=1;
    T->val_t->value=q;
   // T->val_tree->type=ress[count-1].type;
    //T->val_tree->symb=ress[count-1].symb;
    //printf("root type is %d, value is %d, symb is %c\n",(T)->val_tree->type, (T)->val_tree->value, T->val_tree->symb);
    //T->right=(struct node_t*)malloc(sizeof(struct node_t));
    //t3=T->right;
    //if (t3==NULL) printf("t3 is null\n");
    //T->right=tt;
    //printf("root type is %d\n",(T->right)->val_tree->type);
    printf("here\n");
    //printf("root type is %d, right type is %d, left type is %d",(tt)->val_tree->type, (tt)->val_tree->type, (tt)->val_tree->type);
    //printf("found node type %d int %d char %c\n", T->val_tree->type, T->val_tree->value, T->val_tree->symb);
    //if(T->right==NULL) printf("T->right is null\n");
    //if(T->left==NULL) printf("T->left is null\n\n");
    //j=0;
    //print_tree(T,&j);
    //printf("begin----------%d\n",j);
    /*for(i=count-2;i>=0;i--)
    {
        t1=&T;
        printf("%d\n",i);
        t2=search_tree(T, t1);
        printf("found node type %d int %d char %c\n", (*(t1))->val_tree.type_t, (*(t1))->val_tree.value_t, (*(t1))->val_tree.symb_t);
        //if((*(t1))->right==NULL) printf("t1->right is null\n");
        //if((*(t1))->left==NULL) printf("t1->left is null\n");
        //t2=(*t1);
        printf("here112\n");
        t3->val_tree.value_t=ress[i].value;
        printf("here11464747474742\n");
        t3->val_tree.type_t=ress[i].type;
        t3->val_tree.symb_t=ress[i].symb;
        printf("here114422\n");
        t3->right=NULL;
        t3->left=NULL;
        //printf("found node type %d int %d char %c\n", t2->val_tree->type, t2->val_tree->value, t2->val_tree->symb);
        //if(t2->right==NULL) printf("t2->right is null\n");
        //if(t2->left==NULL) printf("t2->left is null\n\n");
        if (t2==T){
            printf("t2=T\n");
            //t2=T;
        }
        if (t2->right==NULL) {
            t2->right=malloc(sizeof(Node_t));
            t2=t2->right;
            printf("right\n");
        } else {
            t2->left=malloc(sizeof(Node_t));
            t2=t2->left;
            printf("left\n");
        }
        //printf("here112\n");
        //t2=t3;
        //if(t2->right==NULL) printf("t2->right is null\n");
        //printf("here0\n");
        t2->val_tree.value_t=ress[i].value;
        //printf("here2\n");
        t2->val_tree.type_t=ress[i].type;
        //printf("here3\n");
        t2->val_tree.symb_t=ress[i].symb;
        //printf("here4\n");
        t2->right=NULL;
        //printf("here0000\n");
        t2->left=NULL;
        //printf("here1\n");
        //printf("%d %d %c", t2->val_tree.value_t, t2->val_tree.type_t,t2->val_tree.symb_t);
        j=0;
        print_tree(T,&j);
        //printf("here5\n");
        printf("end------- %d\n",j);
    }*/
    //printf("%c\n %d\t%d\n",T->val_tree->symb,(T->right)->val_tree->symb, (T->left)->val_tree->symb);
    //print_tree(T,0);

    return 0;
}
