#ifndef STRUCTS
#define STRUCTS

#include <vector>
#include <unordered_map>
#include <variant>
#include <string>
#include <memory>
#include <set>

using std::unordered_map;
using std::variant;
using std::string;
using std::shared_ptr;

struct NestedMaps {
    variant<bool,int,string,double,long long, unordered_map<string, shared_ptr<NestedMaps>>> data;
    int id;
    bool updated;
    bool isLoaded;
};

struct FileDescriptor{
    int FileDesc=-1;
    uint32_t FileLength;
};

struct Intervals{
    int start;
    int end;

    bool operator < (const Intervals& interval)const {
        if(start != interval.start)
            return start < interval.start;
        return end < interval.end;
    }
    int length()const {
        return end-start+1;
    }
};

struct AllocDescriptor{
    int limit;
    shared_ptr<std::set<Intervals>> freeIntervals;
};

struct indexBlock{
    int startOffset;
    int LengthBlock;
    ///startOffset - start offset of the json node
    ///LengthBlock - length of the block with that offset;
};

struct indexBlocksContainer{
    int length;
    shared_ptr<unordered_map<int,indexBlock>>indexBlocks;
};

#endif 