#ifndef TFIGURE_H_INCLUDED
#define TFIGURE_H_INCLUDED

class TFigure {
public:
    virtual double SquareOfFigure() = 0;
    virtual void Print() = 0;
    virtual ~TFigure() {};
};

#endif // TFIGURE_H_INCLUDED
