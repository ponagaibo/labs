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
                    for (i = 0; i < k; i++) myArea[a][b + i] = 'o';
                    amount--;
                }
            } else if ((r % 2) != 0 && a + k - 1 <= 9) {
                for (i = 0; i < k; i++) {
                    if (CheckNear(a + i, b)) temp++;
                    else break;
                }
                if (temp == k) {
                    for (i = 0; i < k; i++) myArea[a + i][b] = 'o';
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
        memset(myArea[i], 0, 11);
        memset(enemyArea[i], 0, 11);
        for (j = 0; j < 11; j++) {
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

int Send(void* socket, char* ans) {
    if (zmq_send(socket, ans, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not send message.\n");
        Free();
        return -1;
    } else return 0;
}

int Receive(void* socket, char* msg) {
    if (zmq_recv(socket, msg, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not receive message.\n");
        Free();
        return -1;
    } else return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error! You should set your ID (> 0) and port number (> 1024).\n");
        return -1;
    }
    int tempID;
    tempID = atoi(argv[1]);
    if (tempID == 0) {
        printf("Wrong ID! Try again.\n");
        return -1;
    }
    char* mainAdr;
    strcpy(mainAdr, "tcp://localhost:1024");
    void* mainContext = zmq_ctx_new();
    if (mainContext == NULL) {
        printf("Can not create mainContext.\n");
        return -1;
    }
    void* mainSocket = zmq_socket(mainContext, ZMQ_REQ);
    if (mainSocket == NULL) {
        printf("Can not create socket (mainSocket).\n");
        return -1;
    }
    if (zmq_connect(mainSocket, mainAdr) == -1) {
        printf("Can not connect.\n");
        return -1;
    }
    char tmp[MESSAGE_SIZE];
    char msg[MESSAGE_SIZE];
    char portNum[6];
    strcpy(tmp, "port");
    if (Send(mainSocket, tmp)) return -1;
    memset(tmp, 0, MESSAGE_SIZE);
    if (Receive(mainSocket, tmp)) return -1;
    sscanf(tmp, "%s %s", msg, portNum);
    if (!strcmp(msg, "error")) {
        printf("Error!\n");
        return -1;
    }
    zmq_close(mainSocket);
    zmq_ctx_destroy(mainContext);
    Init();
    strcpy(adr, "tcp://localhost:");
    strcat(adr, portNum);
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
    char OK[3] = "OK";
    strcpy(tmp, "");
    strcat(tmp, argv[1]);
    sprintf(msg, " area ");
    strcat(tmp, msg);
    char tempChar[11];
    for (i = 0; i < 10; i++) {
        memset(tempChar, 0, 11);
        for (j = 0; j < 10; j++) tempChar[j] = myArea[i][j];
        strcat(tmp, tempChar);
    }
    if (Send(request, tmp)) return -1;
    memset(tmp, 0, MESSAGE_SIZE);
    if (Receive(request, tmp)) return -1;
    printf("%s\n", tmp);
    if (!strcmp(tmp, "You have the first turn") || !strcmp(tmp, "You have the second turn")) {
        if (Send(request, OK)) return -1;
    }
//.........................................................
    char enem[MESSAGE_SIZE];
    char tempAns[MESSAGE_SIZE];
    char check[10];
    while (!feof(stdin)) {
        memset(tmp, 0, MESSAGE_SIZE);
        strcpy(tmp, "");
        if (Receive(request, tmp)) return -1;
        memset(enem, 0, MESSAGE_SIZE);
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
        } else if (!strcmp(tempAns, "marked")) printf("Choose another cell\n");
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
            if (Send(request, tmp)) return -1;
        } else if (!strcmp(tempAns, "miss") || !strcmp(tempAns, "wait")) {
            printf("Wait for your turn\n");
            if (Send(request, OK)) return -1;
        } else if (!strcmp(tempAns, "won")) {
            printf("You win!\n");
            if (Send(request, OK)) return -1;
            return 0;
        } else if (!strcmp(tempAns, "lost")) {
            printf("You lose!\n");
            if (Send(request, OK)) return -1;
            return 0;
        } else {
            printf("Unknown command\n");
            sprintf(tmp, "error");
            if (Send(request, OK)) return -1;
        }
    }
    zmq_close(request);
    zmq_ctx_destroy(context);
    Free();
    return 0;
}
