#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "include/ClassFile.h"
#include "include/ClassFileReader.h"


void printFile(std::istream & in) {
	while(in.eof())
	u1 by = in.get();
}

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
	std::cout << cf->magic << std::endl;
	auto utf8info = cf->constant_pool[cf->constant_pool[cf->this_class - 1]->info.class_info.name_index - 1]->info.utf8_info;
	std::cout << convertUtf8(utf8info.bytes, utf8info.length) << std::endl;

	std::cout << "hell" << std::endl;
    return 0;
}