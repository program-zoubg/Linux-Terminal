# Linux-Terminal
> A small Linux terminal emulator for Windows that allows you to use Linux commands on Windows and achieve the corresponding results. 一个在Windows上运行的小巧的Linux终端仿真器程序，它允许您在Windows上使用Linux命令并实现相应效果。

## 实现

语言：`C/C++`

标准：`GNU C99` | `ISO C++11`

Release版本编译环境：`TDM-GCC 4.9.2 Release` & `O3优化`

## 本地编译

在**Windows**环境下使用`GCC`编译器编译，或自行写`CMake File`：

```shell
g++ main.cpp -o terminal.exe
```

可选的加上`-O3`优化参数

## 特性

目前实现：

- `ls`
- `pwd`
- `mkdir`
- `rm`
- `exit`
- `cd`

支持属性传参，部分调用`Windows`提供的`cmd`程序接口。

## 开源协议

以`GNU GPLv3`协议开源，进行*分发、使用、修改*等操作请遵守协议
