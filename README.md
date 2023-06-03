# CryptoExpr
## Introduction

应用密码学实验课程的代码。

使用的语言：C++

实现的经典加密算法：凯撒密码、单表置换密码、仿射变换密码、DES、AES、RSA

实现的消息摘要算法：MD5

## How to use

每个算法是一个保存在对应cpp源文件中的类，他们均继承自BaseCipher类~~不过我暂时还没有看到这样做的必要性~~

**请使用Task分支来正确运行**

在main.cpp中调用所有这些算法。输入命令以执行对应的算法（大小写敏感）

- 凯撒密码：caesar
- 单表置换密码：mono
- 仿射变换密码：affine
- DES：des
- AES：aes
- RSA：rsa
- MD5：md5
