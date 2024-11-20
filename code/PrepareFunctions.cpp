#include "../headers/PrepareFunctions.hpp"

using namespace std;

void prepare_map(int index, indexBlock block, shared_ptr<indexBlocksContainer> indexBlocksCont, FileDescriptor databaseFile, int skipbytes, shared_ptr<NestedMaps> node)
{
    int lengthchildren;
    lseek(databaseFile.FileDesc, block.startOffset + skipbytes, SEEK_SET);
    read(databaseFile.FileDesc, &lengthchildren, INTSIZE);

    node->id = index;
    node->updated = 0;
    node->isLoaded = 1;
    unordered_map<string,shared_ptr<NestedMaps>> mp;

    for (int i = 0; i < lengthchildren; i++)
    {
        int indexchild;
        shared_ptr<NestedMaps> uncompleteinstance = make_shared<NestedMaps>();

        lseek(databaseFile.FileDesc, block.startOffset + skipbytes + INTSIZE + i * INTSIZE, SEEK_SET);
        read(databaseFile.FileDesc, &indexchild, INTSIZE);

        uncompleteinstance->isLoaded = 0;
        uncompleteinstance->id = indexchild;
        uncompleteinstance->updated = 0;

        string keystring = getKey(databaseFile, (*indexBlocksCont->indexBlocks)[indexchild]);
        mp[keystring] = uncompleteinstance;
    }
    node->data = mp;
}

void prepare_int(int index, indexBlock block, FileDescriptor databaseFile, int skipbytes, shared_ptr<NestedMaps> node)
{

    int value;
    lseek(databaseFile.FileDesc, block.startOffset + skipbytes, SEEK_SET);
    read(databaseFile.FileDesc, &value, INTSIZE);

    node->id = index;
    node->updated = 0;
    node->isLoaded = 1;
    node->data = value;
}

void prepare_long(int index, indexBlock block, FileDescriptor databaseFile, int skipbytes, shared_ptr<NestedMaps> node)
{

    long long value;
    lseek(databaseFile.FileDesc, block.startOffset + skipbytes, SEEK_SET);
    read(databaseFile.FileDesc, &value, LONGSIZE);

    node->id = index;
    node->updated = 0;
    node->isLoaded = 1;
    node->data = value;
}

void prepare_double(int index, indexBlock block, FileDescriptor databaseFile, int skipbytes, shared_ptr<NestedMaps> node)
{

    double value;
    lseek(databaseFile.FileDesc, block.startOffset + skipbytes, SEEK_SET);
    read(databaseFile.FileDesc, &value, DOUBLESIZE);

    node->id = index;
    node->updated = 0;
    node->isLoaded = 1;
    node->data = value;
}

void prepare_bool(int index, indexBlock block, FileDescriptor databaseFile, int skipbytes, shared_ptr<NestedMaps> node)
{

    bool value;
    lseek(databaseFile.FileDesc, block.startOffset + skipbytes, SEEK_SET);
    read(databaseFile.FileDesc, &value, BOOLSIZE);

    node->id = index;
    node->updated = 0;
    node->isLoaded = 1;
    node->data = value;
}
void prepare_string(int index, indexBlock block, FileDescriptor databaseFile, int skipbytes, shared_ptr<NestedMaps> node)
{

    int length;
    lseek(databaseFile.FileDesc, block.startOffset + skipbytes, SEEK_SET);
    read(databaseFile.FileDesc, &length, INTSIZE);

    string s;
    s.resize(length);

    for (int i = 0; i < length; i++)
    {
        lseek(databaseFile.FileDesc, block.startOffset + skipbytes + INTSIZE + i, SEEK_SET);
        read(databaseFile.FileDesc, &(s[i]), CHARSIZE);
    }

    node->id = index;
    node->updated = 0;
    node->isLoaded = 1;
    node->data = s;
}
