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

int CheckNear(int a, int b) {
    if (myArea[a][b] == 'o') return 0;
    if (a > 0 && a < 9) {
        if (myArea[a-1][b] == 'o' || myArea[a+1][b] == 'o') return 0;
        if (b > 0 && b < 9) {
            if (myArea[a-1][b+1] == 'o' || myArea[a-1][b-1] == 'o') return 0;
            if (myArea[a][b+1] == 'o' || myArea[a][b-1] == 'o') return 0;
            if (myArea[a+1][b+1] == 'o' || myArea[a+1][b-1] == 'o') return 0;
        }
        if (b == 0) {
            if (myArea[a-1][b+1] == 'o') return 0;
            if (myArea[a][b+1] == 'o') return 0;
            if (myArea[a+1][b+1] == 'o') return 0;
        }
        if (b == 9) {
            if (myArea[a-1][b-1] == 'o') return 0;
            if (myArea[a][b-1] == 'o') return 0;
            if (myArea[a+1][b-1] == 'o') return 0;
        }
    }
    if (a == 0) {
        if (myArea[a+1][b] == 'o') return 0;
        if (b > 0 && b < 9) {
            if (myArea[a][b+1] == 'o' || myArea[a+1][b+1] == 'o') return 0;
            if (myArea[a][b-1] == 'o' || myArea[a+1][b-1] == 'o') return 0;
        }
        if (b == 0) {
            if (myArea[a][b+1] == 'o' || myArea[a+1][b+1] == 'o') return 0;
        }
        if (b == 9) {
            if (myArea[a][b-1] == 'o' || myArea[a+1][b-1] == 'o') return 0;
        }
    }
    if (a == 9) {
        if (myArea[a-1][b] == 'o') return 0;
        if (b > 0 && b < 9) {
            if (myArea[a-1][b+1] == 'o' || myArea[a][b+1] == 'o') return 0;
            if (myArea[a-1][b-1] == 'o' || myArea[a][b-1] == 'o') return 0;
        }
        if (b == 0) {
            if (myArea[a-1][b+1] == 'o' || myArea[a][b+1] == 'o') return 0;
        }
        if (b == 9) {
            if (myArea[a-1][b-1] == 'o' || myArea[a][b-1] == 'o') return 0;
        }
    }
    return 1;
}

void RandomSet() {
    int k;
    int ships = 0;
    for (k = 4; k > 0; k--) {
        int amount = 5 - k;
        int a, b, i, temp, r;
        while (amount) {
            srand(SEED);
            a = rand() % 10;
            b = rand() % 10;
            r = rand();
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
                    ships++;
                }
            } else if (a + k - 1 <= 9) {
                for (i = 0; i < k; i++) {
                    if (CheckNear(a + i, b)) temp++;
                    else break;
                }
                if (temp == k) {
                    for (i = 0; i < k; i++)
                        myArea[a + i][b] = 'o';
                    amount--;
                    ships++;
                }
            }
        }
    }
}


int main(int argc, char* argv[]) {
//........CREATING CONNECTION BETWEEN PROCESSES............
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
    char* adr = (char*)malloc(32 * sizeof(char));
    strcpy(adr, "tcp://localhost:");
    strcat(adr, argv[2]);

    int sz = strlen(argv[1]);
    playerID = (char*)malloc(sz);
    strcpy(playerID, argv[1]);

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
//.........................................................
//......INITIALAIZE BY RANDOM OR BY COORDINATS (TO DO).....
    myArea = (char**)malloc(10 * sizeof(char*));
    int i, j, k;
    for (i = 0; i < 10; i++)
        myArea[i] = (char*)malloc(10 * sizeof(char));
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++)
            myArea[i][j] = '~';
    }

    enemyArea = (char**)malloc(10 * sizeof(char*));
    for (i = 0; i < 10; i++)
        enemyArea[i] = (char*)malloc(10 * sizeof(char));
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++)
            enemyArea[i][j] = '~';
    }

    RandomSet();

    printf("\tYOUR SHIPS\n  ");
    for (i = 0; i < 10; i++) printf("%d ", i);
    printf("\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", i);
        for (j = 0; j < 10; j++) {
            printf("%c ", myArea[i][j]);
        }
        printf("\n");
    }

    printf("\tENEMY'S SHIPS\n  ");
    for (i = 0; i < 10; i++) printf("%d ", i);
    printf("\n");
    for (i = 0; i < 10; i++) {
        printf("%d ", i);
        for (j = 0; j < 10; j++) {
            printf("%c ", enemyArea[i][j]);
        }
        printf("\n");
    }

