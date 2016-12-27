#ifndef TALLOCATIONBLOCK_H_INCLUDED
#define TALLOCATIONBLOCK_H_INCLUDED

#include <cstdlib>
#include <mutex>
#include "TTreeAlloc.h"

class TAllocationBlock {
public:
    TAllocationBlock(size_t size, size_t count);
    void* Allocate();
    void Deallocate(void* pointer);
    virtual ~TAllocationBlock();

private:
    char* usedBlocks;
    TTreeAlloc<void*> freeBlocks;
    size_t blockSize;
    size_t freeCount;
    size_t cap;
    bool hasFree;
    //std::mutex allocMutex;
};

#endif // TALLOCATIONBLOCK_H_INCLUDED
