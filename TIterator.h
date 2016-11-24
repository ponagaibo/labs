#ifndef TITERATOR_H_INCLUDED
#define TITERATOR_H_INCLUDED

#include <memory>
#include <iostream>

template <class Node, class T>
class TIterator
{
public:
    TIterator(std::shared_ptr<Node> n)   {
        node_ptr = n;
    }

    std::shared_ptr<T> operator*() {
        return node_ptr->GetFigure();
    }

    std::shared_ptr<T> operator->(){
        return node_ptr->GetFigure();
    }

    void operator++(){
        node_ptr = node_ptr->GetNext();
    }

    bool operator==(TIterator const& i){
        return node_ptr == i.node_ptr;
    }

    bool operator!=(TIterator const& i){
        return node_ptr != i.node_ptr;
    }
private:
    std::shared_ptr<Node> node_ptr;
};

#endif // TITERATOR_H_INCLUDED
