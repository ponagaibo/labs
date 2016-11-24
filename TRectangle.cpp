#include "TFigure.h"
#include "TRectangle.h"
#include <iostream>
#include <cmath>

TRectangle::TRectangle() : TRectangle(0,0) {}
TRectangle::TRectangle(std::istream &is) {
    is >> side_a;
    is >> side_b;
}
TRectangle::TRectangle(const TRectangle& orig) {
    std::cout << "Rectangle copy created" << std::endl;
    side_a = orig.side_a;
    side_b = orig.side_b;
}
TRectangle::TRectangle(size_t side_n, size_t side_m) : side_a(side_n), side_b(side_m) {
    std::cout << "Rectangle created: " << side_a << ", " << side_b << std::endl;
}

TRectangle& TRectangle::operator=(const TRectangle& rightRe) {
    if (this == &rightRe) {
        return *this;
    }
    side_a = rightRe.side_a;
    side_b = rightRe.side_b;
    return *this;
}

double TRectangle::SquareOfFigure() {
    return double(side_a * side_b);
}

void TRectangle::Print() {
    std::cout << "RECTANGLE: a = " << side_a << ", b = " << side_b << std::endl;
}

/*
std::ostream& operator<<(std::ostream& os, const TRectangle& obj) {
    //os << "a = " << obj.side_a << ", b = " << obj.side_b;
    return os;
}
*/

TRectangle::~TRectangle() {
    std::cout << "Rectangle deleted" << std::endl;
}
