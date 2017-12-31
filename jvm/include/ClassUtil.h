#ifndef CLASS_UTIL_H
#define CLASS_UTIL_H

#include "ClassFile.h"
#include <string>

class ClassUtil
{
public:
	ClassUtil() = default;
	~ClassUtil() = default;
	static std::string convertUtf8ToString(u1* ch, u2 len);
	static int8_t getByteField(std::string fieldName);
	static uint16_t getCharField(std::string fieldName);
	static int16_t getShortField(std::string fieldName);
	static int32_t getIntField(std::string fieldName);
	static int64_t getLongField(std::string fieldName);
	// todo 浮点数计算比较复杂，暂时用c++ 基本数据类型代替，在64位环境下，float是64位
	static float getFloatField(std::string fieldName);
	static double getDoubleField(std::string fieldName);
	static bool getBoolField(std::string fieldName);
};

#endif // !CLASS_UTIL_H
