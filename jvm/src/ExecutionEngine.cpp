#include "../include/ExecutionEngine.h"
#include "../include/VmStack.h"

ExecutionEngine::ExecutionEngine(std::string &classpath):classpath(classpath){

}

int ExecutionEngine::start(std::string &startClassName){
    // 加载所有classpath下的jar，class文件
    loadLib(this->classpath);

    // 初始化栈
    VmStack vm;
    
    return 0;
}

void loadLib(std::string &classpath){

}