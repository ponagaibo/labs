#include <iostream>
#include <cmath>
#include "figure.h"
#include "trapeze.h"

FTrapeze::FTrapeze() : FTrapeze(0,0,0) {}
FTrapeze::FTrapeze(std::istream &is) {
    is >> side_a;
    is >> side_b;
    is >> h;
}
FTrapeze::FTrapeze(const FTrapeze& orig) {
    std::cout << "Trapeze copy created" << std::endl;
    side_a = orig.side_a;
    side_b = orig.side_b;
    h = orig.h;
}
FTrapeze::FTrapeze(size_t side_n, size_t side_m, size_t hh) : side_a(side_n), side_b(side_m), h(hh) {
    std::cout << "Trapeze created: " << side_a << ", " << side_b << ", " << h << std::endl;
}
double FTrapeze::Square() {
    return double( (side_a + side_b) / 2.0 * h);
}
void FTrapeze::Print() {
    std::cout << "a = " << side_a << ", b = " << side_b << ", h = " << h << std::endl;
}
FTrapeze::~FTrapeze() {
    std::cout << "Trapeze deleted" << std::endl;
}
