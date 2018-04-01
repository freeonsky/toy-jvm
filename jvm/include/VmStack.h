#ifndef VM_STACK_H
#define VM_STACK_H

#include <stack>
#include "StackFrame.h"

class VmStack {
private:
	std::stack<StackFrame> vmStack;
public:
	VmStack();
	~VmStack();
    StackFrame& top() {
        return vmStack.top();
    };
    void push(StackFrame& frame){
        vmStack.push(frame);
    };
    void pop(){
        vmStack.pop();
    };
};


#endif