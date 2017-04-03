#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <set>
#include "zmq.h"

#define MESSAGE_SIZE 256

int mainID;
typedef struct {
    int ID;
    int _4d;
    int _3d;
    int _2d;
    int _1d;
} TPlayer;

char** firstArea;
char** secondArea;

char* adr1;
char* adr2;

TPlayer* player1;
TPlayer* player2;

//............FUNCTIONS FOR PROCESSING GAME................

int MarkNear(const int ln, const int cl, const int orient, const int deck, char** area) {
    if (orient == 0) {
        if (ln == 0) {
            area[ln + 1][cl] = '*';
            if (deck == 1 && cl != 10 - deck) {
                area[ln + 1][cl + 1] = '*';
                area[ln][cl + 1] = '*';
            }
            if (cl != 0) {
                area[ln + 1][cl - 1] = '*';
                if (area[ln][cl - 1] != 'X')
                    area[ln][cl - 1] = '*';
            }
        } else if (ln == 9) {
            area[ln - 1][cl] = '*';
            if (deck == 1 && cl != 10 - deck) {
                area[ln - 1][cl + 1] = '*';
                area[ln][cl + 1] = '*';
            }
            if (cl != 0) {
                area[ln - 1][cl - 1] = '*';
                if (area[ln][cl - 1] != 'X')
                    area[ln][cl - 1] = '*';
            }
        } else {
            area[ln - 1][cl] = '*';
            area[ln + 1][cl] = '*';
            if (deck == 1 && cl != 10 - deck) {
                area[ln - 1][cl + 1] = '*';
                area[ln][cl + 1] = '*';
                area[ln + 1][cl + 1] = '*';
            }
            if (cl != 0) {
                area[ln - 1][cl - 1] = '*';
                area[ln + 1][cl - 1] = '*';
                if (area[ln][cl - 1] != 'X')
                    area[ln][cl - 1] = '*';
            }
        }
        if (deck > 1) {
            MarkNear(ln, cl + 1, 0, deck - 1, area);
        }
    }

    if (orient == 1) {
        if (cl == 0) {
            area[ln][cl + 1] = '*';
            if (ln == 0) {
                if (deck == 1) {
                    area[ln + 1][cl] = '*';
                    area[ln + 1][cl + 1] = '*';
                }
            } else {
                area[ln - 1][cl + 1] = '*';
                if (area[ln - 1][cl] != 'X')
                    area[ln - 1][cl] = '*';
                if (deck == 1 && ln != 10 - deck) {
                    area[ln + 1][cl] = '*';
                    area[ln + 1][cl + 1] = '*';
                }
            }
        } else if (cl == 9) {
            area[ln][cl - 1] = '*';
            if (ln == 0) {
                if (deck == 1) {
                    area[ln + 1][cl] = '*';
                    area[ln + 1][cl - 1] = '*';
                }
            } else {
                area[ln - 1][cl - 1] = '*';
                if (area[ln - 1][cl] != 'X')
                    area[ln - 1][cl] = '*';
                if (deck == 1 && ln != 10 - deck) {
                    area[ln + 1][cl] = '*';
                    area[ln + 1][cl - 1] = '*';
                }
            }
        } else {
            area[ln][cl + 1] = '*';
            area[ln][cl - 1] = '*';
            if (ln == 0) {
                if (deck == 1) {
                    area[ln + 1][cl - 1] = '*';
                    area[ln + 1][cl] = '*';
                    area[ln + 1][cl + 1] = '*';
                }
            } else {
                area[ln - 1][cl + 1] = '*';
                area[ln - 1][cl - 1] = '*';
                if (area[ln - 1][cl] != 'X')
                    area[ln - 1][cl] = '*';
                if (deck == 1 && ln != 10 - deck) {
                    area[ln + 1][cl + 1] = '*';
                    area[ln + 1][cl] = '*';
                    area[ln + 1][cl - 1] = '*';
                }
            }
        }
        if (deck > 1) {
            MarkNear(ln + 1, cl, 1, deck - 1, area);
        }
    }
    return 1;
}

