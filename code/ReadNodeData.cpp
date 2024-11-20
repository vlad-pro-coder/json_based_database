#include "../headers/ReadNodeData.hpp"

using namespace std;

// data blocks
// 1byte -> type 1->nestedmap,2->int,3->long long,4->double,5->bool,6->string

/*case1: unordered_map
    key string: 2bytes(short) length
                1byte every consecutive char for read length
    children: 4bytes(int) length
                4bytes every consecutive int for read length
*/

/*case2: int
    key string: 2bytes(short) length
                1byte every consecutive char for read length
    value: 4bytes
*/

/*case3: long long
    key string: 2bytes(short) length
                1byte every consecutive char for read length
    value: 8bytes
*/

/*case4: double
    key string: 2bytes(short) length
                1byte every consecutive char for read length
    value: 8bytes
*/

/*case5: bool
    key string: 2bytes(short) length
                1byte every consecutive char for read length
    value: 1byte
*/

/*case6: string
    key string: 2bytes(short) length
                1byte every consecutive char for read length
    value string:4bytes(int) length
                1byte everry consecutive char for read length
*/

void ReadNodeData(int index, shared_ptr<indexBlocksContainer> indexBlocksCont, FileDescriptor databaseFile, shared_ptr<NestedMaps> node)
{
    
    char type;
    indexBlock block = (*indexBlocksCont->indexBlocks)[index];
    lseek(databaseFile.FileDesc, block.startOffset, SEEK_SET);
    read(databaseFile.FileDesc, &type, CHARSIZE);

    short lengthkey;
    lseek(databaseFile.FileDesc, block.startOffset + CHARSIZE, SEEK_SET);
    read(databaseFile.FileDesc, &lengthkey, SHORTSIZE);

    switch (type)
    {
    case (1):
        prepare_map(index, block, indexBlocksCont,databaseFile, CHARSIZE + SHORTSIZE + lengthkey * CHARSIZE, node);
        break;
    case (2):
        prepare_int(index, block,databaseFile, CHARSIZE + SHORTSIZE + lengthkey * CHARSIZE, node);
        break;
    case (3):
        prepare_long(index, block,databaseFile, CHARSIZE + SHORTSIZE + lengthkey * CHARSIZE, node);
        break;
    case (4):
        prepare_double(index, block,databaseFile, CHARSIZE + SHORTSIZE + lengthkey * CHARSIZE, node);
        break;
    case (5):
        prepare_bool(index, block,databaseFile, CHARSIZE + SHORTSIZE + lengthkey * CHARSIZE, node);
        break;
    case (6):
        prepare_string(index, block,databaseFile, CHARSIZE + SHORTSIZE + lengthkey * CHARSIZE, node);
        break;
    }
}