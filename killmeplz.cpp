#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <stdio.h>

typedef unsigned long long i64;
char filename[20] = "dictionaryAVLtree";
int flagI = 1;
int flagR = 1;
int isDel = 0;

typedef struct node {
    char key[257];
    i64 value;
    node* left;
    node* right;
    int balance;
    node(char* k, i64 vl) {
        strcpy(key, k);
        value = vl;
        left = NULL;
        right = NULL;
        balance = 0;
    }
} Node;

node* RotateToLeft(node* root) {
    node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    return temp;

}

node* RotateToRight(node* root) {
    node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    return temp;
}

node* FixBalance(node* root) {
    int rb = root->balance;
    if (rb == -2) {
        int cb = (root->right)->balance;
        if (cb == -1) {
            root->balance += 2;
            (root->right)->balance += 1;
            root = RotateToLeft(root);
        } else if (cb == 0) {
            root->balance += 1;
            (root->right)->balance += 1;
            root = RotateToLeft(root);
        } else if (cb == 1) {
            int ind = ((root->right)->left)->balance;
            if (ind == 1) {
                root->balance += 2;
                (root->right)->balance -= 2;
                ((root->right)->left)->balance -= 1;
            } else if (ind == 0) {
                root->balance += 2;
                (root->right)->balance -= 1;
            } else if (ind == -1) {
                root->balance += 3;
                (root->right)->balance -= 1;
                ((root->right)->left)->balance += 1;
            } else {
                std::cout << "Do not know this case." << std::endl;
                exit(4);
            }
            root->right = RotateToRight(root->right);
            root = RotateToLeft(root);
        } else {
            std::cout << "Do not know this case." << std::endl;
            exit(1);
        }
    } else if (rb == 2) {
        int cb = (root->left)->balance;
        if (cb == 1) {
            root->balance -= 2;
            (root->left)->balance -= 1;
            root = RotateToRight(root);
        } else if (cb == 0) {
            root->balance -= 1;
            (root->left)->balance -= 1;
            root = RotateToRight(root);
        } else if (cb == -1) {
            int ind = ((root->left)->right)->balance;
            if (ind == -1) {
                root->balance -= 2;
                (root->left)->balance += 2;
                ((root->left)->right)->balance += 1;
            } else if (ind == 0) {
                root->balance -= 2;
                (root->left)->balance += 1;
            } else if (ind == -1) {
                root->balance -= 3;
                (root->left)->balance += 1;
                ((root->left)->right)->balance -= 1;
            } else {
                std::cout << "Do not know this case." << std::endl;
                exit(3);
            }
            root->left = RotateToLeft(root->left);
            root = RotateToRight(root);

        } else {
            std::cout << "Do not know this case." << std::endl;
            exit(2);
        }
    }
    return root;
}

node* Insert(char* k, i64 vl, node* root) {
    flagI = 1;
    if (!root) {
        std::cout << "OK" << std::endl;
        return new node(k, vl);
    }
    if (strcmp(k, root->key) > 0) {
        root->right = Insert(k, vl, root->right);
        if (flagI) {
            root->balance -= 1;
        }
        if (root->balance == 0 || root->balance == -2) {
            flagI = 0;
        }
    } else if (strcmp(k, root->key) < 0){
        root->left = Insert(k, vl, root->left);
        if (flagI) {
            root->balance += 1;
        }
        if (root->balance == 0 || root->balance == 2) {
            flagI = 0;
        }
    } else {
        std::cout << "Exist" << std::endl;
        flagI = 0;
        return root;
    }
    return FixBalance(root);
}

void MinNode(node* root, node* mN) {
    if (root->left) {
        MinNode(root->left, mN);
    } else {
        strcpy(mN->key, root->key);
        mN->value = root->value;
    }
}

node* RemoveMin(node* root) {
    if (!root->left) {
        //delete root; перед этим скопироват в minNode
        return root->right;
    }
    if (root->left) {
        root->left = RemoveMin(root->left);
        if (!isDel) {
            root->balance -= 1;
            if (root->balance == -1 || root->balance == +1) {
                flagR = 0;
            }
            isDel = 1;
            return FixBalance(root);
        }
        if (flagR) {
            root->balance -= 1;
        }
        if (root->balance == -1 || root->balance == +1) {
            flagR = 0;
        }
    }
    return FixBalance(root);
}

