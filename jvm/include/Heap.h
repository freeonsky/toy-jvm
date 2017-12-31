#ifndef HEAP_H
#define HEAP_H

#include "ClassFile.h"

// Heap new 方法返回的结果 [start,start+size]
// start 表示对象在Heap中的起始index, start+size表示对象在Heap中的结束index
// size 最小是3，分别是：start,size,和指向ClassFile class定义的指针。
//      超过3的部分是class的field存放地址
struct MemSize {
	int start;
	int size;
};

// 堆，所有new关键字创建的对象都从堆中按顺序分配.
// Heap 是一个单例对象，在创建 singleton(unsigned int mx, unsigned int ms) 时指定最大内存，起始内存
// newFunc 函数对应new关键字，用来从Heap分配内存，分配的内存用 MemSize 来表示
class Heap
{
private:
	Heap(unsigned int mx, unsigned int ms);
	Heap(const Heap &) = default;
	Heap& operator=(const Heap&) = default;
	unsigned int mx;
	unsigned int ms;
	// 默认值是0，表示Heap中的内存还没有被使用
	unsigned int usage;
	int * heap;

public:
	// Heap 是一个单例对象，在创建 singleton(unsigned int mx, unsigned int ms) 时指定最大内存，起始内存
	static Heap& singleton(unsigned int mx, unsigned int ms);
	MemSize newFunc(ClassFile &cf);
	~Heap();
};

#endif