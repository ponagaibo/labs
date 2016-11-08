#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <ctime>
#include <algorithm>

struct pairElem {
    int day;
    int dayNull;
    int month;
    int monthNull;
    int year;
    int yearNull;
    char* data;
    unsigned int dataNum;
};

class TVector {
public:
    int vectCap;
    struct pairElem* pairKV;
    int vectSize;
    TVector();
    TVector(std::istream &is);
    TVector(int cap);
    void Print();
    void Resize();
    TVector* RadixSort();
    virtual ~TVector();
};

TVector::TVector() {
    vectSize = 0;
    vectCap = 1000;
    pairKV = new pairElem[vectCap];
}

TVector::TVector(int cap) {
    vectSize = 0;
    vectCap = cap;
    pairKV = new pairElem[vectCap];
}

TVector::TVector(std::istream &is) {
    vectSize = 0;
    vectCap = 1000;
    pairKV = new pairElem[vectCap];
    char f[5];
    while (is.peek() == '\n') {
        is.get();
    }
    while(is.getline(f, 5, '.')) {
        pairKV[vectSize].dayNull = 0;
        pairKV[vectSize].monthNull = 0;
        pairKV[vectSize].yearNull = 0;
        for (unsigned int i = 0; i < strlen(f); i++) {
            if (f[i] == '0') {
                pairKV[vectSize].dayNull++;
            } else {
                break;
            }
        }
        pairKV[vectSize].day = atoi(f);

        char num[9];
        int s = 1;
        int k = 1;
        for(int i = 0; i < 2; i++) {
            num[s] = (pairKV[vectSize].day / k) % 10 + '0';
            k *= 10;
            s--;
        }

        is.getline(f, 5, '.');
        for (unsigned int i = 0; i < strlen(f); i++) {
            if (f[i] == '0') {
                pairKV[vectSize].monthNull++;
            } else {
                break;
            }
        }
        pairKV[vectSize].month = atoi(f);

        s = 3;
        k = 1;
        for (int i = 0; i < 2; i++) {
            num[s] = (pairKV[vectSize].month / k) % 10 + '0';
            k *= 10;
            s--;
        }

        is.getline(f, 5, '\t');
        for (unsigned int i = 0; i < strlen(f); i++) {
            if (f[i] == '0') {
                pairKV[vectSize].yearNull++;
            } else {
                break;
            }
        }
        pairKV[vectSize].year = atoi(f);

        s = 7;
        k = 1;
        for (int i = 0; i < 4; i++) {
            num[s] = (pairKV[vectSize].year / k) % 10 + '0';
            k *= 10;
            s--;
        }
        pairKV[vectSize].dataNum = atoi(num);

        char temp[2051];
        is.getline(temp, 2051, '\n');
        pairKV[vectSize].data = new char[strlen(temp) + 1];
        strcpy(pairKV[vectSize].data, temp);
        vectSize++;
        if (vectSize == vectCap) {
            this->Resize();
        }
        while (is.peek() == '\n') {
            is.get();
        }
    }
}

void TVector::Resize() {
    vectCap = (int)(vectCap * 2);
    pairKV = (struct pairElem*)realloc(pairKV, sizeof(struct pairElem) * vectCap);
}

void TVector::Print() {
    for (int i = 0; i < vectSize; i++) {
        for (int j = 0; j < pairKV[i].dayNull; j++) {
            std::cout << "0";
        }
        std::cout << pairKV[i].day << ".";
        for (int j = 0; j < pairKV[i].monthNull; j++) {
            std::cout << "0";
        }
        std::cout << pairKV[i].month << ".";
        for (int j = 0; j < pairKV[i].yearNull; j++) {
            std::cout << "0";
        }
        std::cout << pairKV[i].year << "\t" << pairKV[i].data << "\n";
    }
}

