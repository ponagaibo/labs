#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED
#include <cstdlib>
#include <iostream>

class TSquare{
private:
    size_t side;
public:
    TSquare();
    TSquare(size_t side_n);
    TSquare(const TSquare& orig);

    double SquareOfFigure();

    friend std::ostream& operator<<(std::ostream& os, const TSquare& obj);
    friend std::istream& operator>>(std::istream& is, TSquare& obj);
    friend TSquare operator+(const TSquare& left, const TSquare& right);
    bool operator==(const TSquare& rightSq);
    TSquare& operator=(const TSquare& rightSq);
    TSquare& operator++();

    void Print();
    virtual ~TSquare();
};

#endif // SQUARE_H_INCLUDED
