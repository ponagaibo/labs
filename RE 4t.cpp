#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <stdio.h>

typedef unsigned long long i64;
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
                std::cout << "Unknown case." << std::endl;
                exit(1);
            }
            root->right = RotateToRight(root->right);
            root = RotateToLeft(root);
        } else {
            std::cout << "Unknown case." << std::endl;
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
                std::cout << "Unknown case." << std::endl;
                exit(1);
            }
            root->left = RotateToLeft(root->left);
            root = RotateToRight(root);

        } else {
            std::cout << "Unknown case." << std::endl;
            exit(1);
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
        delete root;
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

void Serialise(node* root, FILE* f) {
    char nll= 'z';
    char leaf = 'l';
    char notLeaf = 'n';
    if (!root) {
        fwrite(&nll, sizeof(char), 1, f);
    } else {
        if (!root->right && !root->left) {

            fwrite(&leaf, sizeof(char), 1, f);
            fwrite(&(root->key), 258 * sizeof(char), 1, f);
            fwrite(&(root->value), sizeof(i64), 1, f);
            fwrite(&(root->balance), sizeof(int), 1, f);
        } else {
            fwrite(&notLeaf, sizeof(char), 1, f);
            fwrite(&(root->key), 258 * sizeof(char), 1, f);
            fwrite(&(root->value), sizeof(i64), 1, f);
            fwrite(&(root->balance), sizeof(int), 1, f);
            Serialise(root->left, f);
            Serialise(root->right, f);
        }
    }
}

node* Deserialise(FILE* f) {
    char lf;
    if ((lf = getc(f)) != EOF ) {
        if (lf != 'z') {
            char k[257];
            i64 v;
            int b;
            fread(&k, 258 * sizeof(char), 1, f);
            fread(&v, sizeof(v), 1, f);
            fread(&b, sizeof(b), 1, f);
            node* res = (node*)malloc(sizeof(node) * 1);
            strcpy(res->key, k);
            res->value = v;
            res->balance = b;
            res->left = NULL;
            res->right = NULL;
            if (lf != 'l') {
                res->left = Deserialise(f);
                res->right = Deserialise(f);
            }
            return res;
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

int main() {
    FILE* f;
    struct node* root = NULL;
    char action;
    while(std::cin >> action) {
        if(action == '+') {
            char str[256];
            i64 num;
            std::cin >> str >> num;
            std::transform(str, str+strlen(str), str, (int (*)(int))std::tolower);
            root = Insert(str, num, root);
        } else if (action == '-') {
            char str[256];
            std::cin >> str;
            std::transform(str, str+strlen(str), str, (int (*)(int))std::tolower);
            root = Remove(str,root);
        } else if (action == '!') {
            char act[5];
            char path[256];
            std::cin >> act >> path;
            if (!strcmp(act, "Load")) {
                f = fopen(path, "rb");
                if (f) {
                    rewind(f);
                    root = Deserialise(f);
                } else {
                    std::cout << "ERROR: can not open (load) tree." << std::endl;
                }
                if (fclose(f) == EOF) {
                    std::cout << "ERROR: can not load tree." << std::endl;
                }
            } else if (!strcmp(act, "Save")) {
                f = fopen(path, "wb");
                fclose(f);
                f = fopen(path, "ab");
                if (f) {
                    rewind(f);
                    Serialise(root, f);
                } else std::cout << "ERROR: can not save tree." << std::endl;
                if (fclose(f) == EOF) {
                    std::cout << "ERROR: can not save tree." << std::endl;
                }
            } else std::cout << "ERROR: unknown command." << std::endl;
        } else {
            ungetc(action, stdin);
            char str[256];
            std::cin >> str;
            std::transform(str, str+strlen(str), str, (int (*)(int))std::tolower);
            Find(str, root);
        }
    }
    return 0;
}
