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

typedef struct {
    int deck;
    int killed;
    int orientation;
    int lineCoord;
    int columnCoord;
} TShip;

TShip* firstShips;
TShip* secondShips;

TPlayer* player1;
TPlayer* player2;

//............FUNCTIONS FOR PROCESSING GAME................

int MarkNear(int ln, int cl, int orient, int deck) {
    if (orient == 0) {
        if (ln == 0) {
            secondArea[ln + 1][cl] = '*';
            if (deck == 1 && cl != 10 - deck) {
                secondArea[ln + 1][cl + 1] = '*';
                secondArea[ln][cl + 1] = '*';
            }
            if (cl != 0) {
                secondArea[ln + 1][cl - 1] = '*';
                if (secondArea[ln][cl - 1] != 'X')
                    secondArea[ln][cl - 1] = '*';
            }
        } else if (ln == 9) {
            secondArea[ln - 1][cl] = '*';
            if (deck == 1 && cl != 10 - deck) {
                secondArea[ln - 1][cl + 1] = '*';
                secondArea[ln][cl + 1] = '*';
            }
            if (cl != 0) {
                secondArea[ln - 1][cl - 1] = '*';
                if (secondArea[ln][cl - 1] != 'X')
                    secondArea[ln][cl - 1] = '*';
            }
        } else {
            secondArea[ln - 1][cl] = '*';
            secondArea[ln + 1][cl] = '*';
            if (deck == 1 && cl != 10 - deck) {
                secondArea[ln - 1][cl + 1] = '*';
                secondArea[ln][cl + 1] = '*';
                secondArea[ln + 1][cl + 1] = '*';
            }
            if (cl != 0) {
                secondArea[ln - 1][cl - 1] = '*';
                secondArea[ln + 1][cl - 1] = '*';
                if (secondArea[ln][cl - 1] != 'X')
                    secondArea[ln][cl - 1] = '*';
            }
        }
        if (deck > 1) {
            MarkNear(ln, cl + 1, 0, deck - 1);
        }
    }

    if (orient == 1) {
        if (cl == 0) {
            secondArea[ln][cl + 1] = '*';
            if (ln == 0) {
                if (deck == 1) {
                    secondArea[ln + 1][cl] = '*';
                    secondArea[ln + 1][cl + 1] = '*';
                }
            } else {
                secondArea[ln - 1][cl + 1] = '*';
                if (secondArea[ln - 1][cl] != 'X')
                    secondArea[ln - 1][cl] = '*';
                if (deck == 1 && ln != 10 - deck) {
                    secondArea[ln + 1][cl] = '*';
                    secondArea[ln + 1][cl + 1] = '*';
                }
            }
        } else if (cl == 9) {
            secondArea[ln][cl - 1] = '*';
            if (ln == 0) {
                if (deck == 1) {
                    secondArea[ln + 1][cl] = '*';
                    secondArea[ln + 1][cl - 1] = '*';
                }
            } else {
                secondArea[ln - 1][cl - 1] = '*';
                if (secondArea[ln - 1][cl] != 'X')
                    secondArea[ln - 1][cl] = '*';
                if (deck == 1 && ln != 10 - deck) {
                    secondArea[ln + 1][cl] = '*';
                    secondArea[ln + 1][cl - 1] = '*';
                }
            }
        } else {
            secondArea[ln][cl + 1] = '*';
            secondArea[ln][cl - 1] = '*';
            
            if (ln == 0) {
                if (deck == 1) {
                    secondArea[ln + 1][cl - 1] = '*';
                    secondArea[ln + 1][cl] = '*';
                    secondArea[ln + 1][cl + 1] = '*';
                }
            } else {
                secondArea[ln - 1][cl + 1] = '*';
                secondArea[ln - 1][cl - 1] = '*';
                if (secondArea[ln - 1][cl] != 'X')
                    secondArea[ln - 1][cl] = '*';
                if (deck == 1 && ln != 10 - deck) {
                    secondArea[ln + 1][cl + 1] = '*';
                    secondArea[ln + 1][cl] = '*';
                    secondArea[ln + 1][cl - 1] = '*';
                }
            }
        }
        if (deck > 1) {
            MarkNear(ln + 1, cl, 1, deck - 1);
        }
    }




    return 1;
}

