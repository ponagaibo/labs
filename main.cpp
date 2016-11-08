#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include "square.h"
#include "rectangle.h"
#include "trapeze.h"
using namespace std;

int print_menu() {
    int com;
    cout << "********* MENU *********" << endl;
    cout << "1. Square of square" << endl;
    cout << "2. Square of rectangle" << endl;
    cout << "3. Square of trapeze" << endl;
    cout << "4. Quit" << endl;
    cout << "Enter command: " << endl;
    cin >> com;
    return com;
}

int main() {
    int com = print_menu();
    while(1) {
        if (com == 1) {
            cout << "Enter size of square: " << endl;
            Figure *ptr = new FSquare(cin);
            ptr->Print();
            cout << "Square = " << ptr->Square() << endl;
            delete ptr;
            com = print_menu();
        } else if (com == 2) {
            cout << "Enter size of rectangle: " << endl;
            Figure *ptr = new FRectangle(cin);
            ptr->Print();
            cout << "Square = " << ptr->Square() << endl;
            delete ptr;
            com = print_menu();
        } else if (com == 3) {
            cout << "Enter size of trapeze: " << endl;
            Figure *ptr = new FTrapeze(cin);
            ptr->Print();
            cout << "Square = " << ptr->Square() << endl;
            delete ptr;
            com = print_menu();
        } else if (com == 4) {
            exit(0);
        } else {
            cout << "Wrong number of command!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
