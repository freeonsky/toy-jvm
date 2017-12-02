# toy-jvm
a toy jvm written by cpp

## 使用工具
### visual studio 2017 community
创建cross platform 工程，程序跑在linux系统，在windows系统用visual studio 2017远程调试。
### linux 操作系统，需要安装（openssh-server g++ gdb gdbserver）
```
以ubuntu 16.04为例
sudo apt-get install openssh-server g++ gdb gdbserver
```

# TODO
## 读取class格式文件到内存
* 定义class 文件格式中的各种数据结构，参考jvm specification
* 读取class 文件到内存

## 写一个类似javap的class文件解析器，能够正常解析class文件

## 解释执行class文件