node* Remove(char* k, node* root) {
    flagR = 1;
    if (!root) {
        std::cout << "NoSuchWord" << std::endl;
        flagR = 0;
        return NULL;
    }
    if (strcmp(k, root->key) > 0) {
        root->right = Remove(k, root->right);
        if (flagR) {
            root->balance += 1;
        }
        if (root->balance == -1 || root->balance == +1) {
            flagR = 0;
        }
    } else if (strcmp(k, root->key) < 0) {
        root->left = Remove(k, root->left);
        if (flagR) {
            root->balance -= 1;
        }
        if (root->balance == -1 || root->balance == +1) {
            flagR = 0;
        }
    } else {
        node* lt = root->left;
        node* rt = root->right;
        int bl = root->balance;
        delete root;
        if(!rt) {
            return lt;
        }
        char temp[2] = " ";
        node* minNode = new node(temp,0);
        MinNode(rt, minNode);
        minNode->balance = bl;
        minNode->right = RemoveMin(rt);
        minNode->left = lt;
        if (flagR) {
            minNode->balance += 1;
        }
        if (minNode->balance == 1 || minNode->balance == -1) {
            flagR = 0;
        }
        std::cout << "OK" << std::endl;
        return FixBalance(minNode);
    }
    return FixBalance(root);
}

void Find(char* k, node* root) {
    if (!root) {
        std::cout << "NoSuchWord" << std::endl;
    } else {
        if (strcmp(k, root->key) > 0) {
            Find(k, root->right);
        } else if (strcmp(k, root->key) < 0) {
            Find(k, root->left);
        } else {
            std::cout << "OK: " << root->value << std::endl;
        }
    }
}

void Print(node* root, int i) {
    if (root) {
        Print(root->right, i+1);
        for (int k = 0; k < i; k++) {
            std::cout << "  ";
        }
        std::cout << root->key << "\t" << root->value << ", balance: " << root->balance <<std::endl;
        Print(root->left, i+1);
	}
}

void Serialise(node* root) {
    char nll= 'z';
    char leaf = 'l';
    char notLeaf = 'n';
    FILE* f;
    //f = fopen(filename, "ab");
    //if (f) {
        if (!root) { // if null
            //std::cout << "add only nll z" << std::endl;
            f = fopen(filename, "ab");
            if (f) {
                std::cout << "add: " << nll << std::endl;
                fwrite(&nll, sizeof(char), 1, f);
            } else {
                std::cout << "ERROR: can not save tree." << std::endl;
            }
            if (fclose(f) == EOF) {
                std::cout << "ERROR: can not save tree." << std::endl;
            } else {
                //std::cout << "closed" << std::endl;
            }

        } else { // not null
            if (!root->right && !root->left) { // leaf
                //std::cout << "add leaf l and node" << std::endl;
                f = fopen(filename, "ab");
                if (f) {
                    std::cout << "add: " << leaf << ", " << root->key << ", " << root->value << ", " << root->balance << std::endl;
                    fwrite(&leaf, sizeof(char), 1, f);
                    fwrite(&(root->key), 258 * sizeof(char), 1, f);
                    fwrite(&(root->value), sizeof(i64), 1, f);
                    fwrite(&(root->balance), sizeof(int), 1, f);
                } else {
                    std::cout << "ERROR: can not save tree." << std::endl;
                }
                if (fclose(f) == EOF) {
                    std::cout << "ERROR: can not save tree." << std::endl;
                } else {
                    //std::cout << "closed" << std::endl;
                }

            } else { // there is left or right node
                //std::cout << "add not leaf n, node and left with right" << std::endl;
                f = fopen(filename, "ab");
                if (f) {
                    std::cout << "add: " << notLeaf << ", " << root->key << ", " << root->value << ", " << root->balance << std::endl;
                    fwrite(&notLeaf, sizeof(char), 1, f);
                    fwrite(&(root->key), 258 * sizeof(char), 1, f);
                    fwrite(&(root->value), sizeof(i64), 1, f);
                    fwrite(&(root->balance), sizeof(int), 1, f);
                } else {
                    std::cout << "ERROR: can not save tree." << std::endl;
                }
                if (fclose(f) == EOF) {
                    std::cout << "ERROR: can not save tree." << std::endl;
                } else {
                    //std::cout << "closed" << std::endl;
                }
                Serialise(root->left);
                Serialise(root->right);
            }
        }
/*    } else {
        std::cout << "ERROR: can not save tree." << std::endl;
    }
    if (fclose(f) == EOF) {
        std::cout << "ERROR: can not save tree." << std::endl;
    } else {
        //std::cout << "closed" << std::endl;
    }
    */
}

void Pr() {
    FILE* f;
    f = fopen(filename, "rb");
    if (f) {
        if (getc(f) == EOF) {
            std::cout << "empty" << std::endl;
        } else {
            rewind(f);
            struct node q("", 0);
            char lf;
            while( (lf = getc(f)) != EOF ) {
                //fread(&lf, sizeof(char), 1, f);
                std::cout << "is leaf? " << lf << std::endl;
                if (lf != 'z') {
                    //std::cout << "not null" << std::endl;
                    fread(&(q.key), 258 * sizeof(char), 1, f);
                    fread(&(q.value), sizeof(i64), 1, f);
                    fread(&(q.balance), sizeof(int), 1, f);
                    std::cout << " key: " << q.key << ", value: " << q.value << ", balance: " << q.balance << std::endl;
                } else {
                    std::cout << "NULL" << std::endl;
                }
            }
        }
    } else {
        std::cout << "ERROR: can not load tree." << std::endl;
    }
    if (fclose(f) == EOF) {
        std::cout << "ERROR: can not save tree." << std::endl;
    } else {
        //std::cout << "closed" << std::endl;
    }
}

