#include "ClassFile.h"
#include <string>
// ��ʵ���������ڴ��еĳ���
class Instance
{
public:
	// ��ȡʵ���Ķ���
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
	// todo ����������Ƚϸ��ӣ���ʱ��c++ �����������ʹ��棬��64λ�����£�float��64λ
	static float getFloatField(std::string fieldName);
	static double getDoubleField(std::string fieldName);
	static bool getBoolField(std::string fieldName);
};

