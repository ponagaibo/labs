#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio_ext.h>
#include "zmq.h"

#define SEED (unsigned int)(time(NULL)*(rand()%10000))
#define MESSAGE_SIZE 256
char** myArea;
char** enemyArea;

char* playerID;
char* adr;

int CheckNear(int a, int b) {
    if (myArea[a][b] == 'o') return 0;
    if (a != 9) {
        if (myArea[a+1][b] == 'o') return 0;
        if (b != 0) {
            if (myArea[a][b-1] == 'o' || myArea[a+1][b-1] == 'o') return 0;
        }
        if (b != 9) {
            if (myArea[a][b+1] == 'o' || myArea[a+1][b+1] == 'o') return 0; 
        }
    }
    if (a != 0) {
        if (myArea[a-1][b] == 'o') return 0;
        if (b != 9) {
            if (myArea[a-1][b+1] == 'o' || myArea[a][b+1] == 'o') return 0;
        }
        if (b != 0) {
            if (myArea[a-1][b-1] == 'o' || myArea[a][b-1] == 'o') return 0; 
        }
    }
    return 1;
}

void CopyPrint(char** area, char* from, int copy) {
    int i, j;
    printf("\n  ");
    for (i = 0; i < 10; i++) printf("%d ", i);
    printf("\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", i);
        for (j = 0; j < 10; j++) {
            if (copy) area[i][j] = from[i * 10 + j];
            printf("%c ", area[i][j]);
        }
        printf("\n");
    }
}

void RandomSet(const int flag) {
    int k, a, b, i, temp, r;
    for (k = 4; k > 0; k--) {
        int amount = 5 - k;
        while (amount) {
            if (flag) {
                srand(SEED);
                a = rand() % 10;
                b = rand() % 10;
                r = rand();
            } else {
                __fpurge(stdin);
                printf("Still have %d %d-decker ships to set\n", amount, k);
                printf("Enter orientation (1 - vertical, 0 - horizontal)\n>");
                scanf("%1d", &r);
                printf("Enter coordinats of first ship decker:\n>");
                __fpurge(stdin);
                scanf("%1d", &a);
                __fpurge(stdin);
                scanf("%1d", &b);
            }
            temp = 0;
            if ((r % 2) == 0 && b + k - 1 <= 9) {
                for (i = 0; i < k; i++) {
                    if (CheckNear(a, b + i)) temp++;
                    else break;
                }
                if (temp == k) {
                    for (i = 0; i < k; i++)
                        myArea[a][b + i] = 'o';
                    amount--;
                }
            } else if ((r % 2) != 0 && a + k - 1 <= 9) {
                for (i = 0; i < k; i++) {
                    if (CheckNear(a + i, b)) temp++;
                    else break;
                }
                if (temp == k) {
                    for (i = 0; i < k; i++)
                        myArea[a + i][b] = 'o';
                    amount--;
                }
            } else if (!flag) printf("Wrong coordinats, try again\n");
            if (!flag) CopyPrint(myArea, 0, 0);
        }
    }
}

void Init() {
    int i, j;
    adr = (char*)malloc(32 * sizeof(char));
    myArea = (char**)malloc(10 * sizeof(char*));
    enemyArea = (char**)malloc(10 * sizeof(char*));
    for (i = 0; i < 10; i++) {
        myArea[i] = (char*)malloc(11 * sizeof(char));
        enemyArea[i] = (char*)malloc(11 * sizeof(char));
    }
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            myArea[i][j] = '~';
            enemyArea[i][j] = '~';
        }
    }
}

void Free() {
    int i;
    for (i = 0; i < 10; i++) {
        free(myArea[i]);
        free(enemyArea[i]);
    }
    free(myArea);
    free(enemyArea);
    free(adr);
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Error! You should set your ID (> 0) and port number (> 1024).\n");
        return -1;
    }
    int tempAdr, tempID;
    tempID = atoi(argv[1]);
    if (tempID == 0) {
        printf("Wrong ID! Try again.\n");
        return -1;
    }
    tempAdr = atoi(argv[2]);
    if (tempAdr <= 1024) {
        printf("Wrong port number! Try again.\n");
        return -1;
    }
    Init();
    strcpy(adr, "tcp://localhost:");
    strcat(adr, argv[2]);
    void* context = zmq_ctx_new();
    if (context == NULL) {
        printf("Can not create context.\n");
        return -1;
    }
    void* request = zmq_socket(context, ZMQ_REQ);
    if (request == NULL) {
        printf("Can not create socket (request).\n");
        return -1;
    }
    if (zmq_connect(request, adr) == -1) {
        printf("Can not connect.\n");
        return -1;
    }
    printf("Do you want set ships yourself (0) or randomly (1)?\n>");
    int randomly = 0;
    scanf("%1d", &randomly);
    RandomSet(randomly);
    int i, j;
