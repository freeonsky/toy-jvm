#include "../include/Heap.h"



Heap::Heap(unsigned int mx, unsigned int ms):mx(mx),ms(ms), usage(0)
{
	this->heap = operator new(ms);
}


Heap& Heap::singleton(unsigned int mx, unsigned int ms)
{
	static Heap instance(mx, ms);
	return instance;
}

// ��heap����һ�����󣬷��ش˶���ľ������heap�е�������
// jvm�淶�������ͣ�byte,bool,char,short,int,float ��ռ��1��slot��double,longռ��2��slot��,��������ռ��1��slot.
// �򻯿�����ÿ�����Ͷ�ռ��1��slot;
// ������heap�еĲ��֣� {size, ClassFilePointer, isReference, fieldCount, fields}
// ����ռ�õ�������= size(1) + ClassFilePointer(1) + isReference(1) + fieldCount(1) + fields
unsigned int Heap::newFunc(ClassFile & cf)
{
	unsigned int start = usage;

	void* p = this->heap + usage;
	*(unsigned int *)(p) = 4 + cf.fields_count;
	//*(ClassFile*)(p + 1) = &cf;

	usage = 4 + cf.fields_count;
	return start;
}

MemStruct Heap::getMemStruct(unsigned int index)
{
	MemStruct ms;
	void* p = this->heap;
	ms.size = *(unsigned int *)(p + index);
	ms.classFilePointer = (ClassFile*)(p + index + 1);
	ms.isReference = *(referenced*)(p + index + 2);
	ms.fieldCount = *(unsigned int*)(p + index + 3);
	ms.fields = p + index + 4;
	return ms;
}

Heap::~Heap()
{
	delete this->heap;
}

