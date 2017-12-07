#include "ClassFile.h"
#include <string>

class ClassPrinter
{
public:
	ClassPrinter();
	~ClassPrinter();
	void printClass(ClassFile &cf);
	std::string convertUtf8(u1* ch, u2 len);
	std::string getAccessFlag(u2 accessFlag);
	std::string getSuperClass(ClassFile &cf);
	std::string getClassName(ClassFile &cf);
};

