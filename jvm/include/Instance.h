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


