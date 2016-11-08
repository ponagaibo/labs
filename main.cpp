#include <cstdlib>
#include <iostream>
#include "Square.h"
#include "TStackItem.h"
#include "TStack.h"
using namespace std;

int PrintMenu() {
    int com;
    cout << "\n********* MENU *********" << endl;
    cout << "1. Add square in stack" << endl;
    cout << "2. Get square from stack" << endl;
    cout << "3. Print stack" << endl;
    cout << "4. Delete stack" << endl;
    cout << "0. Quit" << endl;
    cout << "Enter command: " << endl;
    cin >> com;
    return com;
}

int main() {
    TStack stack;
    int com;
    while(com = PrintMenu()) {
        if (com == 1) {
            cout << "Enter size of square: " << endl;
            TSquare sq;
            cin >> sq;
            cout << sq << endl;
            stack.Push(sq);
        } else if (com == 2) {
            if (!stack.Empty()) {
                TSquare s;
                s = stack.Pop();
                std::cout << s;
            } else {
                cout << "Stack is empty." << endl;
            }
        } else if (com == 3) {
            if (!stack.Empty()) {
                cout << stack;
            } else {
                cout << "Stack is empty." << endl;
            }
        } else if (com == 4) {
            delete &stack;
        } else {
            cout << "Wrong number of command!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
