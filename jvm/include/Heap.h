#ifndef HEAP_H
#define HEAP_H

#include "ClassFile.h"

union referenced {
	unsigned int length; // Ŀ������isReferenceռ��1��slot
	bool flag;
};

// Heap new ��������Ľ�� 
// size ��С��2���ֱ��ǣ�size,��ָ��ClassFile class�����ָ�롣
// {size, ClassFilePointer, isReference, fieldCount, fields}
struct MemStruct {
	unsigned int size;
	ClassFile* classFilePointer;
	referenced isReference;
	unsigned int fieldCount;
	void * fields;
};

// �ѣ�����new�ؼ��ִ����Ķ��󶼴Ӷ��а�˳�����.
// Heap ��һ�����������ڴ��� singleton(unsigned int mx, unsigned int ms) ʱָ������ڴ棬��ʼ�ڴ�
// newFunc ������Ӧnew�ؼ��֣�������Heap�����ڴ棬������ڴ��� MemSize ����ʾ
class Heap
{
private:
	Heap(unsigned int mx, unsigned int ms);
	Heap(const Heap &) = default;
	Heap& operator=(const Heap&) = default;
	unsigned int mx;
	unsigned int ms;
	// Ĭ��ֵ��0����ʾHeap�е��ڴ滹û�б�ʹ��,ÿ�ε��� newFunc��usage��ֵ���ӷ����ڴ�length��
	unsigned int usage;
	void * heap;

public:
	// Heap ��һ�����������ڴ��� singleton(unsigned int mx, unsigned int ms) ʱָ������ڴ棬��ʼ�ڴ�
	static Heap& singleton(unsigned int mx, unsigned int ms);

	// ��heap����һ�����󣬷��ش˶���ľ������heap�е�������
	// jvm�淶�������ͣ�byte,bool,char,short,int,float ��ռ��1��slot��double,longռ��2��slot��,��������ռ��1��slot.
	// �򻯿�����ÿ�����Ͷ�ռ��1��slot;
	// ������heap�еĲ��֣� {size, ClassFilePointer, isReference, fieldCount, fields}
	// ����ռ�õ�������= size(1) + ClassFilePointer(1) + isReference(1) + fieldCount(1) + fields
	unsigned int newFunc(ClassFile &cf);
	
	// ���ݾ����ȡheap�еĽṹ
	MemStruct getMemStruct(unsigned int index);
	~Heap();
};

#endif