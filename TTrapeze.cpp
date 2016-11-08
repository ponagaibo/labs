#include <iostream>
#include <cmath>
#include "TFigure.h"
#include "TTrapeze.h"

TTrapeze::TTrapeze() : TTrapeze(0,0,0) {}
TTrapeze::TTrapeze(std::istream &is) {
    is >> side_a;
    is >> side_b;
    is >> h;
}
TTrapeze::TTrapeze(const TTrapeze& orig) {
    std::cout << "Trapeze copy created" << std::endl;
    side_a = orig.side_a;
    side_b = orig.side_b;
    h = orig.h;
}
TTrapeze::TTrapeze(size_t side_n, size_t side_m, size_t hh) : side_a(side_n), side_b(side_m), h(hh) {
    std::cout << "Trapeze created: " << side_a << ", " << side_b << ", " << h << std::endl;
}

TTrapeze& TTrapeze::operator=(const TTrapeze& rightTr) {
    if (this == &rightTr) {
        return *this;
    }
    side_a = rightTr.side_a;
    side_b = rightTr.side_b;
    h = rightTr.h;
    return *this;
}

void TTrapeze::Print() {
    std::cout << "TRAPEZE: a = " << side_a << ", b = " << side_b << ", h = " << h << std::endl;
}

std::ostream& operator<<(std::ostream& os, const TTrapeze& obj) {
    //os << "TRAPEZE: a = " << obj.side_a << ", b = " << obj.side_b << ", h = " << obj.h;
    return os;
}

TTrapeze::~TTrapeze() {
    //std::cout << "Trapeze deleted" << std::endl;
}
