# LetCompileFly

#### 介绍
2021-2022学年编译原理课程设计，起名灵感源于某著名论坛LetITFly。

#### 安装教程

1.  克隆本仓库
2.  使用CMake构建运行

#### 语言文法

本次编译原理课程设计实现的语言是由小组成员自行设计的简化语言，命名为lcf语言。由于时间异常紧迫，目前支持的语法如下：

1. 定义变量，支持全局变量与局部变量，但是只有整形与字符型可以正常使用。支持多维数组。
```
var a:int,b:bool;   //定义一个整型变量与布尔型变量
var c[15]:float;    //定义一个长度为15的浮点型数组变量
var d[2][4]:char;   //定义一个2*4的字符型二维数组变量
```
2. 定义过程，要求无参数无返回值。程序段中必须有一个main过程。
```
proc main {
    //多条语句
}
```
3. 算术运算，支持加减乘除。
```
a[2][3]=(1+b)*(c[2]-d)/e[4][5][6];
```
4. 逻辑表达式与`if`条件语句。支持嵌套。
```
if(a==1 || b!=2)
    //语句
else if(c<3 && d>=4) {
    //语句块
} else {
    //语句块
}
```
5. `while`循环语句。支持嵌套以及与`if`语句嵌套。
```
if(a>1) {
    while(c<=5){
         //语句块   
    }
} else while(d!=0){
    //语句块
}
```

#### 使用说明

1.  编译代码，准备好DOSBOX虚拟环境与MASM编译环境
2.  编写符合lcf文法的源程序
3.  运行编译后的程序。根据提示选择对源程序进行词法分析或直接生成8086汇编代码
4.  进入DOSBOX环境，将生成的8086汇编代码编译并使用debug运行

#### 参与贡献

1.  Fork 本仓库
2.  新建 Feat_xxx 分支
3.  提交代码
4.  新建 Pull Request
