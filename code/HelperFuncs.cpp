#include "../headers/HelperFuncs.hpp"

using namespace std;

string getKey(FileDescriptor databaseFile, indexBlock block)
{
    short lengthkey;
    lseek(databaseFile.FileDesc, block.startOffset + CHARSIZE, SEEK_SET);
    read(databaseFile.FileDesc, &lengthkey, SHORTSIZE);

    string retString;
    retString.resize(lengthkey);

    for (int i = 0; i < lengthkey; i++)
    {
        lseek(databaseFile.FileDesc, block.startOffset + CHARSIZE + SHORTSIZE + i * CHARSIZE, SEEK_SET);
        read(databaseFile.FileDesc, &(retString[i]), CHARSIZE);
    }
    return retString;
}