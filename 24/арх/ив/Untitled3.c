#include <stdio.h>
#include <stdlib.h>


typedef union unon{
    int number;
    char* variable;
    char operation;
}unon;
typedef struct s{
    unon* data;
    int* type;
    int size;
    unon cap;
}s;
typedef struct mass{
    unon* arr;
    int* type;
    int size;
}mass;
typedef struct tree{
    unon a;
    int type;
    struct tree* left;
    struct tree* right;
    int bracket;
}tree;
typedef struct tree* tr;
typedef struct mass* m;
typedef struct s* stack;
int cnt=0;
tr build_tree(m ar,int br){
    tr res=(tr)malloc(sizeof(tree));
    if(cnt!=-1) {
        if(ar->type[cnt]>2) {
            res->a = ar->arr[cnt];
            res->type = ar->type[cnt];
            res->bracket=br;
            cnt--;
            res->right=build_tree(ar,2);
            res->left=build_tree(ar,1);
        }else{
            res->type=ar->type[cnt];
            res->a=ar->arr[cnt];
            res->bracket=br;
            cnt--;
        }
    }
    return res;
}
int bias=0;
int task35=0;

int cur=0;
void print_tree(tr tree,m a) {
    if (tree->left) {
        print_tree(tree->left, a);
    }
    unon q;
    switch (tree->type) {
        case 1:
            if (tree->bracket == 1) {
                q.operation = '(';
                a->arr[cur] = q;
                a->type[cur] = 3;
                cur++;
                a->arr[cur] = tree->a;
                a->type[cur] = 1;
                a->size += 2;
            } else if (tree->bracket == 2) {
                q.operation = ')';
                a->arr[cur] = tree->a;
                a->type[cur] = 1;
                cur++;
                a->arr[cur] = q;
                a->type[cur] = 3;
                a->size += 2;
            }else{
                a->arr[cur]=tree->a;
                a->type[cur]=1;
                cur++;
                a->size += 1;
            }
            cur++;
            break;
        case 2:
            if (tree->bracket == 1) {
                q.operation = '(';
                a->arr[cur] = q;
                a->type[cur] = 3;
                cur++;
                a->arr[cur] = tree->a;
                a->type[cur] = 2;
                a->size += 2;
            } else if (tree->bracket == 2) {
                q.operation = ')';
                a->arr[cur] = tree->a;
                a->type[cur] = 2;
                cur++;
                a->arr[cur] = q;
                a->type[cur] = 3;
                a->size += 2;
            }else{
                a->arr[cur]=tree->a;
                a->type[cur]=1;
                cur++;
                a->size += 1;
            }
            cur++;
            break;
        case 3:
            a->arr[cur] = tree->a;
            a->type[cur] = 3;
            a->size += 1;
            cur++;
            break;
    }


    if (tree->right) {
        print_tree(tree->right, a);
    }
}
int is_empty_stack(stack s){
    if(s->size)
        return 0;
    else
        return 1;
}
void push_back(stack st,unon u){
    if(is_empty_stack(st)){
        st->data=(unon*)malloc(100*sizeof(unon));
        st->type=(int*)malloc(100*sizeof(int));
        st->data[0]=u;
        st->cap=u;
        st->size=1;
    }else{
        st->data[st->size]=u;
        st->size++;
        st->cap=u;
    }
}
void pop_back(stack s){
    if(!is_empty_stack(s)){
        s->size--;
        if(s->size!=0)
            s->cap=s->data[s->size-1];
        else{
            unon temp;
            temp.operation='&';
            s->cap=temp;
        }
    }
}
int char_array_to_int(char* a){
    int res=0;
    int j=0;
    while(a[j]!='\0'){
        res+=a[j]-'0';
        res*=10;
        j++;
    }
    return res/10;
}
int is_bracket(char a){
    return a==')' || a=='(';
}
int is_plus_minus(char a){
    return a=='+' || a=='-';
}
int is_multiply_divide(char a){
    return a=='/' || a=='*';
}
int is_power(char a){
    return a=='^';
}
int type_of_element(char a){
    if(is_bracket(a))
        return 10;
    if(is_plus_minus(a))
        return 20;
    if(is_multiply_divide(a))
        return 30;
    if(is_power(a))
        return 40;
    return 0;
}
int size_of_string(char* a){
    int j=0;
    while(a[j]!='\0')
        j++;
    return j;
}
int correct_bracket(char* a){
    int res=0;
    int i=0;
    for(i=0;i<size_of_string(a);i++){
        if(a[i]=='(')
            res++;
        else if(a[i]==')')
            res--;
        if(res<0)
            return 0;
    }
    if(res)
        return res;
    else
        return 0;
}
int is_digit(char a){
    int t=a-'0';
    if(t<0 || t>9)
        return 0;
    else
        return 1;
}
int is_alpha(char a){
    if((a>=65 && a<=90) || (a>=97 && a<=122))
        return  1;
    else
        return 0;
}
m string_to_union_array(char* a){
    m res=(m)malloc(sizeof(mass));
    int siz=size_of_string(a);
    res->arr=(unon*)malloc(siz*sizeof(unon));
    res->type=(int*)malloc(siz*sizeof(int));
    res->size=0;
    int j=0;
    int i=0;
    for(i=0;i<size_of_string(a);i++){

        if( (a[i]=='-' && a[i-1]=='(') ){
            int temp=i+1;
            if(is_digit(a[i+1])){
                while(!type_of_element(a[temp])){
                    if(!is_digit(a[temp])){
                        printf("Invalid variable \n");
                        return 0;
                    }else
                        temp++;
                }
                //printf("its my temp:%d %d\n",temp,i);
                int size=temp-i;
                char* ar=(char*) malloc((size+1)*sizeof(char));
                int q=0;
                for(;q<size-1;q++){
                    ar[q]=a[i+q+1];
                }
                ar[q]='\0';
                int test=char_array_to_int(ar);
                test*=-1;
                res->arr[j].number=test;
                res->type[j]=1;
                j++;
                i=temp;
            }else{
                temp++;
                while(!type_of_element(a[temp])){
                    if(!is_digit(a[temp]) && !is_alpha(a[temp])){
                        printf("Invalid variable \n");
                        return 0;
                    }else
                        temp++;
                }
                printf("its my temp:%d %d\n",temp,i);
                int size=temp-i;
                char* ar=(char*) malloc((size+1)*sizeof(char));
                int q=0;
                for(;q<size;q++){
                    ar[q]=a[i+q];
                }
                ar[q]='\0';
                res->arr[j].variable=ar;
                res->type[j]=2;
                j++;
                i=temp;
            }
        }else if(is_digit(a[i])){
            int temp=i+1;
            while(!type_of_element(a[temp])){
                if(!is_digit(a[temp]) && !is_alpha(a[temp])){
                    printf("Invalid variable \n");
                    return 0;
                }else
                    temp++;
            }
            //printf("end of number:%d\n",temp);
            int size=temp-i;
            char* ar=(char*) malloc((size+1)*sizeof(char));
            int q=0;
            for(;q<size;q++){
                ar[q]=a[i+q];
            }
            ar[size+1]='\0';
            int test=char_array_to_int(ar);
            //printf("%d <- number in expr \n",test);
            res->arr[j].number=test;
            res->type[j]=1;
            j++;
            i=temp;
        }else  if(is_alpha(a[i])){
            int temp=i+1;
            while(!type_of_element(a[temp])){
                if(!is_digit(a[temp]) && !is_alpha(a[temp])){
                    printf("Invalid variable \n");
                    return 0;
                }else
                    temp++;
            }
            //printf("end of positive variable:%d\n",temp);
            int size=temp-i;
            char* ar=(char*)malloc(size*sizeof(char));
            int q=0;
            for(;q<size;q++){
                ar[q]=a[i+q];
            }
            ar[size]='\0';
            res->arr[j].variable=ar;
            res->type[j]=2;
            j++;
            i=temp;
        }
        if (type_of_element(a[i])) {
            unon temp;
            temp.operation = a[i];
            res->arr[j] = temp;
            res->type[j]=3;
            j++;
        }

    }
    res->size=j;
    return res;
}
void print_union_array(m ms){
    //printf("----uuuu %d uuuu-----\n",ms->size);
    int temp=ms->size;
    int i=0;
    for(i=0;i<temp;i++){
        switch(ms->type[i]){
            case 1:
                printf("%d ",ms->arr[i].number);
                break;
            case 2:
                printf("%s ",ms->arr[i].variable);
                break;
            case 3:
                printf("%c ",ms->arr[i].operation);
                break;
            default:
                break;
        }
    }
}
m dijkstra(m expr){
    stack st1=(stack)malloc(sizeof(s));
    m res=(m)malloc(sizeof(mass));
    res->arr=(unon*)malloc(expr->size*sizeof(unon));
    res->type=(int*)malloc(expr->size*sizeof(int));
    int n;
    int j=0,i=0;
    for(i=0;i<expr->size;i++){
        n=expr->type[i];
        switch(n){
            case 1:
                res->type[j]=expr->type[i];
                res->arr[j]=expr->arr[i];
                res->size++;
                j++;
                break;
            case 2:
                res->type[j]=expr->type[i];
                res->arr[j]=expr->arr[i];
                res->size++;
                j++;
                break;
            case 3:
                if(is_empty_stack(st1)){
                    push_back(st1,expr->arr[i]);
                    st1->type[st1->size-1]=3;
                } else {
                    int type = type_of_element(expr->arr[i].operation);
                    unon q = expr->arr[i];
                    /*10 - скобки
                     * 20 - (+ и -)
                     * 30 - (* и /)
                     * 40 - ^
                     * */
                    int cp = type_of_element(st1->cap.operation);
                    if (cp >= type && type!=10) {
                        res->arr[j]=st1->cap;
                        res->type[j]=3;
                        res->size++;
                        j++;
                        pop_back(st1);
                        /*while(type>=type_of_element(st1->cap.operation) && st1->cap.operation!='('){
                            res->arr[j]=st1->cap;
                            res->type[j]=3;
                            res->size++;
                            pop_back(st1);
                            j++;
                        }*/
                        push_back(st1,expr->arr[i]);
                        st1->type[st1->size-1]=3;
                    } else {
                        if (type == cp && !is_bracket(expr->arr[i].operation)) {
                            res->arr[j] = st1->cap;
                            res->type[j] = 3;
                            res->size++;
                            pop_back(st1);
                            push_back(st1, expr->arr[i]);
                            st1->type[st1->size - 1] = 3;
                            j++;
                        } else {
                            if (is_bracket(expr->arr[i].operation) && expr->arr[i].operation == ')') {
                                while (st1->cap.operation != '(') {
                                    res->arr[j] = st1->cap;
                                    res->type[j] = 3;
                                    res->size++;
                                    j++;
                                    pop_back(st1);
                                }
                                pop_back(st1);
                            } else {
                                push_back(st1, expr->arr[i]);
                            }
                        }
                    }
                }
                break;
            default:
                break;
        }
        //print_union_array(res);
        //printf("\n");
    }
    return res;
}
int bin_pow(int a,int n){
    int res = 1;
    while (n) {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}
void correction(m arr){
    int res=0,i=0;
    for(i=0;i<arr->size;i++){
        if(arr->type[i]==3 && arr->arr[i].operation=='(')
            res++;
        if(arr->type[i]==3 && arr->arr[i].operation==')')
            res--;
    }
    for(i=res;i<0;i++){
        printf("(");
    }
    print_union_array(arr);
    for(i=0;i<res;i++)
        printf(")");
}
void simplification(tr tree){
    if(tree->right && tree->left) {
        if (tree->left->type == 1 && tree->right->type == 1) {
            unon temp;
            switch (tree->a.operation) {
                case '+':
                    temp.number = tree->left->a.number + tree->right->a.number;
                    tree->a = temp;
                    tree->type=1;
                    tree->right = NULL;
                    tree->left = NULL;
                    break;
                case '-':
                    temp.number = tree->left->a.number - tree->right->a.number;
                    tree->a = temp;
                    tree->type=1;
                    tree->right = NULL;
                    tree->left = NULL;
                    break;
                case '*':
                    temp.number = tree->left->a.number * tree->right->a.number;
                    tree->a = temp;
                    tree->type=1;
                    tree->right = NULL;
                    tree->left = NULL;
                    break;
                case '/':
                    if(tree->right->a.number==0){
                        printf("Alarm divison by zero\n");

                    }else {
                        temp.number = tree->left->a.number / tree->right->a.number;
                        tree->a = temp;
                        tree->type = 1;
                        tree->right = NULL;
                        tree->left = NULL;
                    }
                    break;
                case '^':
                    temp.number = bin_pow(tree->left->a.number , tree->right->a.number);
                    tree->a = temp;
                    tree->type=1;
                    tree->right = NULL;
                    tree->left = NULL;
                    break;
                default:
                    break;
            }
        }
    }
    if(tree->right){
        simplification(tree->right);
    }
    if(tree->left){
        simplification(tree->left);
    }
}
void print_menu(){
    printf("|----------------------------------------------|\n");
    printf("   		     Menu                     \n");
    printf("|----------------------------------------------|\n");
    printf("0.Print menu	 \n");
    printf("1.Enter a formula		                   \n");
    printf("2.Print tree		                   \n");
    printf("3.Print postfix formula	   \n");
    printf("4.Simplification of tree	  	   \n");
    printf("5.Task		                   \n");
    printf("6.Quit                                       \n");
}
int count=0;
void task(tr tree){
    if (tree->left) {
        task(tree->left);
    }
    if(tree->type!=3)
        count++;
    if (tree->right) {
        task(tree->right);
    }
}
int is_correct(m arr){
    int n,i;
    for(i=0;i<arr->size-1;i++){
        n=arr->type[i];
        switch(n){
            case 1:
                if(arr->type[i+1]!=3){
                    return 0;
                }else{
                    if(arr->arr[i+1].operation=='('){
                        return 0;
                    }
                }
                break;
            case 2:
                if(arr->type[i+1]!=3){
                    return 0;
                }else{
                    if(arr->arr[i+1].operation=='('){
                        return 0;
                    }
                }
                break;
            case 3:
                if(arr->arr[i].operation=='('){
                    if(arr->arr[i+1].operation!='(' && arr->type[i+1]==3)
                        return 0;
                }else if(arr->arr[i].operation==')'){
                    if(arr->type[i+1]!=3 || arr->arr[i+1].operation=='(')
                        return 0;
                }else if(arr->type[i+1]==3 && !is_bracket(arr->arr[i+1].operation)){
                    return 0;
                }
                break;
        }
    }
    return 1;
}
int main(){
    char a[100];
    char r[]="(3+(4*2/(1-5)^2))";
    char d[]="(3*3^x)";
    m test;
    m test2;
    tr tree;
    m res=(m)malloc(sizeof(mass));
    res->arr=(unon*)malloc(50*sizeof(unon));
    res->type=(int*)malloc(50*sizeof(int));
    cnt=0;
    printf("\n");
    int x;
    while(1){
        scanf("%d",&x);
        switch(x){
            case 0:
                print_menu();
                break;
            case 1:
                scanf("%s",a);
                test=string_to_union_array(a);
                if(!is_correct(test)){
                    printf("Not correct expression");
                    return 0;
                }
                test2=dijkstra(test);
                cnt=test2->size-1;
                tree=build_tree(test2,0);

                printf("\n");
                break;
            case 2:
                res->size=0;
                cur=0;
                print_tree(tree,res);
                correction(res);
                printf("\n");
                break;
            case 3:
                print_union_array(test2);
                printf("\n");
                break;
            case 4:
                simplification(tree);
                break;
            case 5:
                count=0;
                task(tree);
                printf("The answer is %d\n",count);
                break;
            default:
                return 0;
        }
    }
}
