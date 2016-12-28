#include "stdio.h"
#include "stdlib.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void SumOfSequence(int member, int pipefd[2]) {
    int res = 0;
    if (member < 1) {
        printf("Number less than 0!\n");
        exit(-1);
    }
    if (member == 1 || member == 2) {
        write(pipefd[1], &member, sizeof(int));
        exit(0);
    }

    pid_t childPID = fork();
    if (childPID == -1) {
        perror("Fork error");
        exit(EXIT_FAILURE);
    } else if (childPID == 0) {
        SumOfSequence(member - 1, pipefd);
    } else {
        wait(NULL);
        int cur = 0;
        if (read(pipefd[0], &cur, sizeof(int)) > 0) {
            res = cur + member;
            write(pipefd[1], &res, sizeof(int));
        }
    }
}


int main() {
    int maxNum;
    int res = 0;
    printf("Enter number greater than 0:\n> ");
    scanf("%d", &maxNum);
    int pipefd[2];

    if(pipe(pipefd) == -1) {
        perror("Pipe error");
        exit(EXIT_FAILURE);
    }

    pid_t childPID = fork();

    if (childPID == -1) {
        perror("Fork error");
        exit(EXIT_FAILURE);
    } else if (childPID == 0) {
        SumOfSequence(maxNum, pipefd);
    } else {
        wait(NULL);
        close(pipefd[1]);
        int cur;
        while(read(pipefd[0], &cur, sizeof(int)) > 0) {
            res += cur;
        }
        close(pipefd[0]);
        if (maxNum > 1) res += 1;
        if (maxNum > 0) {
            printf("*** FINAL RES ***\n");
            printf("%d\n", res);
            float orig = ((float)((1 + maxNum) * maxNum)) / 2;
            printf("*** RIGHT ANSWER ***\n");
            printf("%d\n", (int)orig);
        }
    }
    return 0;
}