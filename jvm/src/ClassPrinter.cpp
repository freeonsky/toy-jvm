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

std::string ClassPrinter::getMethodReturnName(ClassFile & cf, u2 index)
{
	std::string descriptor = getUtf8String(cf, index);
	auto right = descriptor.find(")");
	auto rtype = descriptor.substr(right+1);
	return std::move(rtype);
}

std::string ClassPrinter::getMethodSign(ClassFile & cf, method_info & mi)
{
	std::string ms;
	ms += getMethodAccessFlag(mi.access_flags);
	ms += getMethodReturnName(cf, mi.descriptor_index);
	ms += getMethodName(cf, mi.name_index);
	return std::move(ms);
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
1. get this class name
2. get super class name
3. get method
4. get interface
5. get fields
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
		methods += getMethodSign(cf, *mInfo) + "\n";
	}

	std::cout << accessFlag << thisClassName << superStri << " {"
		<< methods

		<< std::endl << "}"
		<< std::endl;
}