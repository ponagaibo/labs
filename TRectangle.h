#ifndef TRECTANGLE_H_INCLUDED
#define TRECTANGLE_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include "TFigure.h"

class TRectangle : public TFigure {
public:
    TRectangle();
    TRectangle(std::istream &is);
    TRectangle(size_t side_n, size_t side_m);
    TRectangle(const TRectangle& orig);

    TRectangle& operator=(const TRectangle& rightRe);
    friend std::ostream& operator<<(std::ostream& os, const TRectangle& obj);
    double SquareOfFigure();
    void Print();

    bool operator==(TFigure& other) override;
    bool operator<(TFigure& other) override;
    bool operator>(TFigure& other) override;
    bool operator<=(TFigure& other) override;
    bool operator>=(TFigure& other) override;
    operator double ();

    //void* operator new (size_t size);
    //void operator delete(void *pointer);
    virtual ~TRectangle();
private:
    size_t side_a;
    size_t side_b;
    //static TAllocationBlock allocator;
};

#endif // TRECTANGLE_H_INCLUDED
