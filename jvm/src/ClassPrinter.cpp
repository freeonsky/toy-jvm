#include <cstdint>
#include <sstream>
#include <map>
#include <iostream>

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


/**
Flag Name 		Value 	Meaning
ACC_PUBLIC 		0x0001 	Marked or implicitly public in source.
ACC_FINAL 		0x0010 	Marked final in source.
ACC_SUPER 		0x0020 	Treat superclass methods specially when invoked by the invokespecial instruction.
ACC_INTERFACE 	0x0200 	Was an interface in source.
ACC_ABSTRACT 	0x0400 	Marked or implicitly abstract in source
*/
std::string ClassPrinter::getClassAccessFlag(u2 accessFlag)
{
	std::map<u2, std::string> hashMap = { 
		{ 0x0001 , "public " },
		{ 0x0010 , "final " },
		//{ 0x0020 , "super " },
		{ 0x0200 , "interface " },
		{ 0x0400 , "abstract class"}
	
	};
	std::string ss;
	for (auto item : hashMap) {
		if ((accessFlag & item.first) != 0) {
			ss += item.second;
		}
	}
	if ((accessFlag & ACC_INTERFACE) == 0 && (accessFlag & ACC_ABSTRACT) == 0) {
		ss += "class ";
	}
	return std::move(ss);
}

/*
ACC_PUBLIC 			0x0001 	Declared public; may be accessed from outside its package.
ACC_PRIVATE 		0x0002 	Declared private; accessible only within the defining class.
ACC_PROTECTED 		0x0004 	Declared protected; may be accessed within subclasses.
ACC_STATIC 			0x0008 	Declared static.
ACC_FINAL 			0x0010 	Declared final; may not be overridden.
ACC_SYNCHRONIZED 	0x0020 	Declared synchronized; invocation is wrapped in a monitor lock.
ACC_NATIVE 			0x0100 	Declared native; implemented in a language other than Java.
ACC_ABSTRACT 		0x0400 	Declared abstract; no implementation is provided.
ACC_STRICT 			0x0800 	Declared strictfp; floating-point mode is FP-strict
*/
std::string ClassPrinter::getMethodAccessFlag(u2 accessFlag)
{
	std::map<u2, std::string> hashMap = {
		{ 0x0001 , "public " },
		{ 0x0002 , "private " },
		{ 0x0004 , "protected " },
		{ 0x0008 , "static " },
		{ 0x0010 , "final " },
		{ 0x0020 , "synchronized " },
		{ 0x0100 , "native " }, 
		{ 0x0400 , "abstract " },
		{ 0x0800 , "strictfp " }

	};
	std::string ss;
	for (auto item : hashMap) {
		if ((accessFlag & item.first) != 0) {
			ss += item.second;
		}
	}

	return std::move(ss);
}

static std::string getUtf8String(ClassFile & cf, u2 nameIndex) {
	auto utf8Info = cf.constant_pool[nameIndex - 1]->info.utf8_info;
	auto name = ClassPrinter::convertUtf8(utf8Info.bytes, utf8Info.length);
	return std::move(name);
}

std::string ClassPrinter::getMethodName(ClassFile & cf, u2 nameIndex)
{
	return std::move(getUtf8String(cf, nameIndex));
}

/*
B 	byte 	signed byte
C 	char 	Unicode character
D 	double 	double-precision floating-point value
F 	float 	single-precision floating-point value
I 	int 	integer
J 	long 	long integer
L<classname>; 	reference 	an instance of class <classname>
S 	short 	signed short
Z 	boolean 	true or false
[ 	reference 	one array dimension
*/
static std::string getDescriptorType(std::string str, unsigned int& i) {
	std::map<char, std::string> hMap = {
		{ 'B', "byte" },
		{ 'C', "char" },
		{ 'D', "double" },
		{ 'F', "float" },
		{ 'I', "int" },
		{ 'J', "long" },
		{ 'S', "short" },
		{ 'Z', "boolean" },
		{ 'V', "void" }
	};

	std::string mp;
	while (i < str.length()) {
		// 从第二个参数开始添加逗号
		if (mp.size() >0) {
			mp += ", ";
		}
		auto search = hMap.find(str[i]);
		if (search != hMap.end()) {
			mp += search->second;
			i++;
		}
		else {
			if (str[i] == 'L') {
				auto referenceSeprator = str.find(";", i);
				auto className = str.substr(i + 1, referenceSeprator - i - 1);
				std::string::size_type pos = className.find("/");
				while(pos != std::string::npos) {
					className.replace(pos, 1, ".");
					pos = className.find("/");
				}
				mp += className;
				i = (unsigned int)(referenceSeprator + 1);
			}
			else if (str[i] == '[') {
				unsigned int arrIndex = i;
				while (str[arrIndex] == '[') {
					arrIndex++;
				}
				std::string arrQuate = std::string(arrIndex - i, '[') + std::string(arrIndex - i, ']');
				std::string type = getDescriptorType(str, arrIndex);
				i = arrIndex;
				type += arrQuate;
				mp += type;
			}
			else {
				i++;
			}
		}
	}
	return mp;
}

std::string ClassPrinter::getMethodReturnName(ClassFile & cf, u2 index)
{
	std::string descriptor = getUtf8String(cf, index);
	auto right = descriptor.find(")");
	std::string rtype = descriptor.substr(right+1);
	unsigned int i = 0;
	return getDescriptorType(rtype, i);
}



