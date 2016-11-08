#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include "TSquare.h"
#include "TRectangle.h"
#include "TTrapeze.h"
#include "TSmartStackItem.h"
#include "TSmartStack.h"
using namespace std;

int PrintMenu() {
    int com;
    cout << "\n********* MENU *********" << endl;
    cout << "1. Add figure in stack" << endl;
    cout << "2. Get figure from stack" << endl;
    cout << "3. Print stack" << endl;
    cout << "4. Delete stack" << endl;
    cout << "0. Quit" << endl;
    cout << "Enter command: " << endl;
    cin >> com;
    return com;
}

int PrintFigures() {
    int com;
    cout << "\n********* CHOOSE FIGURE *********" << endl;
    cout << "1. Rectangle" << endl;
    cout << "2. Square" << endl;
    cout << "3. Trapeze" << endl;
    cout << "Enter command: " << endl;
    cin >> com;
    return com;
}

int main() {
    TSmartStack stack;
    int com;
    while(com = PrintMenu()) {
        if (com == 1) {
            system("cls");
            int f = PrintFigures();
            if (f == 1) {
                cout << "Enter size of rectangle (first side, second side): " << endl;
                int a, b;
                cin >> a >> b;
                stack.Push(shared_ptr<TFigure>(new TRectangle(a,b)));
            } else if (f == 2) {
                cout << "Enter size of square (side): " << endl;
                int a;
                cin >> a;
                stack.Push(shared_ptr<TFigure>(new TSquare(a)));
            } else if (f == 3) {
                cout << "Enter size of trapeze (first side, second side, height): " << endl;
                int a, b, h;
                cin >> a >> b >> h;
                stack.Push(shared_ptr<TFigure>(new TTrapeze(a,b,h)));
            } else {
                cout << "Unknown figure!" << endl;
            }
        } else if (com == 2) {
            system("cls");
            if (!stack.Empty()) {
                shared_ptr<TFigure> s = stack.Pop();
                cout << " ***** RECEIVED FIGURE: *****" << endl;
                s->Print();
            } else {
                cout << "Stack is empty." << endl;
            }
        } else if (com == 3) {
            system("cls");
            if (!stack.Empty()) {
                cout << " ***** PRINT STACK: *****\n" << stack << endl;
            } else {
                cout << "Stack is empty." << endl;
            }
        } else if (com == 4) {
            if (!stack.Empty()) {
                delete &stack;
            } else {
                cout << "Stack is empty." << endl;
            }
        } else {
            cout << "Wrong number of command!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}
