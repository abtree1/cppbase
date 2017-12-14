//pragma 命令宏
#pragma once
//include 宏
#include<iostream>

using namespace std;
//简单宏(宏后面一定不要加；)
#define N 10
//宏定义带参数或操作符一定要加（）
#define MAX(x,y) ((x)>(y)?(x):(y))
#define IS_EVENT(n) ((n)%2 == 0)
#define TOUPPER(c) ('a'<=(c)&&(c)<='z'?(c)-'a'+'A':(c))
#define getchar() getc(stdin)
//带 '#' 和 '##'运算符
#define PRINT_INT(x) printf(#x"=%d\n", x)
/*
int i = 2,j = 1;
PRINT_INT(i/j) -> i/j=2
*/
#define GENERIC_MAX(type) \
type type##_max(type x, type y) \
{			 \
	return x>y?x:y; \
}
/*
GENERIC_MAX(long) ->
long long_max(long x, long y){
	return x > y?x:y;
}
*/
void f(){
//条件宏
#if N //N 不为0 或 undefined
	printf("in function f N is = %d \n", N);
//空宏
#
#elif defined(MAX) && defined(TOUPPER)
	printf("in function f upper 'c' is %c \n", TOUPPER('c'));
#else
//error 宏 中断程序编译 打印出错信息 通常用于处理一些条件宏不应该走到的分支 或者在某些平台不应该引用的头文件
#error In function f else cann't go into
#endif
}

//line 宏 在做编译器等工具时很有用
//从这行的下一行起 改变行号为50
#line 50
//从这行的下一行起 改变行号为other.h 的 51行
#line 51 "other.h"

void p();

//定义一个函数
GENERIC_MAX(int)

int main(){
	f();
	p();
#undef N   //取消N的定义
	PRINT_INT(int_max(1,2)); // -> int_max(1,2)=2
	return 0;
}

void p(){
//宏是在预处理期间处理 在main中undef了N  此处已经没有N的定义了
#ifndef N
	printf("in function p N is undefined \n");
#endif
}
