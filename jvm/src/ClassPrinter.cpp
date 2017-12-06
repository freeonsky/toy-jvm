#include "../include/ClassPrinter.h"



ClassPrinter::ClassPrinter()
{
}


ClassPrinter::~ClassPrinter()
{
}

std::string ClassPrinter::convertUtf8(u1* ch, u2 len) {
	char * by = new char[len + 1];
	for (int i = 0; i < len; i++) {
		by[i] = ch[i];
	}
	by[len] = '\0';
	std::string str(by);
	return std::move(str);
}

void ClassPrinter::printClass(ClassFile &cf) {
	auto thisClassInfo = cf.constant_pool[cf.this_class - 1]->info.class_info;
	auto utf8Info = cf.constant_pool[thisClassInfo.name_index - 1]->info.utf8_info;
	std::string thisClassName = convertUtf8(utf8Info.bytes, utf8Info.length);

}