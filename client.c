#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include "zmq.h"

void Help() {
    printf("\tAvailable commands:\n>deposit SID SUM >withdraw SUM ");
    printf(">transfer BANK_ADR SUM >balance\n");
}

int main (int argc, char* argv[]) {
    if (argc != 3) {
        printf("Error! You should set client ID and bank adress.\n");
        return -1;
    }
    char* adr = (char*)malloc(32 * sizeof(char));
    strcpy(adr, "tcp://localhost:");
    strcat(adr, argv[2]);
    int sz = strlen(argv[1]);
    char* curID = (char*)malloc(sz);
    strcpy(curID, argv[1]);
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
    char tmp[100];
    Help();
    char msg[100];
    while (!feof(stdin)) {
        __fpurge(stdin);
        printf("\nEnter your command:\n>");
        fgets(tmp, 100, stdin);
        strcpy(msg, curID);
        strcat(msg, " ");
        strcat(msg, tmp);
        if (zmq_send(request, msg, 100, 0) == -1) {
            printf("Error! Can not send message.\n");
            return -1;
        }
        memset(tmp, 0, 100);
        if (zmq_recv(request, tmp, 100, 0) == -1) {
            printf("Error! Can not receive message.\n");
            return -1;
        }
        printf("%s\n", tmp);
    }
    zmq_close(request);
    zmq_ctx_destroy(context);
    return 0;
}
