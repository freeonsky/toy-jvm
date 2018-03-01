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

// 在heap创建一个对象，返回此对象的句柄（在heap中的索引）
// jvm规范基本类型（byte,bool,char,short,int,float 都占用1个slot；double,long占用2个slot）,引用类型占用1个slot.
// 简化开发，每种类型都占用1个slot;
// 对象在heap中的布局： {size, ClassFilePointer, isReference, fieldCount, fields}
// 这样占用的总数量= size(1) + ClassFilePointer(1) + isReference(1) + fieldCount(1) + fields
unsigned int Heap::newFunc(ClassFile & cf)
{
	unsigned int start = usage;
	/*
	void* p = this->heap + usage;
	*(unsigned int *)(p) = 4 + cf.fields_count;
	//*(ClassFile*)(p + 1) = &cf;
	*/
	usage = 4 + cf.fields_count;
	return start;
}

MemStruct Heap::getMemStruct(unsigned int index)
{
	MemStruct ms;
	/*
	void* p = this->heap;
	ms.size = *(unsigned int *)(p + index);
	ms.classFilePointer = (ClassFile*)(p + index + 1);
	ms.isReference = *(referenced*)(p + index + 2);
	ms.fieldCount = *(unsigned int*)(p + index + 3);
	ms.fields = p + index + 4;
	*/
	return ms;
}

Heap::~Heap()
{
	delete this->heap;
}