//...............FIRST AREA................................
    char tmp[MESSAGE_SIZE];
    char msg[MESSAGE_SIZE];
    char OK[3] = "OK";
    strcpy(msg, "");
    strcpy(tmp, "");
    strcat(tmp, playerID);
    sprintf(msg, " area ");
    strcat(tmp, msg);

    for (i = 0; i < 10; i++)
        strcat(tmp, myArea[i]);

    if (zmq_send(request, tmp, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not send message.\n");
        return -1;
    }

    memset(tmp, 0, MESSAGE_SIZE);
    if (zmq_recv(request, tmp, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not receive message.\n");
        return -1;
    }
    printf("%s\n", tmp);
    if (!strcmp(tmp, "You have the first turn") || !strcmp(tmp, "You have the second turn")) {
        //sprintf(tmp, "OK");
        if (zmq_send(request, OK, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not send message.\n");
            return -1;
        }
    }

//.........................................................

//......INFINITE LOOP FOR SENDING COMMANDS TO SERVER.......
    while (!feof(stdin)) {
        memset(tmp, 0, MESSAGE_SIZE);
        if (zmq_recv(request, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            return -1;
        }

        char enem[MESSAGE_SIZE];
        strcpy(enem, "");
        char tempAns[MESSAGE_SIZE];
        strcpy(tempAns, "");
        sscanf(tmp, "%s %s", tempAns, enem);
        
        printf("%s\n", tempAns);

// won lost marked miss wait
        if (!strcmp(tempAns, "your_turn") || !strcmp(tempAns, "killed") || !strcmp(tempAns, "injured")) {
            while (1) {
                __fpurge(stdin);
                strcpy(msg, "");
                strcpy(tmp, "");

                printf("\nEnter your command:\n>");
                fgets(msg, MESSAGE_SIZE, stdin);

                char check[MESSAGE_SIZE];

                int tmpL = 0;
                int tmpC = 0;
                printf("msg: %s\n", msg);
                strcat(tmp, msg);
                sscanf(msg, "%s %d %d", check, &tmpL, &tmpC);
                if (strcmp(check, "shoot")) printf("Wrong command!\n");
                if (!strcmp(check, "shoot") && tmpL >= 0 && tmpL <= 9 && tmpC >= 0 && tmpC <= 9) 
                    break;
                else printf("Wrong coordinates!\n");

            }
            printf("send: %s\n", tmp);
            if (zmq_send(request, tmp, MESSAGE_SIZE, 0) == -1) {
                printf("Error! Can not send message.\n");
                return -1;
            }

        memset(tmp, 0, MESSAGE_SIZE);
        if (zmq_recv(request, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            return -1;
        }
        if (!strcmp(tmp, "wait")) {
            if (zmq_send(request, OK, MESSAGE_SIZE, 0) == -1) {
                printf("Error! Can not send message.\n");
                return -1;
            }

        }

        char enem[MESSAGE_SIZE];
        strcpy(enem, "");
        char tempAns[10];
        strcpy(tempAns, "");
        sscanf(tmp, "%s %s", tempAns, enem);
        printf("%s\n", tempAns);
        if (!strcmp(tempAns, "won!")) {
            printf("You won the game!\n");
            return 0;
        } else if (!strcmp(tempAns, "lost!")) {
            printf("You lost the game!\n");
            return 0;
        } else if (!strcmp(tempAns, "marked")) continue;
        else if (!strcmp(tempAns, "miss")) {

        }
        printf("\tENEMY\n  ");
        for (i = 0; i < 10; i++) printf("%d ", i);
        printf("\n");
        for (i = 0; i < 10; i++) {
            printf("%d ", i);
            for (j = 0; j < 10; j++) {
                enemyArea[i][j] = enem[i * 10 + j];
                printf("%c ", enemyArea[i][j]);
            }
            printf("\n");
        }
        }










        while (1) {
            __fpurge(stdin);
            strcpy(msg, "");
            strcpy(tmp, "");

            printf("\nEnter your command:\n>");
            fgets(msg, MESSAGE_SIZE, stdin);

            char check[MESSAGE_SIZE];

            int tmpL = 0;
            int tmpC = 0;
            printf("msg: %s\n", msg);
            strcat(tmp, msg);
            sscanf(msg, "%s %d %d", check, &tmpL, &tmpC);
            if (strcmp(check, "shoot")) printf("Wrong command!\n");
            if (!strcmp(check, "shoot") && tmpL >= 0 && tmpL <= 9 && tmpC >= 0 && tmpC <= 9) 
                break;
            else printf("Wrong coordinates!\n");

        }
        printf("send: %s\n", tmp);
        if (zmq_send(request, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not send message.\n");
            return -1;
        }

        memset(tmp, 0, MESSAGE_SIZE);
        if (zmq_recv(request, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            return -1;
        }
        if (!strcmp(tmp, "wait")) {
            if (zmq_send(request, OK, MESSAGE_SIZE, 0) == -1) {
                printf("Error! Can not send message.\n");
                return -1;
            }

        }

        char enem[MESSAGE_SIZE];
        strcpy(enem, "");
        char tempAns[10];
        strcpy(tempAns, "");
        sscanf(tmp, "%s %s", tempAns, enem);
        printf("%s\n", tempAns);
        if (!strcmp(tempAns, "won!")) {
            printf("You won the game!\n");
            return 0;
        } else if (!strcmp(tempAns, "lost!")) {
            printf("You lost the game!\n");
            return 0;
        } else if (!strcmp(tempAns, "marked")) continue;
        else if (!strcmp(tempAns, "miss")) {

        }
        printf("\tENEMY\n  ");
        for (i = 0; i < 10; i++) printf("%d ", i);
        printf("\n");
        for (i = 0; i < 10; i++) {
            printf("%d ", i);
            for (j = 0; j < 10; j++) {
                enemyArea[i][j] = enem[i * 10 + j];
                printf("%c ", enemyArea[i][j]);
            }
            printf("\n");
        }
    }

    zmq_close(request);
    zmq_ctx_destroy(context);
    return 0;
}
