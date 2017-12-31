#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "include/ClassFile.h"
#include "include/ClassFileReader.h"
#include "include/ClassPrinter.h"


int main()
{
	std::string path("/home/zft/projects/Test.class");
	std::filebuf fin;
	if (!fin.open(path, std::ios::in)) {
		std::cout << "fail to pen file" << std::endl;
	}
	std::istream is(&fin);

	ClassFileReader reader;
	ClassFile *cf = reader.readClassFile(is);

	ClassPrinter cp;
	cp.printClass(*cf);
    return 0;
}