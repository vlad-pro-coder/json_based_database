#ifndef SMALLID
#define SMALLID

#include <iostream>
#include <memory.h>
#include "./delcarations/Structs.hpp"
#include "./delcarations/Defines.hpp"

class SmallIDfinder{
    private:
        int length;
        std::shared_ptr<int[]> IndexArr;
        void ExpandIndexFinder();
        int getSum(int pos);
        void setIdTaken(int pos);
    public:
        SmallIDfinder(shared_ptr<indexBlocksContainer> blocksContainer);
        void removeIdTaken(int pos);
        int findAvailableId();
};

#endif