node* Deserialise() {
    FILE* f;
    f = fopen(filename, "rb");
    if (f) {
        if (getc(f) == EOF) {
            std::cout << "empty" << std::endl;
        } else {
            rewind(f);
            struct node qq("", 0);
            struct node* q = &qq;
            char lf;
            while( (lf = getc(f)) != EOF ) {
                std::cout << "is leaf? " << lf << std::endl;
                if (lf != 'z') {
                    //std::cout << "sizeof q->key: " << sizeof(q->key) << ", sizeof &q->key: " << sizeof(&(q->key))
                    //<< ", sizeof *q->key: " << sizeof(*(q->key)) << std::endl;
                    char k[257];
                    //char* p;
                    //char* kk;
                    //p = k;
                    //i64 v;
                    //int b;
                    fread(&q->key, 257 * sizeof(char), 1, f);
                    fread(&q->value, sizeof(i64), 1, f);
                    fread(&q->balance, sizeof(int), 1, f);
                    //std::cout << "here, key is: " << q->key << std::endl;
                    //std::cout << "sizeof k: " << sizeof(k) << std::endl;
                    //std::cout << "sizeof q->key: " << sizeof(q->key) << std::endl;
                    /*
                    for (int i = 0; i < sizeof(q->key); i++) {
                        q->key[i] = k[i];
                        std::cout << i << std::endl;
                    }
                    */
                    //q->key = strcpy(q->key, k);
                    //std::cout << "here2" << std::endl;

                    std::cout << " key: " << q->key << ", value: " << q->value << ", balance: " << q->balance << std::endl;
                    q->left = Deserialise();
                    q->right = Deserialise();
                    return q;
                } else {
                    std::cout << "NULL" << std::endl;
                    return NULL;
                }
            }
        }
    } else {
        std::cout << "ERROR: can not load tree." << std::endl;
    }
    if (fclose(f) == EOF) {
        std::cout << "ERROR: can not save tree." << std::endl;
    } else {

    }
}

int main() {
    struct node* root = NULL;
    char action;
    while(std::cin >> action) {
        if(action == '+') {
            char str[256];
            i64 num;
            std::cin >> str >> num;
            std::transform(str, str+strlen(str), str, (int (*)(int))std::tolower);
            root = Insert(str, num, root);
            Print(root, 0);
        } else if (action == '-') {
            char str[256];
            std::cin >> str;
            std::transform(str, str+strlen(str), str, (int (*)(int))std::tolower);
            root = Remove(str,root);
            Print(root, 0);
        } else if (action == '!') {

        } else {
            ungetc(action, stdin);
            char str[256];
            std::cin >> str;
            std::cout << "word is " << str << std::endl;
            Find(str, root);
        }
    }

/*
    FILE* mf;
    std::cout << "errno1 " << errno << std::endl;
    mf = fopen("dictionaryAVLtree", "wb");
    std::cout << "errno2 " << errno << std::endl;
    if (mf) {
        if (!root->right && !root->left) { // leaf
            fwrite(&(root->key), 258 * sizeof(char), 1, mf);
            fwrite(&(root->value), sizeof(i64), 1, mf);
            fwrite(&(root->balance), sizeof(int), 1, mf);
        }
    } else {
        std::cout << "ERROR: can not save tree." << std::endl;
    }
    if (fclose(mf) == EOF) std::cout << "error! can not close" << std::endl;
    else std::cout << "closed1" << std::endl;

    mf = fopen("dictionaryAVLtree", "rb");
    if (mf) {
        if (getc(mf) == EOF) {
            std::cout << "empty" << std::endl;
        } else {
            rewind(mf);
            struct node q("",0);
            fread(&(q.key), 258 * sizeof(char), 1, mf);
            fread(&(q.value), sizeof(i64), 1, mf);
            fread(&(q.balance), sizeof(int), 1, mf);
            std::cout << " key: " << q.key << ", value: " << q.value << ", balance: " << q.balance << std::endl;
            if (getc(mf) == EOF) std::cout << "eof" << std::endl;
            if (fclose(mf) == EOF) std::cout << "error! can not close" << std::endl;
            else std::cout << "closed" << std::endl;
        }
    } else {
        std::cout << "ERROR: can not load tree." << std::endl;
    }

*/

    FILE* f;
    f = fopen(filename, "wb");
    fclose(f);
    Serialise(root);
    std::cout << "saved" << std::endl;
    root = Deserialise();
    std::cout << "loaded" << std::endl;
    //Pr();
    return 0;
}
