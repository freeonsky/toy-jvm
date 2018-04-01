#ifndef EXECUTION_ENGINE_H
#define EXECUTION_ENGINE_H
#include <string>

class ExecutionEngine
{
private:
    std::string classpath;   

public:
	ExecutionEngine(std::string &);
	~ExecutionEngine();
	int start(std::string &);
};

#endif // !EXECUTION_ENGINE_H