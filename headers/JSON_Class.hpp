#ifndef JSONCLASS
#define JSONCLASS


#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <variant>
#include <string>
#include <iostream>
#include <memory>
#include "./delcarations/Structs.hpp"
#include "./GetFileMappingData.hpp"
#include "./ReadNodeData.hpp"
#include "./TableAllocator.hpp"
#include "./SmallestIDfinder.hpp"

using std::shared_ptr;
using std::string;
using std::vector;

class JSON{
private:
        shared_ptr<indexBlocksContainer> existingIndexes;
        shared_ptr<NestedMaps> root;
        FileDescriptor jsonDBFile,indexesFile,TableAllocFile;
        TableAllocator FreeTable;
        SmallIDfinder IndexFinder;

        shared_ptr<NestedMaps> create_instance();
        
        void save_DB(shared_ptr<NestedMaps> node,string key);
        void save_indexes(shared_ptr<indexBlocksContainer> indexes);
        void save_freeMemTable(shared_ptr<AllocDescriptor> allocTable);

        void save_map(shared_ptr<NestedMaps> node, string key);
        void save_int(shared_ptr<NestedMaps> node, string key);
        void save_long(shared_ptr<NestedMaps> node, string key);
        void save_double(shared_ptr<NestedMaps> node, string key);
        void save_bool(shared_ptr<NestedMaps> node, string key);
        void save_string(shared_ptr<NestedMaps> node, string key);
public:
        JSON();
        void closeDB();
        void set(const vector<string>& path,variant<bool,int,string,double,long long> value);
        variant<bool,int,string,double,long long> getValue(const vector<string>& path) const;
        variant<bool,int,string,double,long long> operator [](const vector<string>& path) const;
};

#endif