#include "../../headers/JSON_Class.hpp"

using namespace std;

void JSON::save_map(shared_ptr<NestedMaps> node, string key)
{
        /// check if newly created
        if (node->updated && node->id != -1)
        {
                Intervals todelete;
                todelete.start = (*existingIndexes->indexBlocks)[node->id].startOffset;
                todelete.end = (*existingIndexes->indexBlocks)[node->id].startOffset + (*existingIndexes->indexBlocks)[node->id].LengthBlock - 1;
                FreeTable.freeMemory(todelete);
        }
        if (node->id == -1)
                node->id = IndexFinder.findAvailableId();

        if (node->updated)
        {
                auto& mp = get<unordered_map<string, shared_ptr<NestedMaps>>>(node->data);
                int lengthBlock = CHARSIZE + SHORTSIZE + CHARSIZE * key.size() + INTSIZE * (mp.size() + 1);
                int Offset = FreeTable.getMemory(lengthBlock);

                indexBlock newblock;
                newblock.LengthBlock = lengthBlock;
                newblock.startOffset = Offset;
                (*existingIndexes->indexBlocks)[node->id] = newblock;

                char type = 1;
                short keysize = key.size();

                lseek(jsonDBFile.FileDesc, Offset, SEEK_SET);
                write(jsonDBFile.FileDesc, &type, CHARSIZE);

                lseek(jsonDBFile.FileDesc, Offset + CHARSIZE, SEEK_SET);
                write(jsonDBFile.FileDesc, &keysize, SHORTSIZE);

                for (int i = 0; i < keysize; i++)
                {
                        lseek(jsonDBFile.FileDesc, Offset + CHARSIZE + SHORTSIZE + i * CHARSIZE, SEEK_SET);
                        write(jsonDBFile.FileDesc, &key[i], CHARSIZE);
                }

                int skipbytes = CHARSIZE + SHORTSIZE + keysize * CHARSIZE;

                int numchildren = mp.size();
                lseek(jsonDBFile.FileDesc, Offset + skipbytes, SEEK_SET);
                write(jsonDBFile.FileDesc, &numchildren, INTSIZE);

                int i = 0;
                for (const auto &buc : mp)
                {
                        lseek(jsonDBFile.FileDesc, Offset + skipbytes + INTSIZE + i * INTSIZE, SEEK_SET);
                        write(jsonDBFile.FileDesc, &buc.second->id, INTSIZE);
                        i++;
                }
        }
}

void JSON::save_int(shared_ptr<NestedMaps> node, string key){
        if (node->updated && node->id != -1)
        {
                Intervals todelete;
                todelete.start = (*existingIndexes->indexBlocks)[node->id].startOffset;
                todelete.end = (*existingIndexes->indexBlocks)[node->id].startOffset + (*existingIndexes->indexBlocks)[node->id].LengthBlock - 1;
                FreeTable.freeMemory(todelete);
        }
        if (node->id == -1)
                node->id = IndexFinder.findAvailableId();

        if (node->updated)
        {
                int lengthBlock = CHARSIZE + SHORTSIZE + CHARSIZE * key.size() + INTSIZE;
                int Offset = FreeTable.getMemory(lengthBlock);

                indexBlock newblock;
                newblock.LengthBlock = lengthBlock;
                newblock.startOffset = Offset;
                (*existingIndexes->indexBlocks)[node->id] = newblock;

                char type = 2;
                short keysize = key.size();

                lseek(jsonDBFile.FileDesc, Offset, SEEK_SET);
                write(jsonDBFile.FileDesc, &type, CHARSIZE);

                lseek(jsonDBFile.FileDesc, Offset + CHARSIZE, SEEK_SET);
                write(jsonDBFile.FileDesc, &keysize, SHORTSIZE);

                for (int i = 0; i < keysize; i++)
                {
                        lseek(jsonDBFile.FileDesc, Offset + CHARSIZE + SHORTSIZE + i * CHARSIZE, SEEK_SET);
                        write(jsonDBFile.FileDesc, &key[i], CHARSIZE);
                }
                int skipbytes = CHARSIZE + SHORTSIZE + keysize * CHARSIZE;
                auto& val = get<int>(node->data);
                lseek(jsonDBFile.FileDesc, Offset + skipbytes, SEEK_SET);
                write(jsonDBFile.FileDesc, &val, INTSIZE);
        }
}

