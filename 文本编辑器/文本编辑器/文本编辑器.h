#pragma once
#include <stdio.h>
#include <stdlib.h>

#define MAX_行 1000
#define MAX_文件名 50
#define scanf scanf_s

// 定义文本行结构体（链表节点）
typedef struct 文本行 {
    char 内容[MAX_行];
    struct 文本行* 下一行;
} hang;

typedef struct 文本编辑器 {
    hang* 首行;
    hang* 尾行;
    int 总行数;
    char 文件名[MAX_文件名];
    int 已修改;
} wen;

// 函数声明
void 初始化编辑器(wen* 文本);
int 打开文件(wen* 文本, const char* 文件名);
void 显示内容(const wen* 文本);
hang* 创建新行(const char* 内容);
int 保存文件(const wen* 文本);
void 释放内存(wen* 文本);
hang* 获取行(const wen* 文本, int 行号);
int 插入行(wen* 文本, int 行号, const char* 内容);
int 修改行(wen* 文本, int 行号, const char* 新内容);
int 删除行(wen* 文本, int 起始行, int 行数);
int 拷贝行(wen* 文本, int 源行号, int 目标行号);
int 查找字符串函数(wen* 文本, const char* 查找字符串);
int 替换字符串函数(wen* 文本, const char* 查找字符串, const char* 替换字符串);