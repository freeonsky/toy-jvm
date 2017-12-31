#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "include/ClassFile.h"
#include "include/ClassFileReader.h"
#include "include/ClassPrinter.h"

/*
void printFile(std::istream & in) {
	while(in.eof())
	u1 by = in.get();
}
*/

std::string convertUtf8(u1* ch, u2 len) {
	char * by = new char[len+1];
	for (int i = 0; i < len; i++) {
		by[i] = ch[i];
	}
	by[len] = '\0';
	std::string str(by);
	return std::move(str);
}

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