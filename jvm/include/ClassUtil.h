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
	// todo ����������Ƚϸ��ӣ���ʱ��c++ �����������ʹ��棬��64λ�����£�float��64λ
	static float getFloatField(std::string fieldName);
	static double getDoubleField(std::string fieldName);
	static bool getBoolField(std::string fieldName);
};

#endif // !CLASS_UTIL_H
