#include "ClassFile.h"
#include <string>
// 类实例化后在内存中的抽象
class Instance
{
public:
	// 获取实例的定义
	virtual ClassFile* getClassFile();

	Instance();
	~Instance();
};

class InstanceUtil
{
public:
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