TVector* TVector::RadixSort() {

    for (int j = 0; j < 2; j++) {
        int k = 1;
        for (int q = 0; q < j; q++) {
            k = k * 10;
        }
        int arr_C[10];
        TVector* arr_B = new TVector(vectCap);
        for (int i = 0; i < 10; i++) {
            arr_C[i] = 0;
        }
        for (int i = 0; i < vectSize; i++) {
            arr_C[((int)(pairKV[i].day / k)) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            arr_C[i] = arr_C[i] + arr_C[i-1];
        }
        for (int i = vectSize - 1; i >= 0; i--) {
            int index = arr_C[((int)(pairKV[i].day / k)) % 10] - 1;
            arr_B->pairKV[index] = pairKV[i];
            arr_C[((int)(pairKV[i].day / k)) % 10] = index;
            arr_B->vectSize++;
        }
        for (int i = 0; i < vectSize; i++) {
          pairKV[i].day = arr_B->pairKV[i].day;
          pairKV[i].dayNull = arr_B->pairKV[i].dayNull;
          pairKV[i].month = arr_B->pairKV[i].month;
          pairKV[i].monthNull = arr_B->pairKV[i].monthNull;
          pairKV[i].year = arr_B->pairKV[i].year;
          pairKV[i].yearNull = arr_B->pairKV[i].yearNull;
          pairKV[i].data = new char[strlen(arr_B->pairKV[i].data) + 1];
          pairKV[i].dataNum = arr_B->pairKV[i].dataNum;
          strcpy(pairKV[i].data, arr_B->pairKV[i].data);
        }
        delete(arr_B);
    }
    for (int j = 0; j < 2; j++) {
        int k = 1;
        for (int q = 0; q < j; q++) {
            k = k * 10;
        }
        int arr_C[10];
        TVector* arr_B = new TVector(vectCap);
        for (int i = 0; i < 10; i++) {
            arr_C[i] = 0;
        }
        for (int i = 0; i < vectSize; i++) {
            arr_C[((int)(pairKV[i].month / k)) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
                arr_C[i] = arr_C[i] + arr_C[i-1];
        }
        for (int i = vectSize - 1; i >= 0; i--) {
            int index = arr_C[((int)(pairKV[i].month / k)) % 10] - 1;
            arr_B->pairKV[index] = pairKV[i];
            arr_C[((int)(pairKV[i].month / k)) % 10] = index;
            arr_B->vectSize++;
        }
        for (int i = 0; i < vectSize; i++) {
          pairKV[i].day = arr_B->pairKV[i].day;
          pairKV[i].dayNull = arr_B->pairKV[i].dayNull;
          pairKV[i].month = arr_B->pairKV[i].month;
          pairKV[i].monthNull = arr_B->pairKV[i].monthNull;
          pairKV[i].year = arr_B->pairKV[i].year;
          pairKV[i].yearNull = arr_B->pairKV[i].yearNull;
          pairKV[i].data = new char[strlen(arr_B->pairKV[i].data) + 1];
          pairKV[i].dataNum = arr_B->pairKV[i].dataNum;
          strcpy(pairKV[i].data, arr_B->pairKV[i].data);
        }
        delete(arr_B);
    }
    for (int j = 0; j < 4; j++) {
        int k = 1;
        for (int q = 0; q < j; q++) {
            k = k * 10;
        }
        int arr_C[10];
        TVector* arr_B = new TVector(vectCap);
        for (int i = 0; i < 10; i++) {
            arr_C[i] = 0;
        }
        for (int i = 0; i < vectSize; i++) {
            arr_C[((int)(pairKV[i].year / k)) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            arr_C[i] = arr_C[i] + arr_C[i-1];
        }
        for (int i = vectSize - 1; i >= 0; i--) {
            int index = arr_C[((int)(pairKV[i].year / k)) % 10] - 1;
            arr_B->pairKV[index] = pairKV[i];
            arr_C[((int)(pairKV[i].year / k)) % 10] = index;
            arr_B->vectSize++;
        }
        for (int i = 0; i < vectSize; i++) {
          pairKV[i].day = arr_B->pairKV[i].day;
          pairKV[i].dayNull = arr_B->pairKV[i].dayNull;
          pairKV[i].month = arr_B->pairKV[i].month;
          pairKV[i].monthNull = arr_B->pairKV[i].monthNull;
          pairKV[i].year = arr_B->pairKV[i].year;
          pairKV[i].yearNull = arr_B->pairKV[i].yearNull;
          pairKV[i].data = new char[strlen(arr_B->pairKV[i].data) + 1];
          pairKV[i].dataNum = arr_B->pairKV[i].dataNum;
          strcpy(pairKV[i].data, arr_B->pairKV[i].data);
        }
        delete(arr_B);
    }
    return this;
}

TVector::~TVector() {
    for (int i = 0; i < vectCap; i++) {
        delete[] pairKV[i].data;
    }
    delete[] pairKV;
}

bool Compare(pairElem l, pairElem r) {
    return l.dataNum < r.dataNum;
}

int main(int argc, char *argv[]) {
    if(argc == 1) {
        TVector* vec = new TVector(std::cin);
        vec->RadixSort();
        vec->Print();
        delete(vec);
    }
    if (argc > 1) {
        std::cout << "argv[1] " << argv[1] << std::endl;
        TVector* vec = new TVector(std::cin);
        unsigned int start = clock();
        vec->RadixSort();
        unsigned int end = clock();
        std::cout << "RADIX: " << end-start << " ms." << std::endl;
        start = clock();
        std::stable_sort(vec->pairKV, (vec->pairKV + (vec->vectSize)), Compare);
        end = clock();
        std::cout << "STD: " << end-start << " ms." << std::endl;
    }
    getchar();
    return 0;
}
