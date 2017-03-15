#include <iostream>
#include <bits/stdc++.h>
#include <climits>
#include <string>

int main() {
    srand(time(NULL));
    std::cout << "enter file name" << std::endl;
    std::string name;
    std::getline (std::cin, name);
    std::ofstream F(name, std::ios::app);
    //unsigned long long am1 = rand() % 1000000 + 1000000;
    int num;

    //unsigned long long am2 = rand() % 1000000 + 1000000;
    for (unsigned long long j = 0; j < 1000; ++j) {
        int r = rand() % 47 + 3;
        for (unsigned long long i = 0; i < r; ++i) {
            num = rand() % 26 + 97;
            F << (char)num;
        }
        F << '\n';
    }
}
