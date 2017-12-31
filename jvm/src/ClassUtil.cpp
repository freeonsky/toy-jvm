#include "../include/ClassUtil.h"



std::string ClassUtil::convertUtf8ToString(u1* ch, u2 len) {
	char * by = new char[len + 1];
	for (int i = 0; i < len; i++) {
		by[i] = ch[i];
	}
	by[len] = '\0';
	std::string str(by);
	return std::move(str);
}


int8_t ClassUtil::getByteField(std::string fieldName)
{
	return int8_t();
}

uint16_t ClassUtil::getCharField(std::string fieldName)
{
	return uint16_t();
}

int16_t ClassUtil::getShortField(std::string fieldName)
{
	return int16_t();
}

int32_t ClassUtil::getIntField(std::string fieldName)
{
	return int32_t();
}

int64_t ClassUtil::getLongField(std::string fieldName)
{
	return int64_t();
}

float ClassUtil::getFloatField(std::string fieldName)
{
	return 0.0f;
}

double ClassUtil::getDoubleField(std::string fieldName)
{
	return 0.0;
}

bool ClassUtil::getBoolField(std::string fieldName)
{
	return false;
}
