#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <ctime>
#include <unistd.h>

int DIFFERENCE = 0;
int TIMES = 0;
char** arr;
int MAX_TR = 128;

pthread_mutex_t mutex_ce = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_inf = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int index;
    int shift;
} trInfo;

void CompareExchange(int l, int r) {
    if (strcmp(arr[l], arr[r]) > 0) {
        pthread_mutex_lock(&mutex_ce);
        int sz = (strlen(arr[l]) + 1) * sizeof(char);
        char* temp = (char*)malloc(sz);
        strcpy(temp, arr[l]);
        char* t1 = (char*)realloc(arr[l], sizeof(char) * (strlen(arr[r]) + 1));
        if (!t1) {
            printf("Can not realloc!\n");
            return;
        }
        arr[l] = t1;
        strcpy(arr[l], arr[r]);
        char* t2 = (char*)realloc(arr[r], sz);
        if (!t2) {
            printf("Can not realloc!\n");
            return;
        }
        arr[r] = t2;
        strcpy(arr[r], temp);
        free(temp);
        pthread_mutex_unlock(&mutex_ce);
    }
}

void* ExecCE(void* data) {
    trInfo* ndata = (trInfo*)data;
    CompareExchange(ndata->index, ndata->shift);
}

void OddEvenMerge(int l, int size, int step) {
    int t = step * 2;
    if (t < size) {
        OddEvenMerge(l, size, t);
        OddEvenMerge(l + step, size, t);
        int k, i, j = 0;
        int q = (size - step) / t;
        //int my = 1;
        int min;
        if (q < MAX_TR) {
            min = q;
        } else {
            min = MAX_TR;
        }
        pthread_t* threads = (pthread_t*)malloc(min * sizeof(pthread_t));
        trInfo* data = (trInfo*)malloc(min * sizeof(trInfo));
        for (i = l + step; i + step < l + size; i += t, j++) {
            data[j % MAX_TR].index = i;
            data[j % MAX_TR].shift = i + step;
            if (j != 0 && j % MAX_TR == 0) {
                for (k = 0; k < min; k++) {
                    pthread_join(threads[k], NULL);
                }
            }
            int iret1 = pthread_create( &threads[j % MAX_TR], NULL, ExecCE, &data[j % MAX_TR]);
            if (iret1) {
                fprintf(stderr,"Error - pthread_create() return code: %d\nNum: %d\n", iret1, j);
                exit(EXIT_FAILURE);
            }

            //printf("i = %d, l = %d, size = %d, step = %d, t = %d\n", i, l, size, step, t);
            //CompareExchange(i, i + step);
        }

        for (i = 0; i < j % MAX_TR; i++) {
            pthread_join(threads[i], NULL);
        }
        free(threads);
        free(data);
    } else CompareExchange(l, l + step);
}

void OddEvenMergeSort(int l, int size) {
    if (size > 1) {
        pthread_t thread1, thread2;
        int p1, p2;
        int mid = size / 2;
        OddEvenMergeSort(l, mid);
        OddEvenMergeSort(l + mid, mid);
        OddEvenMerge(l, size, 1);
    }
}

int PowerOf2(int num) {
    if (num < 1) return 0;
    while ((num % 2) == 0) {
        if ((num / 2) == 1) return 1;
        num /= 2;
    }
    return 0;
}

int main() {
    unsigned long long start = clock();
    char tmp[256];
    int sz = 0;
    arr = (char**)malloc(sizeof(char*));
    while (scanf("%s", tmp) != EOF) {
        ++sz;
        arr = (char**)realloc(arr, sizeof(char*) * sz);
        arr[sz - 1] = (char*)malloc(sizeof(char) * (strlen(tmp) + 1));
        strcpy(arr[sz - 1], tmp);
        strcpy(tmp, "");
    }
    int i, j;
    if (!PowerOf2(sz)) {
        int temp = log10(sz) / log10(2);
        int nsz = pow(2, temp + 1);
        arr = (char**)realloc(arr, sizeof(char*) * nsz);
        for (j = sz; j < nsz; j++) {
            arr[j] = (char*)malloc(sizeof(char) * 4);
            strcpy(arr[j], "");
        }
        DIFFERENCE = nsz - sz;
        OddEvenMergeSort(0, nsz);
        for (i = DIFFERENCE; i < nsz; i++) {
            //printf("aft s: %d: %s\n", i + 1 - DIFFERENCE, arr[i]);
        }
    } else {
        OddEvenMergeSort(0, sz);
        for (i = 0; i < sz; i++) {
            //printf("aft s: %d: %s\n", i + 1 - DIFFERENCE, arr[i]);
        }
    }
    for (j = 0; j < sz; j++) {
        free(arr[j]);
    }
    free(arr);
    unsigned long long end = clock();
    printf("TIME: %llu\n", end - start);
    return 0;
}

// проверить время работы
