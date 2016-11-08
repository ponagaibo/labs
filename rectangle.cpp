#include "rectangle.h"
#include <iostream>
#include <cmath>
#include "figure.h"

FRectangle::FRectangle() : FRectangle(0,0) {}
FRectangle::FRectangle(std::istream &is) {
    is >> side_a;
    is >> side_b;
}
FRectangle::FRectangle(const FRectangle& orig) {
    std::cout << "Rectangle copy created" << std::endl;
    side_a = orig.side_a;
    side_b = orig.side_b;
}
FRectangle::FRectangle(size_t side_n, size_t side_m) : side_a(side_n), side_b(side_m) {
    std::cout << "Rectangle created: " << side_a << ", " << side_b << std::endl;
}
double FRectangle::Square() {
    return double(side_a * side_b);
}
void FRectangle::Print() {
    std::cout << "a = " << side_a << ", b = " << side_b << std::endl;
}
FRectangle::~FRectangle() {
    std::cout << "Rectangle deleted" << std::endl;
}
