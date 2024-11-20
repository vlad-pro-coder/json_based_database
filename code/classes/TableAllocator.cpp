#include "../../headers/TableAllocator.hpp"

using namespace std;

TableAllocator::TableAllocator(FileDescriptor TableAllocFile)
{
        allocTable = getFileAllocDescriptor(TableAllocFile);
}

int TableAllocator::getMemory(int length)
{ // returns the offset to start writing

        int OffsetStart = -1;
        while (true)
        {
                for (auto it = allocTable->freeIntervals->begin(); it != allocTable->freeIntervals->end(); ++it)
                {
                        if (it->length() >= length)
                        {
                                OffsetStart = it->start;
                                if (it->length() == length)
                                {
                                        allocTable->freeIntervals->erase(it);
                                        break;
                                }

                                Intervals NewInterv;
                                NewInterv.start = it->start + length;
                                NewInterv.end = it->end;

                                allocTable->freeIntervals->erase(it);
                                allocTable->freeIntervals->insert(NewInterv);
                                break;
                        }
                }
                if (OffsetStart != -1)
                        break;
                Intervals expandingInterval;
                expandingInterval.start = allocTable->limit;
                expandingInterval.end = allocTable->limit + TEN_MB - 1;
                allocTable->limit += TEN_MB;
                freeMemory(expandingInterval);
        }
        return OffsetStart;
}

void TableAllocator::freeMemory(Intervals addingInterval)
{
        if (allocTable->freeIntervals->size() != 0)
        {
                auto findBetweenInterv = allocTable->freeIntervals->lower_bound(addingInterval);
                if (findBetweenInterv != allocTable->freeIntervals->begin() && prev(findBetweenInterv)->end + 1 >= addingInterval.start)
                {
                        addingInterval.start = prev(findBetweenInterv)->start;
                        allocTable->freeIntervals->erase(prev(findBetweenInterv));
                }
                if (findBetweenInterv != allocTable->freeIntervals->end() && addingInterval.end + 1 >= findBetweenInterv->start)
                {
                        addingInterval.end = findBetweenInterv->end;
                        allocTable->freeIntervals->erase(findBetweenInterv);
                }
        }
        allocTable->freeIntervals->insert(addingInterval);
}
