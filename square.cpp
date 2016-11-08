#include "square.h"
#include <iostream>
#include <cmath>
#include "figure.h"

FSquare::FSquare() : FSquare(0) {}
FSquare::FSquare(std::istream &is) {
    is >> side;
}
FSquare::FSquare(const FSquare& orig) {
    std::cout << "Square copy created" << std::endl;
    side = orig.side;
}
FSquare::FSquare(size_t side_n) : side(side_n) {
    std::cout << "Square created: " << side << std::endl;
}

double FSquare::Square() {
    return double(side * side);
}
void FSquare::Print() {
    std::cout << "side = " << side << std::endl;
}
FSquare::~FSquare() {
    std::cout << "Square deleted" << std::endl;
}
