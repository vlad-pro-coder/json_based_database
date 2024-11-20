#ifndef HELPERFUNCS
#define HELPERFUNCS

#include <fcntl.h>
#include <unistd.h>
#include "./delcarations/Structs.hpp"
#include <string>
#include <memory>
#include "./delcarations/Defines.hpp"

std::string getKey(FileDescriptor databaseFile,indexBlock block);

#endif