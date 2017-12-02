#ifndef CLASS_FILE_READER
#define CLASS_FILE_READER
#include <iostream>
#include "ClassFile.h"

class ClassFileReader
{
public:
	ClassFileReader();
	~ClassFileReader();
	ClassFile* readClassFile(std::istream &);
};

#endif // !CLASS_FILE_READER