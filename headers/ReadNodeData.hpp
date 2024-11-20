#ifndef READDATA
#define READDATA

#include <memory>
#include "./delcarations/Structs.hpp"
#include <fcntl.h>
#include <unistd.h>
#include "./delcarations/Defines.hpp"
#include "./PrepareFunctions.hpp"
#include <iostream>

void ReadNodeData(int index,std::shared_ptr<indexBlocksContainer>indexBlocks,FileDescriptor databaseFile,std::shared_ptr<NestedMaps> node);

#endif