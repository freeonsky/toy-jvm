#ifndef HEAP_H
#define HEAP_H

#include "ClassFile.h"

union referenced {
	unsigned int length; // 目的是让isReference占用1个slot
	bool flag;
};

// Heap new 方法分配的结果 
// size 最小是2，分别是：size,和指向ClassFile class定义的指针。
// {size, ClassFilePointer, isReference, fieldCount, fields}
struct MemStruct {
	unsigned int size;
	ClassFile* classFilePointer;
	referenced isReference;
	unsigned int fieldCount;
	void * fields;
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
	// 默认值是0，表示Heap中的内存还没有被使用,每次调用 newFunc，usage的值增加分配内存length；
	unsigned int usage;
	void * heap;

public:
	// Heap 是一个单例对象，在创建 singleton(unsigned int mx, unsigned int ms) 时指定最大内存，起始内存
	static Heap& singleton(unsigned int mx, unsigned int ms);

	// 在heap创建一个对象，返回此对象的句柄（在heap中的索引）
	// jvm规范基本类型（byte,bool,char,short,int,float 都占用1个slot；double,long占用2个slot）,引用类型占用1个slot.
	// 简化开发，每种类型都占用1个slot;
	// 对象在heap中的布局： {size, ClassFilePointer, isReference, fieldCount, fields}
	// 这样占用的总数量= size(1) + ClassFilePointer(1) + isReference(1) + fieldCount(1) + fields
	unsigned int newFunc(ClassFile &cf);
	
	// 根据句柄获取heap中的结构
	MemStruct getMemStruct(unsigned int index);
	~Heap();
};

#endif