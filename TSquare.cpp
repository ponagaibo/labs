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

TSquare& TSquare::operator=(const TSquare& rightSq) {
    if (this == &rightSq) {
        return *this;
    }
    side = rightSq.side;
    return *this;
}

void TSquare::Print() {
    std::cout << "SQUARE: side = " << side << std::endl;
}

std::ostream& operator<<(std::ostream& os, const TSquare& obj) {
    //os << "SQUARE: side = " << obj.side;
    return os;
}

TSquare::~TSquare() {
    //std::cout << "Square deleted" << std::endl;
}
