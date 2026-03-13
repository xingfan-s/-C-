#include <stdio.h>
#include "string.h"
#include "用户操作界面.h"
#include "文本编辑器.h"

#define scanf scanf_s

int main() {


    // 初始化文本编辑器
    wen 编辑器;
    初始化编辑器(&编辑器);

    用户操作界面(&编辑器);  // 传递编辑器指针

    return 0;
}