void ReduceShips(const int deck, TPlayer* player) {
    if (deck == 4) {
        player->_4d--;
    } else if (deck == 3) {
        player->_3d--;
    } else if (deck == 2) {
        player->_2d--;
    } else if (deck == 1) {
        player->_1d--;
    }
}

int CheckVictory() {
    if (player1->_4d == 0 && player1->_3d == 0 && player1->_2d == 0 && player1->_1d == 0) return 2;
    if (player2->_4d == 0 && player2->_3d == 0 && player2->_2d == 0 && player2->_1d == 0) return 1;
    else return 0;
}

int CheckIfKilled(const int line, const int column, char** area, TPlayer* player) {
    if (line < 0 || line > 9 || column < 0 || line > 9) printf("ALARM!!\n");
    printf("in CheckIfKilled, line: %d column: %d player: %d\n", line, column, player->ID);
    int hor = 0;
    int vert = 0;
    int inj = 0;
    int cnt = 1;
    while (cnt < 4) {
        if (line + cnt > 9) break;
        if (area[line + cnt][column] == 'X' || area[line + cnt][column] == 'o') {
            vert++;
            if (area[line + cnt][column] == 'X')
                inj++;
            cnt++;
        } else break;
    }
    printf("1 ");
    cnt = 1;
    while (cnt < 4) {
        if (line - cnt < 0) break;
        if (area[line - cnt][column] == 'X' || area[line - cnt][column] == 'o') {
            vert++;
            if (area[line - cnt][column] == 'X')
                inj++;
            cnt++;
        } else break;
    }
    printf("2 ");
    cnt = 1;
    while (cnt < 4) {
        if (column + cnt > 9) break;
        if (area[line][column + cnt] == 'X' || area[line][column + cnt] == 'o') {
            hor++;
            if (area[line][column + cnt] == 'X')
                inj++;
            cnt++;
        } else break;
    }
    printf("3 ");
    cnt = 1;
    while (cnt < 4) {
        if (column - cnt < 0) break;
        if (area[line][column - cnt] == 'X' || area[line][column - cnt] == 'o') {
            hor++;
            if (area[line][column - cnt] == 'X')
                inj++;
            cnt++;
        } else break;
    }
    printf("4 ");
    cnt = 1;
    int killed = 0;
    if (inj == vert + hor) {
        killed = 1;
    }
    int dc = 1 + vert + hor;
    int begL, begC;
    begC = column;
    begL = line;
    cnt = 1;
    printf("5 ");
    if (vert != 0) {
        while ((area[line - cnt][column] == 'X' || area[line - cnt][column] == 'o') && line - cnt >= 0) {
            begL--;
            cnt++;
        }
    } else if (hor != 0) {
        while ((area[line][column - cnt] == 'X' || area[line][column - cnt] == 'o') && column - cnt >= 0) {
            begC--;
            cnt++;
        }
    }
    printf("6 ");
    if (killed) {
        if (hor != 0) MarkNear(begL, begC, 0, dc, area);
        else MarkNear(begL, begC, 1, dc, area);
        printf("7 ");
        ReduceShips(dc, player);
        printf("8 ");
        printf("1: 4d: %d, 3d: %d, 2d: %d, 1d: %d\n", player1->_4d, player1->_3d, player1->_2d, player1->_1d);
        printf("2: 4d: %d, 3d: %d, 2d: %d, 1d: %d\n", player2->_4d, player2->_3d, player2->_2d, player2->_1d);
        return 1;
    }
    return 0;
}
//.........................................................

void PrintSecond() {
    int i, j;
    printf("\tSECOND\n  ");
    for (i = 0; i < 10; i++) printf("%d ", i);
    printf("\n");

    for (i = 0; i < 10; i++) {
        printf("%d ", i);
        for (j = 0; j < 10; j++) {
            printf("%c ", secondArea[i][j]);
        }
        printf("\n");
    }
}

void PrintFirst() {
    int i, j;
    printf("\tFIRST\n  ");
    for (i = 0; i < 10; i++) printf("%d ", i);
    printf("\n");

    for (i = 0; i < 10; i++) {
        printf("%d ", i);
        for (j = 0; j < 10; j++) {
            printf("%c ", firstArea[i][j]);
        }
        printf("\n");
    }
}

