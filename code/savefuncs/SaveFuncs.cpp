#include "../../headers/JSON_Class.hpp"

using namespace std;

void JSON::save_DB(shared_ptr<NestedMaps> node, string key)
{
        if (holds_alternative<unordered_map<string, shared_ptr<NestedMaps>>>(node->data))
        {
                auto& mp = get<unordered_map<string, shared_ptr<NestedMaps>>>(node->data);
                for (auto &buc : mp)
                {
                        if (buc.second != nullptr)
                                save_DB(buc.second, buc.first);
                }
                save_map(node, key);
                
        }
        if (holds_alternative<int>(node->data))
                save_int(node, key);
        if (holds_alternative<double>(node->data))
                save_double(node, key);
        if (holds_alternative<long long>(node->data))
                save_long(node, key);
        if (holds_alternative<bool>(node->data))
                save_bool(node, key);
        if (holds_alternative<string>(node->data))
                save_string(node, key);
}

void JSON::save_indexes(shared_ptr<indexBlocksContainer> indexes)
{
        int currsize = indexes->indexBlocks->size();

        lseek(indexesFile.FileDesc, 0, SEEK_SET);
        write(indexesFile.FileDesc, &currsize, INTSIZE);

        int i=0;
        for (auto &buc : (*indexes->indexBlocks))
        {
                lseek(indexesFile.FileDesc, INTSIZE + (3*i)* INTSIZE, SEEK_SET);
                write(indexesFile.FileDesc, &buc.first, INTSIZE);

                lseek(indexesFile.FileDesc, INTSIZE + (3*i+1)*INTSIZE, SEEK_SET);
                write(indexesFile.FileDesc, &buc.second.startOffset, INTSIZE);

                lseek(indexesFile.FileDesc, INTSIZE + (3*i+2)*INTSIZE, SEEK_SET);
                write(indexesFile.FileDesc, &buc.second.LengthBlock, INTSIZE);

                i++;
        }
}

void JSON::save_freeMemTable(shared_ptr<AllocDescriptor> allocTable){

        int num_interv = allocTable->freeIntervals->size();
        lseek(TableAllocFile.FileDesc, 0, SEEK_SET);
        write(TableAllocFile.FileDesc, &num_interv, INTSIZE);

        lseek(TableAllocFile.FileDesc, INTSIZE, SEEK_SET);
        write(TableAllocFile.FileDesc, &allocTable->limit, INTSIZE);

        int i=0;
        for (auto &buc : (*allocTable->freeIntervals))
        {
                lseek(TableAllocFile.FileDesc, 2*INTSIZE + (2*i)* INTSIZE, SEEK_SET);
                write(TableAllocFile.FileDesc, &buc.start, INTSIZE);

                lseek(TableAllocFile.FileDesc, 2*INTSIZE + (2*i+1)*INTSIZE, SEEK_SET);
                write(TableAllocFile.FileDesc, &buc.end, INTSIZE);

                i++;
        }
}