void ReduceShips(int deck) {
    if (deck == 4) {
        player2->_4d--;
    } else if (deck == 3) {
        player2->_3d--;
    } else if (deck == 2) {
        player2->_2d--;
    } else if (deck == 1) {
        player2->_1d--;
    }
}

int CheckIfKilled(int line, int column) {
    int hor = 0;
    int vert = 0;
    int inj = 0;
    int cnt = 1;
    //printf("in check kill\n");
    while (cnt < 4) {
        //printf("in first loop\n");
        if (line + cnt > 9) break;
        if (secondArea[line + cnt][column] == 'X' || secondArea[line + cnt][column] == 'o') {
            vert++;
            if (secondArea[line + cnt][column] == 'X')
                inj++;
            cnt++;
        } else break;
    }
    //printf("vert: %d  hor: %d\n", vert, hor);
    cnt = 1;
    while (cnt < 4) {
        //printf("in second loop\n");
        if (line - cnt < 0) break;
        if (secondArea[line - cnt][column] == 'X' || secondArea[line - cnt][column] == 'o') {
            vert++;
            if (secondArea[line - cnt][column] == 'X')
                inj++;
            cnt++;
        } else break;
    }
    //printf("vert: %d  hor: %d\n", vert, hor);
    cnt = 1;
    while (cnt < 4) {
        //printf("in 3rd loop\n");
        if (column + cnt > 9) break;
        if (secondArea[line][column + cnt] == 'X' || secondArea[line][column + cnt] == 'o') {
            hor++;
            if (secondArea[line][column + cnt] == 'X')
                inj++;
            cnt++;
        } else break;
    }
    //printf("vert: %d  hor: %d\n", vert, hor);
    cnt = 1;
    while (cnt < 4) {
        //printf("in 4th loop\n");
        if (column - cnt < 0) break;
        if (secondArea[line][column - cnt] == 'X' || secondArea[line][column - cnt] == 'o') {
            hor++;
            if (secondArea[line][column - cnt] == 'X')
                inj++;
            cnt++;
        } else break;
    }
    //printf("inj: %d, vert: %d  hor: %d\n", inj, vert, hor);
    cnt = 1;
    int killed = 0;
    if (inj == vert + hor) {
        killed = 1;
        //printf("killed!\n");
    }
    int dc = 1 + vert + hor;
    int begL, begC;
    begC = column;
    begL = line;
    cnt = 1;
    if (vert != 0) {
        //printf("vert not 0: %d\n", vert);

        while (secondArea[line - cnt][column] == 'X' || secondArea[line - cnt][column] == 'o') {
            //printf("in vert loop\n");
            begL--;
            cnt++;
        }
    } else if (hor != 0) {
        //printf("hor not 0: %d\n", hor);
        while (secondArea[line][column - cnt] == 'X' || secondArea[line][column - cnt] == 'o') {
            //printf("in hor loop\n");
            begC--;
            cnt++;
        }
    }
    //printf("deck:%d, start coordinats: %d %d\n", dc, begL, begC);
    if (killed) {
        if (hor != 0) MarkNear(begL, begC, 0, dc);
        else MarkNear(begL, begC, 1, dc);
        ReduceShips(dc);
        return 1;
    }
    return 0;
}



