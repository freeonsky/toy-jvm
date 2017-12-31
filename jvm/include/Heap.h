#ifndef HEAP_H
#define HEAP_H

#include "ClassFile.h"

// Heap new �������صĽ�� [start,start+size]
// start ��ʾ������Heap�е���ʼindex, start+size��ʾ������Heap�еĽ���index
// size ��С��3���ֱ��ǣ�start,size,��ָ��ClassFile class�����ָ�롣
//      ����3�Ĳ�����class��field��ŵ�ַ
struct MemSize {
	int start;
	int size;
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
	// Ĭ��ֵ��0����ʾHeap�е��ڴ滹û�б�ʹ��
	unsigned int usage;
	int * heap;

public:
	// Heap ��һ�����������ڴ��� singleton(unsigned int mx, unsigned int ms) ʱָ������ڴ棬��ʼ�ڴ�
	static Heap& singleton(unsigned int mx, unsigned int ms);
	MemSize newFunc(ClassFile &cf);
	~Heap();
};

#endif