//...............FIRST AREA................................
    char tmp[MESSAGE_SIZE];
    char msg[MESSAGE_SIZE];
    char OK[3] = "OK";
    strcpy(tmp, "");
    strcat(tmp, argv[1]);
    sprintf(msg, " area ");
    strcat(tmp, msg);
    for (i = 0; i < 10; i++) strcat(tmp, myArea[i]);
    if (zmq_send(request, tmp, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not send message.\n");
        Free();
        return -1;
    }
    memset(tmp, 0, MESSAGE_SIZE);
    if (zmq_recv(request, tmp, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not receive message.\n");
        Free();
        return -1;
    }
    printf("%s\n", tmp);
    if (!strcmp(tmp, "You have the first turn") || !strcmp(tmp, "You have the second turn")) {
        if (zmq_send(request, OK, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not send message.\n");
            Free();
            return -1;
        }
    }
//.........................................................
    char enem[MESSAGE_SIZE];
    char tempAns[MESSAGE_SIZE];
    char check[MESSAGE_SIZE];
    while (!feof(stdin)) {
        memset(tmp, 0, MESSAGE_SIZE);
        if (zmq_recv(request, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            Free();
            return -1;
        }
        sscanf(tmp, "%s %s", tempAns, enem);
        printf("%s\n", tempAns);
        if (!strcmp(tempAns, "wait")) {
            printf("Turn of another player:\n");
            printf("\tYOUR AREA");
            CopyPrint(myArea, enem, 1);
        } else if (!strcmp(tempAns, "your_turn")) {
            printf("\tYOUR AREA");
            CopyPrint(myArea, enem, 1);
            printf("Your turn:\n");
            printf("\tENEMY");
            CopyPrint(enemyArea, enem, 0);
        } else if (!strcmp(tempAns, "killed") || !strcmp(tempAns, "injured")) {
            printf("\tYOUR AREA");
            CopyPrint(myArea, enem, 0);
            printf("Your turn:\n");
            printf("\tENEMY");
            CopyPrint(enemyArea, enem, 1);
        } else if (!strcmp(tempAns, "miss")) {
            printf("\tENEMY");
            CopyPrint(enemyArea, enem, 1);
            printf("Turn of another player:\n");
        } else if (!strcmp(tempAns, "marked")) {
            printf("Choose another cell\n");
        }
        if (!strcmp(tempAns, "your_turn") || !strcmp(tempAns, "killed") || !strcmp(tempAns, "injured") || !strcmp(tempAns, "marked")) {
            while (1) {
                __fpurge(stdin);
                printf("\nEnter your command:\n>");
                fgets(msg, MESSAGE_SIZE, stdin);
                int tmpL = 0;
                int tmpC = 0;
                strcpy(tmp, msg);
                sscanf(msg, "%s %d %d", check, &tmpL, &tmpC);
                if (strcmp(check, "shoot")) printf("Wrong command!\n");
                if (!strcmp(check, "shoot") && tmpL >= 0 && tmpL <= 9 && tmpC >= 0 && tmpC <= 9) 
                    break;
                else printf("Wrong coordinates!\n");
            }
            if (zmq_send(request, tmp, MESSAGE_SIZE, 0) == -1) {
                printf("Error! Can not send message.\n");
                Free();
                return -1;
            }
        } else if (!strcmp(tempAns, "miss") || !strcmp(tempAns, "wait")) {
            printf("Wait for your turn\n");
            if (zmq_send(request, OK, MESSAGE_SIZE, 0) == -1) {
                printf("Error! Can not send message.\n");
                Free();
                return -1;
            }
        } else if (!strcmp(tempAns, "won")) {
            printf("You win!\n");
            if (zmq_send(request, OK, MESSAGE_SIZE, 0) == -1) {
                printf("Error! Can not send message.\n");
                Free();
                return -1;
            }
            return 0;
        } else if (!strcmp(tempAns, "lost")) {
            printf("You lose!\n");
            if (zmq_send(request, OK, MESSAGE_SIZE, 0) == -1) {
                printf("Error! Can not send message.\n");
                Free();
                return -1;
            }
            return 0;
        } else {
            printf("Unknown command\n");
            sprintf(tmp, "error");
            if (zmq_send(request, OK, MESSAGE_SIZE, 0) == -1) {
                printf("Error! Can not send message.\n");
                Free();
                return -1;
            }
        }
    }
    zmq_close(request);
    zmq_ctx_destroy(context);
    Free();
    return 0;
}