void JSON::save_long(shared_ptr<NestedMaps> node, string key){
        if (node->updated && node->id != -1)
        {
                Intervals todelete;
                todelete.start = (*existingIndexes->indexBlocks)[node->id].startOffset;
                todelete.end = (*existingIndexes->indexBlocks)[node->id].startOffset + (*existingIndexes->indexBlocks)[node->id].LengthBlock - 1;
                FreeTable.freeMemory(todelete);
        }
        if (node->id == -1)
                node->id = IndexFinder.findAvailableId();

        if (node->updated)
        {
                int lengthBlock = CHARSIZE + SHORTSIZE + CHARSIZE * key.size() + LONGSIZE;
                int Offset = FreeTable.getMemory(lengthBlock);

                indexBlock newblock;
                newblock.LengthBlock = lengthBlock;
                newblock.startOffset = Offset;
                (*existingIndexes->indexBlocks)[node->id] = newblock;

                char type = 3;
                short keysize = key.size();

                lseek(jsonDBFile.FileDesc, Offset, SEEK_SET);
                write(jsonDBFile.FileDesc, &type, CHARSIZE);

                lseek(jsonDBFile.FileDesc, Offset + CHARSIZE, SEEK_SET);
                write(jsonDBFile.FileDesc, &keysize, SHORTSIZE);

                for (int i = 0; i < keysize; i++)
                {
                        lseek(jsonDBFile.FileDesc, Offset + CHARSIZE + SHORTSIZE + i * CHARSIZE, SEEK_SET);
                        write(jsonDBFile.FileDesc, &key[i], CHARSIZE);
                }
                int skipbytes = CHARSIZE + SHORTSIZE + keysize * CHARSIZE;
                auto& val = get<long long>(node->data);
                lseek(jsonDBFile.FileDesc, Offset + skipbytes, SEEK_SET);
                write(jsonDBFile.FileDesc, &val, LONGSIZE);
        }
}

void JSON::save_double(shared_ptr<NestedMaps> node, string key){
        if (node->updated && node->id != -1)
        {
                Intervals todelete;
                todelete.start = (*existingIndexes->indexBlocks)[node->id].startOffset;
                todelete.end = (*existingIndexes->indexBlocks)[node->id].startOffset + (*existingIndexes->indexBlocks)[node->id].LengthBlock - 1;
                FreeTable.freeMemory(todelete);
        }
        if (node->id == -1)
                node->id = IndexFinder.findAvailableId();

        if (node->updated)
        {
                int lengthBlock = CHARSIZE + SHORTSIZE + CHARSIZE * key.size() + DOUBLESIZE;
                int Offset = FreeTable.getMemory(lengthBlock);

                indexBlock newblock;
                newblock.LengthBlock = lengthBlock;
                newblock.startOffset = Offset;
                (*existingIndexes->indexBlocks)[node->id] = newblock;

                char type = 4;
                short keysize = key.size();

                lseek(jsonDBFile.FileDesc, Offset, SEEK_SET);
                write(jsonDBFile.FileDesc, &type, CHARSIZE);

                lseek(jsonDBFile.FileDesc, Offset + CHARSIZE, SEEK_SET);
                write(jsonDBFile.FileDesc, &keysize, SHORTSIZE);

                for (int i = 0; i < keysize; i++)
                {
                        lseek(jsonDBFile.FileDesc, Offset + CHARSIZE + SHORTSIZE + i * CHARSIZE, SEEK_SET);
                        write(jsonDBFile.FileDesc, &key[i], CHARSIZE);
                }
                int skipbytes = CHARSIZE + SHORTSIZE + keysize * CHARSIZE;
                auto& val = get<double>(node->data);
                lseek(jsonDBFile.FileDesc, Offset + skipbytes, SEEK_SET);
                write(jsonDBFile.FileDesc, &val, LONGSIZE);
        }
}

