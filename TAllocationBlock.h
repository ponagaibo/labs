#ifndef TALLOCATIONBLOCK_H_INCLUDED
#define TALLOCATIONBLOCK_H_INCLUDED

#include <cstdlib>
#include "TTree.h"

class TAllocationBlock {
public:
    TAllocationBlock(size_t size, size_t count);
    void* Allocate();
    void Deallocate(void* pointer);
    virtual ~TAllocationBlock();

private:
    char* usedBlocks;
    TTree<void*> freeBlocks;
    size_t blockSize;
    size_t freeCount;
    size_t cap;
    bool hasFree;
};

#endif // TALLOCATIONBLOCK_H_INCLUDED
