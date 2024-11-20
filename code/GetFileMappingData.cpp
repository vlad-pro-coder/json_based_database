#include "../headers/GetFileMappingData.hpp"

using namespace std;

FileDescriptor getFileDescriptors(const char *filename)
{
    int filedesc = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);

    if (filedesc < 0)
    {
        cout << "error reading database files";
        exit(1);
    }

    FileDescriptor fileDescriptor;

    off_t fileLength = lseek(filedesc, 0, SEEK_END);
    fileDescriptor.FileDesc = filedesc;
    fileDescriptor.FileLength = fileLength;

    return fileDescriptor;
}

shared_ptr<AllocDescriptor> getFileAllocDescriptor(FileDescriptor fileDescriptor)
{

    /// allocating the allocDescriptor
    shared_ptr<AllocDescriptor> allocDescriptor = make_shared<AllocDescriptor>();

    /// get the number of free intervals
    int length;
    lseek(fileDescriptor.FileDesc, 0, SEEK_SET);
    ssize_t bytes_read = read(fileDescriptor.FileDesc, &length, INTSIZE);

    if (bytes_read == -1)
    {
        cout<<fileDescriptor.FileDesc<<'\n';
        cout << "error while trying to read file allocator"<<'\n';
        exit(1);
    }

    lseek(fileDescriptor.FileDesc, INTSIZE, SEEK_SET);
    read(fileDescriptor.FileDesc, &allocDescriptor->limit, INTSIZE);
    
    shared_ptr<set<Intervals>> gotIntervals = make_shared<set<Intervals>>();

    for (int i = 0; i < length; i++)
    {
        Intervals interval;

        lseek(fileDescriptor.FileDesc, 2*INTSIZE + (2*i) * INTSIZE, SEEK_SET);
        read(fileDescriptor.FileDesc, &interval.start, INTSIZE);

        lseek(fileDescriptor.FileDesc, 2*INTSIZE + (2*i + 1) * INTSIZE, SEEK_SET);
        read(fileDescriptor.FileDesc, &interval.end, INTSIZE);

        gotIntervals->insert(interval);
    }

    allocDescriptor->freeIntervals = gotIntervals;

    return allocDescriptor;
}

shared_ptr<indexBlocksContainer> ReadIndexFile(FileDescriptor fileDescriptor)
{
    shared_ptr<indexBlocksContainer> blocksContainer = make_shared<indexBlocksContainer>();

    lseek(fileDescriptor.FileDesc, 0, SEEK_SET);
    ssize_t bytes_read = read(fileDescriptor.FileDesc, &blocksContainer->length, INTSIZE);

    if (bytes_read == -1)
    {
        cout << "error while trying to read file allocar";
        exit(1);
    }

    blocksContainer->indexBlocks = make_unique<unordered_map<int, indexBlock>>();

    for (int i = 0; i < blocksContainer->length; i++)
    {
        indexBlock indexblock;
        int id;

        lseek(fileDescriptor.FileDesc, INTSIZE + (3*i) * INTSIZE, SEEK_SET);
        read(fileDescriptor.FileDesc, &id, INTSIZE);

        lseek(fileDescriptor.FileDesc, INTSIZE + (3*i + 1) * INTSIZE, SEEK_SET);
        read(fileDescriptor.FileDesc, &indexblock.startOffset, INTSIZE);

        lseek(fileDescriptor.FileDesc, INTSIZE + (3*i + 2) * INTSIZE, SEEK_SET);
        read(fileDescriptor.FileDesc, &indexblock.LengthBlock, INTSIZE);

        (*blocksContainer->indexBlocks)[id] = indexblock;
    }

    return blocksContainer;
}