#ifndef TFIGURE_H_INCLUDED
#define TFIGURE_H_INCLUDED
#include <iostream>

class TFigure {
public:
    virtual double SquareOfFigure() = 0;
    virtual void Print() = 0;
    //friend std::ostream& operator<<(std::ostream& os, const TFigure& obj);
    virtual ~TFigure() {};
};

#endif // TFIGURE_H_INCLUDED
