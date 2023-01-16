# Unique简介

## 信息
	为SourceSpace工作室编写代码准备的编程语言。

## 如何安装？

### 1.我默认您位于“Unique”目录中，并且您的计算机有“Make”(或者mingw32-make)。

### 2.安装Unique编译器和Unique虚拟机。
1. 使用`make`或`mingw32 make`安装。
2. 编译器在`/UCM/build/`并且叫`quec`，
   虚拟机处于`UVM/build/`并且叫`que`。
3. 我建议设置环境变量之后使用`quec(文件名)`运行编译器，
   用`que(字节码文件名)`运行虚拟机。

### 3.尝试编译Unique代码。
1. 在`./testbench/test1`中有一个名为`pro1.que`的Unique代码文件。
2. `quec ./testbench/test1/pro1.que`进行编译。
3. `que pro1`执行Unique字节码。

# 更多语言
1. [Engilsh](../README.md)
2. 如需其他语言，请联系我们。

# 更多信息
1. [更新日志](./updateLog.md)
2. [语法](./garmmar.md)

# 鸣谢
&emsp;非常感谢一个叫theflysong的github用户。<br>
&emsp;当时是在一个QQ群里认识的，我得知他挺懂编程语言时，加了他QQ并且问起一些有关的问题，他也挺有耐心地给我解答。<br>
&emsp;不久，他邀请我帮他写rain语言(开源的，[rain语言项目仓库](https://github.com/theflysong/rain)。他说这个已经是第4次重构的了。)，写得真的不错，我这个Unique语言就是从中得到灵感的<br>
&emsp;最后，我真的特别感谢theflysong的帮助与支持。

# 如何联系我们？
1. 添加我的QQ: 3572113478
2. 发送电子邮件: Kkasi2007@outlook.com