void Init() {
    int i;
    adr1 = (char*)malloc(32 * sizeof(char));
    adr2 = (char*)malloc(32 * sizeof(char));
    firstArea = (char**)malloc(10 * sizeof(char*));
    secondArea = (char**)malloc(10 * sizeof(char*));
    for (i = 0; i < 10; i++) {
        firstArea[i] = (char*)malloc(11 * sizeof(char));
        secondArea[i] = (char*)malloc(11 * sizeof(char));
    }
    player1 = (TPlayer*)malloc(sizeof(TPlayer));
    player2 = (TPlayer*)malloc(sizeof(TPlayer));
    player1->ID = 0;
    player2->ID = 0;
    player1->_1d = 4;
    player1->_2d = 3;
    player1->_3d = 2;
    player1->_4d = 1;
    player2->_1d = 4;
    player2->_2d = 3;
    player2->_3d = 2;
    player2->_4d = 1;
}

void Free() {
    int i;
    for (i = 0; i < 10; i++) {
        free(firstArea[i]);
        free(secondArea[i]);
    }
    free(firstArea);
    free(secondArea);
    free(player1);
    free(player2);
    free(adr1);
    free(adr2);
}

int main (int argc, char* argv[]) {
    int i,j;
    if (argc != 3) {
        printf("Error! You should set two port adresses.\n");
        return -1;
    }
//............CREATING SOCKETS REPLY REQUEST...............

    void* context1 = zmq_ctx_new();
    if (context1 == NULL) {
        printf("Can not create context.\n");
        return -1;
    }

    void* context2 = zmq_ctx_new();
    if (context2 == NULL) {
        printf("Can not create context.\n");
        return -1;
    }

    void* respond1 = zmq_socket(context1, ZMQ_REP);
    if (respond1 == NULL) {
        printf("Can not create socket (responder).\n");
        return -1;
    }

    void* respond2 = zmq_socket(context1, ZMQ_REP);
    if (respond2 == NULL) {
        printf("Can not create socket (responder).\n");
        return -1;
    }    


    Init();
    strcpy(adr1, "tcp://*:");
    strcat(adr1, argv[1]);
    strcpy(adr2, "tcp://*:");
    strcat(adr2, argv[2]);

    if (zmq_bind(respond1, adr1) == -1) {
        printf("Can not bind socket1.\n");
        Free();
        return -1;
    }
    printf("adr1: %s\nadr2: %s\n", adr1, adr2);
    if (zmq_bind(respond2, adr2) == -1) {
        printf("Can not bind socket2.\n");
        Free();
        return -1;
    }

//.........................................................
    
    char tmp[MESSAGE_SIZE];
    char cmd[MESSAGE_SIZE];

//...............FIRST AREA................................
    strcpy(cmd, "");
    strcpy(tmp, "");
    if (zmq_recv(respond1, tmp, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not receive message.\n");
        Free();
        return -1;
    }

    sscanf(tmp, "%d %s", &player1->ID, cmd);
    if (!strcmp(cmd, "area")) {
        sscanf(tmp, "%*d %*s %s", tmp);
        printf("\tFIRST PLAYER\n  ");
        for (i = 0; i < 10; i++) printf("%d ", i);
        printf("\n");

        for (i = 0; i < 10; i++) {
            printf("%d ", i);
            for (j = 0; j < 10; j++) {
                firstArea[i][j] = tmp[i * 10 + j];
                printf("%c ", firstArea[i][j]);
            }
            printf("\n");
        }
    }

    char ans[MESSAGE_SIZE];
    sprintf(ans, "You have the first turn");

    if (zmq_send(respond1, ans, strlen(ans), 0) == -1)
        printf("Error! Can not send message1.\n");
//.........................................................

//...............SECOND AREA................................
    strcpy(cmd, "");
    strcpy(tmp, "");
    if (zmq_recv(respond2, tmp, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not receive message.\n");
        Free();
        return -1;
    }

    sscanf(tmp, "%d %s", &player2->ID, cmd);
    if (!strcmp(cmd, "area")) {
        sscanf(tmp, "%*d %*s %s", tmp);
        printf("\tSECOND PLAYER\n  ");

        for (i = 0; i < 10; i++) printf("%d ", i);
        printf("\n");
        for (i = 0; i < 10; i++) {
            printf("%d ", i);
            for (j = 0; j < 10; j++) {
                secondArea[i][j] = tmp[i * 10 + j];
                printf("%c ", secondArea[i][j]);
            }
            printf("\n");
        }
    }
    sprintf(ans, "You have the second turn");

    if (zmq_send(respond2, ans, strlen(ans), 0) == -1)
        printf("Error! Can not send message2.\n");
//.........................................................
    char tmp2[MESSAGE_SIZE];
    char cmd2[MESSAGE_SIZE];
    char yourTurn[10] = "your_turn";
    char wait[5] = "wait";
    char miss[5] = "miss";

//............INFINITE LOOP FOR RECEIVING MESSAGES.........
    while (1) {
        strcpy(cmd, "");
        strcpy(tmp, "");
        if (zmq_recv(respond1, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            Free();
            return -1;
        }
        if (zmq_recv(respond2, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            Free();
            return -1;
        }


        if (zmq_send(respond1, yourTurn, strlen(ans), 0) == -1) {
            printf("Error! Can not send message31.\n");
            Free();
            return -1;
        }


        if (zmq_send(respond2, wait, strlen(ans), 0) == -1) {
            printf("Error! Can not send message31.\n");
            Free();
            return -1;
        }



        strcpy(tmp, "");
        if (zmq_recv(respond1, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            Free();
            return -1;
        }

        if (zmq_recv(respond2, tmp2, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            Free();
            return -1;
        }

        sscanf(tmp, "%s", cmd);
        printf("here1\n");
        printf("cmd: %s\n", cmd);
        while (!strcmp(cmd, "shoot")) {
            if (!strcmp(tmp, "OK")) {

            }
            int l, col;
            sscanf(tmp, "%*s %d %d", &l, &col);
            printf("first loop, l: %d, col: %d\n", l, col);
            if (secondArea[l][col] == '~') {
                secondArea[l][col] = '*';
                sprintf(ans, "miss ");
                char tempChar[11];
                for (i = 0; i < 10; i++) {
                    memset(tempChar, 0, 11);
                    for (j = 0; j < 10; j++) {
                        if (secondArea[i][j] == 'o') {
                            tempChar[j] = '~';
                        } else tempChar[j] = secondArea[i][j];
                    }
                    strcat(ans, tempChar);
                }
                if (zmq_send(respond1, ans, strlen(ans), 0) == -1) {
                    printf("Error! Can not send message3.\n");
                    Free();
                    return -1;
                }

                printf("miss1\n");
                if (zmq_send(respond1, yourTurn, strlen(ans), 0) == -1) {
                    printf("Error! Can not send message31.\n");
                    Free();
                    return -1;
                }
                break; 
            } else if (secondArea[l][col] == 'o') {
                secondArea[l][col] = 'X';
                if (CheckIfKilled(l, col, secondArea, player2)) {
                    sprintf(ans, "killed ");
                    if (CheckVictory() == 1) {
                        sprintf(ans, "won! ");
                        if (zmq_send(respond1, ans, strlen(ans), 0) == -1)
                            printf("Error! Can not send message4.\n");
                        sprintf(ans, "lost! ");
                        if (zmq_send(respond2, ans, strlen(ans), 0) == -1)
                            printf("Error! Can not send message5.\n");
                        Free();
                        return 0;
                    }
                } else sprintf(ans, "injured ");
    
                char tempChar[11];
                for (i = 0; i < 10; i++) {
                    memset(tempChar, 0, 11);
                    for (j = 0; j < 10; j++) {
                        if (secondArea[i][j] == 'o') {
                            tempChar[j] = '~';
                        } else tempChar[j] = secondArea[i][j];
                    }
                    strcat(ans, tempChar);
                }

                if (zmq_send(respond1, ans, strlen(ans), 0) == -1)
                    printf("Error! Can not send message6.\n");
                PrintSecond();

                strcpy(cmd, "");
                strcpy(tmp, "");
                if (zmq_recv(respond1, tmp, MESSAGE_SIZE, 0) == -1) {
                    printf("Error! Can not receive message.\n");
                    Free();
                    return -1;
                }

                sscanf(tmp, "%s", cmd);
                printf("hit1\n");
                printf("cmd1: %s\n", cmd);
            } else {
                sprintf(ans, "marked ");
                if (zmq_send(respond1, ans, strlen(ans), 0) == -1)
                    printf("Error! Can not send message7.\n");
                strcpy(cmd, "");
                strcpy(tmp, "");
                if (zmq_recv(respond1, tmp, MESSAGE_SIZE, 0) == -1) {
                    printf("Error! Can not receive message.\n");
                    Free();
                    return -1;
                }

                sscanf(tmp, "%s", cmd);
            }
        }
        PrintSecond();

        strcpy(cmd, "");
        strcpy(tmp, "");
        if (zmq_recv(respond2, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            Free();
            return -1;
        }
        sscanf(tmp, "%s", cmd);
        while (!strcmp(cmd, "shoot")) {
            int l, col;
            sscanf(tmp, "%*s %d %d", &l, &col);
            if (firstArea[l][col] == '~') {
                firstArea[l][col] = '*';
                sprintf(ans, "miss ");
                char tempChar[11];
                for (i = 0; i < 10; i++) {
                    memset(tempChar, 0, 11);
                    for (j = 0; j < 10; j++) {
                        if (firstArea[i][j] == 'o') {
                            tempChar[j] = '~';
                        } else tempChar[j] = firstArea[i][j];
                    }
                    strcat(ans, tempChar);
                }
                if (zmq_send(respond2, ans, strlen(ans), 0) == -1)
                    printf("Error! Can not send message9.\n");
                break;
            } else if (firstArea[l][col] == 'o') {
                firstArea[l][col] = 'X';
                if (CheckIfKilled(l, col, firstArea, player1)) {
                    sprintf(ans, "killed ");
                    if (CheckVictory() == 2) {
                        sprintf(ans, "won! ");
                        if (zmq_send(respond2, ans, strlen(ans), 0) == -1)
                            printf("Error! Can not send message10.\n");
                        sprintf(ans, "lost! ");
                        if (zmq_send(respond1, ans, strlen(ans), 0) == -1)
                            printf("Error! Can not send message11.\n");
                        Free();
                        return 0;
                    }
                } else sprintf(ans, "injured ");

                char tempChar[11];
                for (i = 0; i < 10; i++) {
                    memset(tempChar, 0, 11);
                    for (j = 0; j < 10; j++) {
                        if (firstArea[i][j] == 'o') {
                            tempChar[j] = '~';
                        } else tempChar[j] = firstArea[i][j];
                    }
                    strcat(ans, tempChar);
                }
                if (zmq_send(respond2, ans, strlen(ans), 0) == -1)
                    printf("Error! Can not send message12.\n");

                PrintFirst();
                strcpy(cmd, "");
                strcpy(tmp, "");
                if (zmq_recv(respond2, tmp, MESSAGE_SIZE, 0) == -1) {
                    printf("Error! Can not receive message.\n");
                    Free();
                    return -1;
                }

                sscanf(tmp, "%s", cmd);


            } else {
                sprintf(ans, "marked ");
                if (zmq_send(respond2, ans, strlen(ans), 0) == -1)
                    printf("Error! Can not send message13.\n");
                strcpy(cmd, "");
                strcpy(tmp, "");
                if (zmq_recv(respond2, tmp, MESSAGE_SIZE, 0) == -1) {
                    printf("Error! Can not receive message.\n");
                    Free();
                    return -1;
                }

                sscanf(tmp, "%s", cmd);

            }
        }
        PrintFirst();

    }
//.........................................................
    zmq_close(respond1);
    zmq_close(respond2);
    zmq_ctx_destroy(context1);
    zmq_ctx_destroy(context2);
    return 0;
}
