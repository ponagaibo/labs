#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <memory>
#include "TFigure.h"
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
    TSmartStack<TFigure> stack;
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
                //cout << " ***** PRINT STACK: *****\n" << stack << endl;
                cout << " ***** ITERATION: *****" << endl;
                for (auto i : stack)
                    i->Print();
            } else {
                cout << "Stack is empty." << endl;
            }
        } else if (com == 4) {
            if (stack.Empty()) {
                cout << "Stack is empty." << endl;
            } else {
                stack.Clear();
            }
        } else {
            cout << "Wrong number of command!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}


/*
int main() {
    TSmartStack<TFigure> stack;
    TAllocationBlock allocator(sizeof(int), 2);
    std::cout << "*** INITED ***" << std::endl;
    int *a1 = nullptr;
    int *a2 = nullptr;
    int *a3 = nullptr;
    int *a4 = nullptr;
    int *a5 = nullptr;

    a1 = (int*)allocator.Allocate();
    *a1 = 11;
    std::cout << "a1 pointer value:" << *a1 << std::endl;
    a2 = (int*)allocator.Allocate();
    *a2 = 22;
    std::cout << "a2 pointer value:" << *a2 << std::endl;
    a3 = (int*)allocator.Allocate();
    *a3 = 33;
    std::cout << "a3 pointer value:" << *a3 << std::endl;

    allocator.Deallocate(a1);
    allocator.Deallocate(a3);

    a4 = (int*)allocator.Allocate();
    *a4 = 44;
    std::cout << "a4 pointer value:" << *a4 << std::endl;
    a5 = (int*)allocator.Allocate();
    *a5 = 55;
    std::cout << "a5 pointer value:" << *a5 << std::endl;
    std::cout << "*** ALL ***" << std::endl;
    std::cout << "a1 pointer value:" << *a1 << std::endl;
    std::cout << "a2 pointer value:" << *a2 << std::endl;
    std::cout << "a3 pointer value:" << *a3 << std::endl;
    std::cout << "a4 pointer value:" << *a4 << std::endl;
    std::cout << "a5 pointer value:" << *a5 << std::endl;
    allocator.Deallocate(a2);
    allocator.Deallocate(a4);
    allocator.Deallocate(a5);
    return 0;
}
*/
