#include "../include/Heap.h"



Heap::Heap(unsigned int mx, unsigned int ms):mx(mx),ms(ms), usage(0)
{
	this->heap = new int[ms];
}


Heap& Heap::singleton(unsigned int mx, unsigned int ms)
{
	static Heap instance(mx, ms);
	return instance;
}

MemSize Heap::newFunc(ClassFile & cf)
{

	return MemSize();
}

Heap::~Heap()
{
	delete[] this->heap;
}
