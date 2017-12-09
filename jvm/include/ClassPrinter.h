#include "ClassFile.h"
#include <string>

class ClassPrinter
{
public:
	ClassPrinter();
	~ClassPrinter();
	void printClass(ClassFile &cf);
	static std::string convertUtf8(u1* ch, u2 len);
	std::string getClassAccessFlag(u2 accessFlag);
	std::string getSuperClass(ClassFile &cf);
	std::string getClassName(ClassFile &cf);
	std::string getMethodAccessFlag(u2 accessFlag);
	std::string getMethodName(ClassFile &cf, u2 nameIndex);
	std::string getMethodReturnName(ClassFile &cf, u2 nameIndex);
	std::string getMethodParameter(ClassFile &cf, u2 nameIndex);
	std::string getMethodSign(ClassFile &cf, method_info &mi);
};

