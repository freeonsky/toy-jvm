#ifndef STACK_FRAME_H
#define STACK_FRAME_H

// stackFrame����Ļ�����Ϣ�� currentMethodName, currentClassInstance, �ֲ�������
//                            ������ջ��pc(���������)��ջ�����߶�
// currentMethodName: ����������ơ�����ֵ��������ֱ��ʹ��classfile�����ֵ
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