std::string ClassPrinter::getMethodParameter(ClassFile & cf, u2 index)
{
	std::string descriptor = getUtf8String(cf, index);
	auto right = descriptor.find(")");
	
	// 参数为空
	if (right == 1) {
		return "()";
	}

	std::string para = descriptor.substr(1, right - 1);
	unsigned int i = 0;
	return std::string("(") + getDescriptorType(para, i) + ")";
}

std::string ClassPrinter::getMethodSign(ClassFile & cf, method_info & mi)
{
	std::string ms;
	ms += getMethodAccessFlag(mi.access_flags);
	ms += getMethodReturnName(cf, mi.descriptor_index) + " ";
	ms += getMethodName(cf, mi.name_index);
	ms += getMethodParameter(cf, mi.descriptor_index);
	return std::move(ms);
}

std::string ClassPrinter::getMethodCode(ClassFile & cf, method_info & mi)
{
	std::stringstream st;
	for (int i = 0; i < mi.attributes_count; i++) {
		std::string attrName = getUtf8String(cf, mi.attributes[i]->attribute_name_index);
		if ("Code" == attrName) {
			auto codeInfo = mi.attributes[i]->info.code_info;
			
			st << "max_locals:"
			   << codeInfo.max_locals << "\n"
				<< "max_stack:" << codeInfo.max_stack << "\n"
				<< "code is:" << "\n";
			u1 *code = codeInfo.code;
			for (unsigned int j = 0; j < mi.attributes[i]->info.code_info.code_length; j++) {
				st << OP_CODE_ARRAY[code[j]] << "\n";
			}
		}
	}
	return st.str();
}

/*
Flag Name 		Value 	Interpretation
ACC_PUBLIC 		0x0001 	Declared public; may be accessed from outside its package.
ACC_PRIVATE 	0x0002 	Declared private; usable only within the defining class.
ACC_PROTECTED 	0x0004 	Declared protected; may be accessed within subclasses.
ACC_STATIC 		0x0008 	Declared static.
ACC_FINAL 		0x0010 	Declared final; no further assignment after initialization.
ACC_VOLATILE 	0x0040 	Declared volatile; cannot be cached.
ACC_TRANSIENT 	0x0080 	Declared transient; not written or read by a persistent object manager.
*/
std::string ClassPrinter::getFieldAccessFlag(u2 accessFlag)
{
	std::map<u2, std::string> hashMap = {
	{ 0x0001 , "public " },
	{ 0x0002 , "private " },
	{ 0x0004 , "protected " },
	{ 0x0008 , "static " },
	{ 0x0010 , "final " },
	{ 0x0040 , "volatile " },
	{ 0x0080 , "transient " }

	};
	std::string ss;
	for (auto item : hashMap) {
		if ((accessFlag & item.first) != 0) {
			ss += item.second;
		}
	}

	return std::move(ss);
}

std::string ClassPrinter::getFieldDescriptor(ClassFile & cf, field_info & fInfo)
{
	return std::move(getUtf8String(cf, fInfo.descriptor_index));
}

std::string ClassPrinter::getFieldName(ClassFile & cf, u2 nameIndex)
{
	return std::move(getUtf8String(cf, nameIndex));
}




std::string ClassPrinter::getSuperClass(ClassFile & cf)
{
	if (cf.super_class != 0) {
		auto superClassInfo = cf.constant_pool[cf.super_class - 1]->info.class_info;
		auto utf8Info = cf.constant_pool[superClassInfo.name_index - 1]->info.utf8_info;
		auto name = convertUtf8(utf8Info.bytes, utf8Info.length);
		return std::move(name);
	}
	else {
		return std::string();
	}	
}

std::string ClassPrinter::getClassName(ClassFile & cf)
{
	auto thisClassInfo = cf.constant_pool[cf.this_class - 1]->info.class_info;
	auto utf8Info = cf.constant_pool[thisClassInfo.name_index - 1]->info.utf8_info;
	std::string thisClassName = convertUtf8(utf8Info.bytes, utf8Info.length);
	return std::move(thisClassName);
}



/*
todo:
* get this class name
* get super class name
* get method
* print code
* get fields
* get interface
*/
void ClassPrinter::printClass(ClassFile &cf) {
	auto thisClassName = getClassName(cf);
	auto superClassName = getSuperClass(cf);
	auto accessFlag = getClassAccessFlag(cf.access_flags);
	
	std::string superStri;
	if (superClassName != "java/lang/Object") {
		superStri += " extend " + superClassName;
	}

	std::string methods;
	for (int i = 0; i < cf.methods_count; i++) {
		auto mInfo = cf.methods[i];
		methods += getMethodSign(cf, *mInfo) + "\n{\n";
		methods += getMethodCode(cf, *mInfo) + "\n}\n";
	}

	std::string fields;
	for (int i = 0; i < cf.fields_count; i++) {
		field_info* fInfo = cf.fields[i];
		fields += getFieldAccessFlag(fInfo->access_flags);
		fields += getFieldDescriptor(cf, *fInfo) + " ";
		fields += getFieldName(cf, fInfo->name_index);
		fields += "\n";
	}

	std::cout << accessFlag << thisClassName << superStri << " {" << std::endl
		<< methods
		<< std::endl
		<< fields
		<< std::endl
		<< "}"
		<< std::endl;
}