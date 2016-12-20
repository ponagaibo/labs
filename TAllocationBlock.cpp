#include "TAllocationBlock.h"
#include <iostream>

TAllocationBlock::TAllocationBlock(size_t size, size_t count) : blockSize(size), cap(count) {
    //std::cout << "** size of block: " << size << ", capacity: " << count << " **" << std::endl;
    usedBlocks = (char*)malloc(size * count);
    for(size_t i = 0; i < count; ++i) {
        void* temp = (void*)malloc(sizeof(void*));
        temp = usedBlocks + i * size;
        freeBlocks.Push(temp);
    }
    freeCount = count;
    hasFree = true;
    //std::cout << "** Memory inited **" << std::endl;
}

void* TAllocationBlock::Allocate() {
    if(!freeBlocks.Empty()) {
        freeCount--;
        //std::cout << "** Allocated " << (cap - freeCount) << " of " << cap << " **" << std::endl;
        return freeBlocks.Pop();
    } else {
        //std::cout << "** Sorry, there is no memory =\\ " << std::endl;
        throw std::bad_alloc();
    }
}

void TAllocationBlock::Deallocate(void* pointer) {
    //std::cout << "** Deallocate block **" << std::endl;
    freeBlocks.Push(pointer);
    freeCount++;
}

TAllocationBlock::~TAllocationBlock() {
    while(!freeBlocks.Empty()) {
        freeBlocks.Pop();
    }
    freeBlocks.Delete();
    free(usedBlocks);
    //std::cout << "TAllocationBlock: Memory freed" << std::endl;
}

