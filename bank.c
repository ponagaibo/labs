#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "zmq.h"
#include "vect.h"

int mainID;
void Deposit(void* socket, TVector vect, int clientID, ull value) {
    TNode cur = FindNode(vect, clientID);
    if (cur) cur->sum += value;
    else PushVector(vect, clientID, value);
    printf("Deposit: operation is done.\n");
    char msg[100];
    sprintf(msg, "Deposit: done. +%llu, id: %d", value, clientID);
    if (zmq_send(socket, msg, strlen(msg), 0) == -1)
        printf("Error! Can not send message (deposit).\n");
}

int Withdraw(void* socket, TVector vect, ull value) {
    TNode cur = FindNode(vect, mainID);
    if (cur) {
        if (cur->sum < value) {
            printf("Insufficient funds.\n");
            if (zmq_send(socket, "Insufficient funds", 18, 0) == -1)
                printf("Error! Can not send message (deposit).\n");
            return 0;
        } else {
            cur->sum -= value;
            char msg[100];
            sprintf(msg, "Withdraw: done. -%llu, id: %d", value, mainID);
            if (zmq_send(socket, msg, strlen(msg), 0) == -1) {
                printf("Error! Can not send message (deposit).\n");
                return 0;
            }
            printf("Withdraw: operation is done.\n");
            return 1;
        }
    } else {
        printf("Error! Can not find an account of the client (withdraw).\n");
        if (zmq_send(socket, "Can not find the client's account (withdraw)", 44, 0) == -1)
            printf("Error! Can not send message (withdraw).\n");
        return 0;
    }
}

void Transfer(void* socket1, void* socket2, TVector vect, int adress, ull value) {
    char adr[32];
    char msg[100];
    sprintf(adr, "tcp://localhost:%d", adress);
    sprintf(msg, "%d deposit %d %llu", mainID, mainID, value);
    if (Withdraw(socket1, vect, value)) {
        zmq_connect (socket2, adr);
        zmq_send(socket2, msg, strlen(msg), 0);
        zmq_disconnect (socket2, adr);
        sprintf(msg, "Transfer: done. -%llu, id: %d", value, mainID);
        printf("Transfer: operation is done.\n");
        if (zmq_send(socket1, msg, strlen(msg), 0) == -1)
            printf("Error! Can not send message (transfer).\n");
    } else {
        printf("Error! Not enough money to transfer.\n");
        if (zmq_send(socket1, "Not enough money to transfer", 28, 0) == -1)
            printf("Error! Can not send message (transfer).\n");
    }
}

void Balance(void* socket, TVector vect) {
    TNode cur = FindNode(vect, mainID);
    if (cur) {
        char msg[30];
        sprintf(msg, "Balance: %llu", cur->sum);
        printf("Balance: operation is done. ID: %d, balance: %llu\n", mainID, cur->sum);
        if (zmq_send(socket, msg, strlen(msg), 0) == -1)
            printf("Error! Can not send message (balance).\n");
    }
    else {
        printf("Error! Can not find an account of the client (balance).\n");
        if (zmq_send(socket, "Can not find the client's account (balance)", 43, 0) == -1)
            printf("Error! Can not send message (balance).\n");
    }
}

int main (int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error! You should set the bank adress.\n");
        return -1;
    }
    int bankAdress = atoi(argv[1]);
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
    void* interbank = zmq_socket(context, ZMQ_REQ);
    if (interbank == NULL) {
        printf("Can not create socket (interbank).\n");
        return -1;
    }
    if (zmq_bind(respond, adr) == -1) {
        printf("Can not bind socket.\n");
        return -1;
    }
    TVector vect = CreateVector();
    char tmp[100];
    char cmd[100];
    int clientID;
    int adress;
    ull value;
    while (1) {
        strcpy(cmd, "");
        strcpy(tmp, "");
        if (zmq_recv(respond, tmp, 100, 0) == -1) {
            printf("Error! Can not receive message.\n");
            return -1;
        }
        sscanf(tmp, "%d %s", &mainID, cmd);
        if (!strcmp(cmd, "deposit")) {
            sscanf(tmp, "%*d %*s %d %llu", &clientID, &value);
            Deposit(respond, vect, clientID, value);
        } else if (!strcmp(cmd, "balance")) {
            Balance(respond, vect);
        } else if (!strcmp(cmd, "withdraw")) {
            sscanf(tmp, "%*d %*s %llu", &value);
            Withdraw(respond, vect, value);
        } else if (!strcmp(cmd, "transfer")) {
            sscanf(tmp, "%*d %*s %d %llu", &adress, &value);
            Transfer(respond, interbank, vect, adress, value);
        } else {
            printf("Unknown command!\n");
            if (zmq_send(respond, "Unknown command", 15, 0) == -1) {
                printf("Error! Can not send message (balance).\n");
            }
        }
        clientID = 0;
        value = 0;
        adress = 0;
        sleep(1);
    }
    DeleteVector(&vect);
    zmq_close(respond);
    zmq_close(interbank);
    zmq_ctx_destroy(context);
    return 0;
}