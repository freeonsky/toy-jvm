#ifndef STACK_FRAME_H
#define STACK_FRAME_H

// stackFrame必须的基本信息： currentMethodName, currentClassInstance, 局部变量表，
//                            操作数栈，pc(程序计数器)，栈的最大高度
// currentMethodName: 必须包含名称、返回值、参数，直接使用classfile定义的值
class StackFrame {
private:
	int pc;
	int *locals;
	int *stack;
public:
	StackFrame(int maxLocals, int stackSize) {
		pc = 0;
		locals = new int[maxLocals];
		stack = new int[stackSize];
	}
	~StackFrame() {
		delete locals;
		delete stack;
	}
};


#endif
