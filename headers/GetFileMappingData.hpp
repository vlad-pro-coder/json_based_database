#ifndef MAPPINGDATA
#define MAPPINGDATA

#include <iostream>
#include <memory.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include "./delcarations/Structs.hpp"
#include "./delcarations/Defines.hpp"

FileDescriptor getFileDescriptors(const char* filename);
std::shared_ptr<AllocDescriptor> getFileAllocDescriptor(FileDescriptor fileDescriptor);
std::shared_ptr<indexBlocksContainer> ReadIndexFile(FileDescriptor fileDescriptor);

#endif