TARGET = json_db.out
SRCS = $(shell find . -name "*.cpp")

EXCLUDE_FILE = ./defaultFileDeclarations.cpp
SRCS := $(filter-out $(EXCLUDE_FILE), $(SRCS))

File1 = AllocTableFile
File2 = DBfile
File3 = indexes

all: $(TARGET)

$(TARGET): $(SRCS)
	g++ -std=c++17 -g -o $(TARGET) $(SRCS)
resetfiles:
	g++ -std=c++17 $(EXCLUDE_FILE)
	rm -f $(File1) $(File2) $(File3)
	./a.out