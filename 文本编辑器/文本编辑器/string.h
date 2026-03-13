
#pragma once
#include <stdio.h>


// 函数声明
char my_strcpy(char* 粘贴到, const char* 被复制的);
char my_strcat(char* 追加到, const char* 要添加的);
int my_strcmp(const char* s1, const char* s2);
int my_strlen(const char* 字符串);
void* my_memset(void* str, int c, int n);
/*str -- 指向要填充的内存区域的指针。
c -- 要设置的值，通常是一个无符号字符。
n -- 要被设置为该值的字节数。*/