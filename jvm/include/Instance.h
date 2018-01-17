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