void JSON::save_bool(shared_ptr<NestedMaps> node, string key){
        if (node->updated && node->id != -1)
        {
                Intervals todelete;
                todelete.start = (*existingIndexes->indexBlocks)[node->id].startOffset;
                todelete.end = (*existingIndexes->indexBlocks)[node->id].startOffset + (*existingIndexes->indexBlocks)[node->id].LengthBlock - 1;
                FreeTable.freeMemory(todelete);
        }
        if (node->id == -1)
                node->id = IndexFinder.findAvailableId();

        if (node->updated)
        {
                int lengthBlock = CHARSIZE + SHORTSIZE + CHARSIZE * key.size() + BOOLSIZE;
                int Offset = FreeTable.getMemory(lengthBlock);

                indexBlock newblock;
                newblock.LengthBlock = lengthBlock;
                newblock.startOffset = Offset;
                (*existingIndexes->indexBlocks)[node->id] = newblock;

                char type = 5;
                short keysize = key.size();

                lseek(jsonDBFile.FileDesc, Offset, SEEK_SET);
                write(jsonDBFile.FileDesc, &type, CHARSIZE);

                lseek(jsonDBFile.FileDesc, Offset + CHARSIZE, SEEK_SET);
                write(jsonDBFile.FileDesc, &keysize, SHORTSIZE);

                for (int i = 0; i < keysize; i++)
                {
                        lseek(jsonDBFile.FileDesc, Offset + CHARSIZE + SHORTSIZE + i * CHARSIZE, SEEK_SET);
                        write(jsonDBFile.FileDesc, &key[i], CHARSIZE);
                }
                int skipbytes = CHARSIZE + SHORTSIZE + keysize * CHARSIZE;
                auto& val = get<bool>(node->data);
                lseek(jsonDBFile.FileDesc, Offset + skipbytes, SEEK_SET);
                write(jsonDBFile.FileDesc, &val, BOOLSIZE);
        }
}

void JSON::save_string(shared_ptr<NestedMaps> node, string key){
        if (node->updated && node->id != -1)
        {
                Intervals todelete;
                todelete.start = (*existingIndexes->indexBlocks)[node->id].startOffset;
                todelete.end = (*existingIndexes->indexBlocks)[node->id].startOffset + (*existingIndexes->indexBlocks)[node->id].LengthBlock - 1;
                FreeTable.freeMemory(todelete);
        }
        if (node->id == -1)
                node->id = IndexFinder.findAvailableId();

        if (node->updated)
        {
                auto& str = get<string>(node->data);
                int lengthBlock = CHARSIZE + SHORTSIZE + CHARSIZE * key.size() + INTSIZE + CHARSIZE * str.size();
                int Offset = FreeTable.getMemory(lengthBlock);

                indexBlock newblock;
                newblock.LengthBlock = lengthBlock;
                newblock.startOffset = Offset;
                (*existingIndexes->indexBlocks)[node->id] = newblock;

                char type = 6;
                short keysize = key.size();

                lseek(jsonDBFile.FileDesc, Offset, SEEK_SET);
                write(jsonDBFile.FileDesc, &type, CHARSIZE);

                lseek(jsonDBFile.FileDesc, Offset + CHARSIZE, SEEK_SET);
                write(jsonDBFile.FileDesc, &keysize, SHORTSIZE);

                for (int i = 0; i < keysize; i++)
                {
                        lseek(jsonDBFile.FileDesc, Offset + CHARSIZE + SHORTSIZE + i * CHARSIZE, SEEK_SET);
                        write(jsonDBFile.FileDesc, &key[i], CHARSIZE);
                }
                int skipbytes = CHARSIZE + SHORTSIZE + keysize * CHARSIZE;
                
                int strsize = str.size();
                lseek(jsonDBFile.FileDesc, Offset + skipbytes, SEEK_SET);
                write(jsonDBFile.FileDesc, &strsize, INTSIZE);

                for(int i=0;i<strsize;i++)
                {
                        lseek(jsonDBFile.FileDesc, Offset + skipbytes + INTSIZE, SEEK_SET);
                        write(jsonDBFile.FileDesc, &str[i], CHARSIZE);   
                }
        }
}