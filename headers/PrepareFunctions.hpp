#ifndef PREPAREFUNCS
#define PREPAREFUNCS

#include <string>
#include <memory>
#include <fcntl.h>
#include <unistd.h>
#include "./delcarations/Structs.hpp"
#include "./HelperFuncs.hpp"
#include "./delcarations/Defines.hpp"
#include <iostream>

void prepare_map(int index,indexBlock block,std::shared_ptr<indexBlocksContainer>indexBlocks,FileDescriptor databaseFile,int skipbytes,std::shared_ptr<NestedMaps> node);
void prepare_int(int index,indexBlock block,FileDescriptor databaseFile,int skipbytes,std::shared_ptr<NestedMaps> node);
void prepare_long(int index,indexBlock block,FileDescriptor databaseFile,int skipbytes,std::shared_ptr<NestedMaps> node);
void prepare_double(int index,indexBlock block,FileDescriptor databaseFile,int skipbytes,std::shared_ptr<NestedMaps> node);
void prepare_bool(int index,indexBlock block,FileDescriptor databaseFile,int skipbytes,std::shared_ptr<NestedMaps> node);
void prepare_string(int index,indexBlock block,FileDescriptor databaseFile,int skipbytes,std::shared_ptr<NestedMaps> node);

#endif