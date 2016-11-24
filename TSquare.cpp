#include "TFigure.h"
#include "TSquare.h"
#include <iostream>
#include <cmath>

TSquare::TSquare() : TSquare(0) {}
TSquare::TSquare(std::istream &is) {
    is >> side;
}
TSquare::TSquare(const TSquare& orig) {
    std::cout << "Square copy created" << std::endl;
    side = orig.side;
}
TSquare::TSquare(size_t side_n) : side(side_n) {
    std::cout << "Square created: " << side << std::endl;
}

/*
std::ostream& operator<<(std::ostream& os, const TSquare& obj) {
    os << "SQUARE sq: side = " << obj.side;
    return os;
}
*/

std::istream& operator>>(std::istream& is, TSquare& obj) {
    is >> obj.side;
    return is;
}
TSquare operator+(const TSquare& leftSq, const TSquare& rightSq) {
    return TSquare(leftSq.side + rightSq.side);
}
TSquare& TSquare::operator++() {
    side++;
    return *this;
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

double TSquare::SquareOfFigure() {
    return double (side * side);
}
void TSquare::Print() {
    std::cout << "SQUARE: side = " << side << std::endl;
}

TSquare::~TSquare() {
    std::cout << "Square deleted" << std::endl;
}
