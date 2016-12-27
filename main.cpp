#include <cstdlib>
#include <iostream>
using namespace std;
#include "TFigure.h"
#include "TSquare.h"
#include "TRectangle.h"
#include "TTrapeze.h"
#include "TSmartStackItem.h"
#include "TSmartStack.h"
#include <random>

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
    cout << "5. Add N random figures in stack" << endl;
    cout << "6. Sort" << endl;
    cout << "7. Parallel sort" << endl;
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
                cout << " ***** PRINT STACK: *****" << endl;
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
        } else if (com == 5) {
            system("cls");
            cout << "Enter the number of figures you want to add: " << endl;
            int nn;
            cin >> nn;
            int f = PrintFigures();
            if (f == 1) {
                std::default_random_engine generator;
                std::uniform_int_distribution<int> distribution(1, 100);
                for (int i = 0; i < nn; i++) {
                    int side_a = distribution(generator);
                    int side_b = distribution(generator);
                    stack.Push(shared_ptr<TFigure>(new TRectangle(side_a, side_b)));
                }
            } else if (f == 2) {
                std::default_random_engine generator;
                std::uniform_int_distribution<int> distribution(1, 100);
                for (int i = 0; i < nn; i++) {
                    int side_a = distribution(generator);
                    stack.Push(shared_ptr<TFigure>(new TSquare(side_a)));
                }
            } else if (f == 3) {
                std::default_random_engine generator;
                std::uniform_int_distribution<int> distribution(1, 100);
                for (int i = 0; i < nn; i++) {
                    int side_a = distribution(generator);
                    int side_b = distribution(generator);
                    int h = distribution(generator);
                    stack.Push(shared_ptr<TFigure>(new TTrapeze(side_a, side_b, h)));
                }
            } else {
                cout << "Unknown figure!" << endl;
            }
        } else if (com == 6) {
            if (stack.Empty()) {
                cout << "Stack is empty." << endl;
            } else {
                stack.Sort();
            }
        } else if (com == 7) {
            if (stack.Empty()) {
                cout << "Stack is empty." << endl;
            } else {
                stack.ParallelSort();
            }
        } else {
            cout << "Wrong number of command!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}


/*
int main(int argc, char** argv) {
    TSmartStack<TFigure> stack;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 100);
    for (int i = 0; i < 100; i++) {
        int sidea = distribution(generator);
        int sideb = distribution(generator);
        stack.Push(new TRectangle(sidea, sideb));
    }

    if (!stack.Empty()) {
        //cout << " ***** PRINT STACK BEFORE SORT: *****\n" << stack << endl;
        for (auto i : stack) i->Print();
    }
    std::cout << "Sort -------------" << std::endl;

    //stack.Sort();
    stack.ParallelSort();

    if (!stack.Empty()) {
        //cout << " ***** PRINT STACK AFTER SORT: *****\n" << stack << endl;
        for (auto i : stack) i->Print();
    }

    std::cout << "Done -------------" << std::endl;
    return 0;
}
*/
