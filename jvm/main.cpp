#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "string.h"

#include "include/ClassFile.h"
#include "include/ClassFileReader.h"
#include "include/ClassPrinter.h"


int main(int argc, char** argv)
{
	// 实现javap功能
	// 用法： jtvm print [path]
	// 例子： jtvm print /home/zft/projects/Test.class
	if (argc == 3 && strcmp("print", argv[1])) {
		std::string path("/home/zft/projects/Test.class");
		std::filebuf fin;
		if (!fin.open(path, std::ios::in)) {
			std::cout << "fail to pen file" << std::endl;
			exit(1);
		}
		std::istream is(&fin);

		ClassFileReader reader;
		ClassFile *cf = reader.readClassFile(is);

		ClassPrinter cp;
		cp.printClass(*cf);
	}

    return 0;
}