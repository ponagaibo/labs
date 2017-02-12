#include <stdlib.h>
#include <string>
#include <iostream>
#include "STree.h"

TNode *NewNode(int start, int* end) {
    TNode* node =(TNode*)malloc(sizeof(TNode));
    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        node->child[i] = NULL;
    }
    node->suffLink = root;
    node->start = start;
    node->end = end;
    node->suffIndex = -1;
    return node;
}
 
int EdgeLength(TNode* n) {
    return *(n->end) - (n->start) + 1;
}

void Extend(int pos) {
    leafEnd = pos;
    suffCount++;
    lastNewNode = NULL;
    while(suffCount > 0) {
        if (curLength == 0) {
            curEdge = pos;
        }
        if (curNode->child[(int)patt[curEdge] - 97] == NULL) {
            curNode->child[(int)patt[curEdge] - 97] = NewNode(pos, &leafEnd);
            if (lastNewNode != NULL) {
                lastNewNode->suffLink = curNode;
                lastNewNode = NULL;
            }
        } else {
            TNode* next = curNode->child[(int)patt[curEdge] - 97];
            int len = EdgeLength(next);
            if (curLength >= len) {
                curEdge += len;
                curLength -= len;
                curNode = next;
                continue;
            }
            if (patt[next->start + curLength] == patt[pos]) {
                if (lastNewNode != NULL && curNode != root) {
                    lastNewNode->suffLink = curNode;
                    lastNewNode = NULL;
                }
                curLength++;
                break;
            }
            splitEnd = (int*)malloc(sizeof(int));
            *splitEnd = next->start + curLength - 1;
            TNode* split = NewNode(next->start, splitEnd);
            curNode->child[(int)patt[curEdge] - 97] = split;
            split->child[(int)patt[pos] - 97] = NewNode(pos, &leafEnd);
            next->start += curLength;
            split->child[(int)patt[next->start] - 97] = next;
            if (lastNewNode != NULL) {
                lastNewNode->suffLink = split;
            }
            lastNewNode = split;
        }
        suffCount--;
        if (curNode == root && curLength > 0) {
            curLength--;
            curEdge = pos - suffCount + 1;
        }
        else if (curNode != root) {
            curNode = curNode->suffLink;
        }
    }
}
 
void SetIndex(TNode* n, int labelHeight) {
    if (n == NULL) {
        return;
    }
    int leaf = 1;
    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        if (n->child[i] != NULL) {
            leaf = 0;
            SetIndex(n->child[i], labelHeight + EdgeLength(n->child[i]));
        }
    }
    if (leaf == 1) {
        n->suffIndex = patSize - labelHeight;
    }
}
 
void Delete(TNode* n) {
    if (n == NULL) {
        return;
    }
    int i;
    for (i = 0; i < MAX_CHAR; i++) {
        if (n->child[i] != NULL) {
            Delete(n->child[i]);
        }
    }
    if (n->suffIndex == -1) {
        free(n->end);
    }
    free(n);
}
 
void Build() {
    patSize = patt.length();
    int i;
    rootEnd = (int*)malloc(sizeof(int));
    *rootEnd = -1;
    root = NewNode(-1, rootEnd);
    curNode = root;
    for (i = 0; i < patSize; i++) {
        Extend(i);
    }
    int labelHeight = 0;
    SetIndex(root, labelHeight);
}

void MatchStat() {
    int textSize = text.length();
    int iter = 0;
    curNode = root;
    curLength = 0;
    int i, len;
    TNode* next = NULL;
    for (i = 0; i < textSize; i++) {
        next = curNode->child[(int)text[iter - curLength] - 97];
        if (iter == textSize) {
            next = NULL;
        }
        if (next && next->start + curLength < patSize) {
            while (next && patt[next->start + curLength] == text[iter]) {
                curLength++;
                iter++;
                len = EdgeLength(next);
                if (curLength >= len) {
                    if (next->suffIndex != -1) {
                        break;
                    }
                    curLength -= len;
                    curNode = next;
                    if (iter == textSize) {
                        break;
                    }
                    next = curNode->child[(int)text[iter - curLength] - 97];
                }
                if (iter == textSize) {
                    break;
                }
            }
        }
        if (iter - i == patSize) {
            std::cout << i + 1 << std::endl;
        }
        if (curNode == root && curLength > 0) {
            curLength--;
        } else if (curNode != root) {
            curNode = curNode->suffLink;
            if (next) {
                while (curNode != root && iter - curLength > textSize) {
                    if (patt[next->start + curLength] == text[iter]) {
                        break;
                    }
                    i++;
                    if (iter - i == patSize) {
                        std::cout << i + 1 << std::endl;
                    }
                    curNode = curNode->suffLink;
                }
            }
        }
        if (iter == i) {
            iter++;
        }
    }
}
 
int main(int argc, char* argv[]) {
    std::cin >> patt;
    Build();
    std::cin >> text;
    int textSize = text.length();
    if (textSize == 0) {
        std::cout << "ERROR: empty text." << std::endl;
        patt.clear();
        text.clear();
        free(rootEnd);
        Delete(root);
        return -1;
    }
    MatchStat();
    Delete(root);
    return 0;
}