int main (int argc, char* argv[]) {
    int i,j;
    if (argc != 2) {
        printf("Error! You should set the bank adress.\n");
        return -1;
    }
//............CREATING SOCKETS REPLY REQUEST...............
    char* adr = (char*)malloc(32 * sizeof(char));
    strcpy(adr, "tcp://*:");
    strcat(adr, argv[1]);

    void* context = zmq_ctx_new();
    if (context == NULL) {
        printf("Can not create context.\n");
        return -1;
    }
    void* respond = zmq_socket(context, ZMQ_REP);
    if (respond == NULL) {
        printf("Can not create socket (responder).\n");
        return -1;
    }

    if (zmq_bind(respond, adr) == -1) {
        printf("Can not bind socket.\n");
        return -1;
    }
//.........................................................
    char tmp[MESSAGE_SIZE];
    char cmd[MESSAGE_SIZE];

    firstArea = (char**)malloc(10 * sizeof(char*));
    for (i = 0; i < 10; i++)
        firstArea[i] = (char*)malloc(10 * sizeof(char));

    player1 = (TPlayer*)malloc(sizeof(TPlayer));
    player2 = (TPlayer*)malloc(sizeof(TPlayer));
    player1->_1d = 4;
    player1->_2d = 3;
    player1->_3d = 2;
    player1->_4d = 1;
    player2->_1d = 4;
    player2->_2d = 3;
    player2->_3d = 2;
    player2->_4d = 1;


//...............FIRST AREA................................
    strcpy(cmd, "");
    strcpy(tmp, "");
    if (zmq_recv(respond, tmp, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not receive message.\n");
        return -1;
    }

    sscanf(tmp, "%d %s", &player1->ID, cmd);
    //printf("Get: %d %s\n", player1->ID, cmd);
    if (!strcmp(cmd, "area")) {
        sscanf(tmp, "%*d %*s %s", tmp);
        //printf("server received: %s\n", tmp);
        printf("\tFIRST\n  ");
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
    sprintf(ans, "First Area received");

    if (zmq_send(respond, ans, strlen(ans), 0) == -1)
        printf("Error! Can not send message.\n");
//.........................................................

//...............FIRST SHIPS...............................
    /*
    firstShips = (TShip*)malloc(10 * sizeof(TShip));
    for (i = 0; i < 10; i++){
        strcpy(cmd, "");
        strcpy(tmp, "");
        if (zmq_recv(respond, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            return -1;
        }
        sscanf(tmp, "%s", cmd);
        if (!strcmp(cmd, "Ships")) {
            sscanf(tmp, "%*s %d %d %d %d", &firstShips[i].deck, &firstShips[i].orientation, &firstShips[i].lineCoord, &firstShips[i].columnCoord);
            firstShips[i].killed = 0;
        }

        sprintf(ans, "First Ship received");
        if (zmq_send(respond, ans, strlen(ans), 0) == -1)
            printf("Error! Can not send message.\n");

    }
    for (i = 0; i < 10; i++)
        printf("%d ship: deck = %d, orientation = %d, status = %d, coords: %d %d\n", i, firstShips[i].deck, firstShips[i].orientation, firstShips[i].killed, firstShips[i].lineCoord, firstShips[i].columnCoord);
    */
//.........................................................    

    secondArea = (char**)malloc(10 * sizeof(char*));
    for (i = 0; i < 10; i++) {
        secondArea[i] = (char*)malloc(11 * sizeof(char));
        //strcpy(secondArea[i], "");
        memset(secondArea[i], 0, 11);
    }

//...............SECOND AREA................................
    strcpy(cmd, "");
    strcpy(tmp, "");
    if (zmq_recv(respond, tmp, MESSAGE_SIZE, 0) == -1) {
        printf("Error! Can not receive message.\n");
        return -1;
    }

    sscanf(tmp, "%d %s", &player2->ID, cmd);
    if (!strcmp(cmd, "area")) {
        sscanf(tmp, "%*d %*s %s", tmp);
        //printf("server received: %s\n", tmp);
        printf("\tSECOND\n  ");

        for (i = 0; i < 10; i++) printf("%d ", i);
        printf("\n");
        //printf("parse tmp: %s\n", tmp);
        for (i = 0; i < 10; i++) {
            printf("%d ", i);
            //strcpy(secondArea[i], "");
            //char tmpStr[11];
            //memset(tmpStr, 0, 11);
            for (j = 0; j < 10; j++) {
                //printf("tm: %c ",tmp[i * 10 + j]);
                secondArea[i][j] = tmp[i * 10 + j];
                printf("%c ", secondArea[i][j]);
                //tmpStr[j] = tmp[i * 10 + j];
            }
            //printf("tmpStr: %s\n", tmpStr);

            //secondArea[i] = (char*)realloc(secondArea[i], 10 * sizeof(char));
            //strcpy(secondArea[i], tmpStr);
            printf("\n");
            //printf("this line: %s\n", secondArea[i]);
            //printf("len: %d\n", strlen(secondArea[i]));
        }
    }


    sprintf(ans, "Second Area received");

    if (zmq_send(respond, ans, strlen(ans), 0) == -1)
        printf("Error! Can not send message.\n");
//.........................................................


//...............SECOND SHIPS...............................
    /*
    secondShips = (TShip*)malloc(10 * sizeof(TShip));
    for (i = 0; i < 10; i++){
        strcpy(cmd, "");
        strcpy(tmp, "");
        if (zmq_recv(respond, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            return -1;
        }
    
        sscanf(tmp, "%s", cmd);
        if (!strcmp(cmd, "Ships")) {
            sscanf(tmp, "%*s %d %d %d %d", &secondShips[i].deck, &secondShips[i].orientation, &secondShips[i].lineCoord, &secondShips[i].columnCoord);
            secondShips[i].killed = 0;
        }
        sprintf(ans, "Second Ship received");
        if (zmq_send(respond, ans, strlen(ans), 0) == -1)
            printf("Error! Can not send message.\n");
    }

    for (i = 0; i < 10; i++)
        //printf("%d ship: deck = %d, orientation = %d, status = %d, coords: %d %d\n", i, secondShips[i].deck, secondShips[i].orientation, secondShips[i].killed, secondShips[i].lineCoord, secondShips[i].columnCoord);
*/
// after that initialization we should send message to first player about his turn, but not earlier than
// second player initialization

//............INFINITE LOOP FOR RECEIVING MESSAGES.........
    while (1) {
        int temp1ID, temp2ID;
        strcpy(cmd, "");
        strcpy(tmp, "");
        if (zmq_recv(respond, tmp, MESSAGE_SIZE, 0) == -1) {
            printf("Error! Can not receive message.\n");
            return -1;
        }

        sscanf(tmp, "%d %s", &temp1ID, cmd);
        if (temp1ID == player1->ID) printf("Turn of 1st player\n");

        if (!strcmp(cmd, "shoot")) {
            //printf("here\t\n");
            int l, col;
            sscanf(tmp, "%*d %*s %d %d", &l, &col);
            //printf("line %d, cl %d\n", l, col);
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
            } else if (secondArea[l][col] == 'o') {
                secondArea[l][col] = 'X';
                if (CheckIfKilled(l, col)) {
                    sprintf(ans, "killed ");
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
                //printf("4d = %d, 3d = %d, 2d = %d, 1d: %d\n", player2->_4d, player2->_3d, player2->_2d, player2->_1d);

            } else {
                sprintf(ans, "marked");
            }
            if (zmq_send(respond, ans, strlen(ans), 0) == -1)
                printf("Error! Can not send message.\n");
        } else {
            sprintf(ans, "wrong command");
            if (zmq_send(respond, ans, strlen(ans), 0) == -1)
                printf("Error! Can not send message.\n");
        }






        sscanf(tmp, "%d %s", &temp1ID, cmd);
        if (temp1ID == player1->ID) printf("Turn of 1st player\n");

        if (!strcmp(cmd, "shoot")) {
            //printf("here\t\n");
            int l, col;
            sscanf(tmp, "%*d %*s %d %d", &l, &col);
            //printf("line %d, cl %d\n", l, col);
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
            } else if (secondArea[l][col] == 'o') {
                secondArea[l][col] = 'X';
                if (CheckIfKilled(l, col)) {
                    sprintf(ans, "killed ");
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
                //printf("4d = %d, 3d = %d, 2d = %d, 1d: %d\n", player2->_4d, player2->_3d, player2->_2d, player2->_1d);

            } else {
                sprintf(ans, "marked");
            }
            if (zmq_send(respond, ans, strlen(ans), 0) == -1)
                printf("Error! Can not send message.\n");
        } else {
            sprintf(ans, "wrong command");
            if (zmq_send(respond, ans, strlen(ans), 0) == -1)
                printf("Error! Can not send message.\n");
        }








        
    
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
//.........................................................
    zmq_close(respond);

    zmq_ctx_destroy(context);
    return 0;
}

//~~~~~~~~~~~*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~