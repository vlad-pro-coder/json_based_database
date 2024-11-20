#include "../../headers/SmallestIDfinder.hpp"

using namespace std;

SmallIDfinder::SmallIDfinder(shared_ptr<indexBlocksContainer> blocksContainer)
{
    for (int i = 1; i < 32; i++)
        if ((1 << i) > blocksContainer->length){
            length = blocksContainer->length;
            break;
        }  
        
    IndexArr = make_unique<int[]>(length + 1);

    for(auto buc:(*blocksContainer->indexBlocks)){
        cout<<buc.first<<" offset "<<buc.second.startOffset<<" length "<<buc.second.LengthBlock<<'\n';
    }
    for(auto buc:(*blocksContainer->indexBlocks))
        setIdTaken(buc.first);
}

void SmallIDfinder::ExpandIndexFinder()
{
    length *= 2;
    shared_ptr<int[]> newArray = make_unique<int[]>(length + 1);

    for (size_t i = 1; i <= length / 2; i++)
    {
        int value = getSum(i) - getSum(i - 1);

        for (int j = i; j <= length; j += (j & (-j)))
            newArray[j] += value;
    }

    IndexArr = newArray;
}

int SmallIDfinder::getSum(int pos)
{
    int sum = 0;
    for (; pos >= 1; pos -= (pos & (-pos)))
        sum += IndexArr[pos];
    return sum;
}

void SmallIDfinder::setIdTaken(int pos)
{
    if(pos == 0)
        return ;
    for (; pos <= length; pos += (pos & (-pos)))
        IndexArr[pos] += 1;
}

void SmallIDfinder::removeIdTaken(int pos)
{
    for (; pos <= length; pos += (pos & (-pos)))
        IndexArr[pos] -= 1;
}

int SmallIDfinder::findAvailableId()
{

    int st = 0, dr = length + 1;
    while (st + 1 < dr)
    {
        int mid = (st + dr) >> 1;
        if (getSum(mid) == mid)
            st = mid;
        else
            dr = mid;
    }
    if(dr == length+1)
        ExpandIndexFinder();
    setIdTaken(dr);
    return dr;
}