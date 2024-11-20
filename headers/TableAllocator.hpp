#ifndef TABLEALLOC
#define TABLEALLOC

#include <iostream>
#include "./delcarations/Structs.hpp"
#include "./delcarations/Defines.hpp"
#include "./GetFileMappingData.hpp"
#include <memory>

class TableAllocator{
        public:
                shared_ptr<AllocDescriptor> allocTable;
                TableAllocator(FileDescriptor);
                void freeMemory(Intervals freeableInterval);
                int getMemory(int length);
};

#endif // !