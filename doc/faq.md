# 为什么选择vs写跨平台程序
* 方便调试
* 强大的智能提示，快速coding

# 如何写一个jvm
## 类加载子系统
* 定义class 文件格式中的各种数据结构，参考jvm specification
* 读取class 文件到内存
* 写一个类似javap的class文件解析器，能够正常解析class文件，用来验证类加载系统

## 解释执行子系统
* 写一个解释器，从main方法开始解释执行

## runtime 
* io 
* net
* thread

# 为什么这种顺序
1. class文件格式（用struct表示）是由jvm specification 定义好的，直接读取class文件，往struct填值即可，这是最简单的一步。
2. 将class文件读取到内存后，进行基本的解析并展示其结构、内容（class 名称、方法名称、方法参数、返回值等信息），可以进一步熟悉class文件格式，并为下一步准备好基本信息（类名称，方法名等）

# 解释器的构成
最主要的两个部分：栈桢（stackFrame），堆（Heap）

## stackFrame
每执行一个方法，就创建一个 stackFrame, 方法返回则销毁 stackFrame。
stackFrame必须的基本信息： currentMethodName, currentClassName, 局部变量表，操作数栈，pc(程序计数器)，栈的最大高度
局部变量表：存放函数参数，局部变量值

## Heap
基本方法： 
add(Object *obj)  添加新创建的对象到堆
gc()              回收垃圾



