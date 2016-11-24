#include <bits/stdc++.h>
#include <climits>

int main() {
    srand(time(NULL));

    std::ofstream F("t1.txt", std::ios::app);

    int n;
    std::cin >> n;

    int a = 1 + (rand() % 4);
    int num;
    for (int i = 0; i < a; ++i) {
        num = rand() % ULLONG_MAX;
        F << num << " ";
    }
    F << '\n';

    for(int i = 0; i < n; i++) {

        int cnt = rand() % 50;
        for(int j = 0; j < cnt; j++) {
            int num = rand() % ULLONG_MAX;
            F << num;
            if(j + 1 < cnt) {
                F << " ";
            }
        }
        F << '\n';
    }
}
