#include "Square.h"
#include <iostream>
#include <cmath>

TSquare::TSquare() {}

TSquare::TSquare(const TSquare& orig) {
    side = orig.side;
}
TSquare::TSquare(size_t side_n) : side(side_n) {
    std::cout << "Square created with side: " << side << std::endl;
}

double TSquare::SquareOfFigure() {
    return double(side * side);
}
void TSquare::Print() {
    std::cout << "print, side = " << side << std::endl;
}

bool TSquare::operator==(const TSquare& rightSq) {
    return side == rightSq.side;
}

TSquare& TSquare::operator=(const TSquare& rightSq) {
    if (this == &rightSq) {
        return *this;
    }
    side = rightSq.side;
    return *this;
}

TSquare& TSquare::operator++() {
    side++;
    return *this;
}
//++x;
//x++;
/*
TSquare TSquare::operator++(int) {
    TSquare temp = *this;
    ++*this;
    return temp;
}
*/

TSquare operator+(const TSquare& leftSq, const TSquare& rightSq) {
    return TSquare(leftSq.side + rightSq.side);
}

std::ostream& operator<<(std::ostream& os, const TSquare& obj) {
    os << "square, side = " << obj.side;
    return os;
}

std::istream& operator>>(std::istream& is, TSquare& obj) {
    is >> obj.side;
    return is;
}

TSquare::~TSquare() {}
