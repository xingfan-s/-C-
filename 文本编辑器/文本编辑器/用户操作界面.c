#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "用户操作界面.h"
#include "文本编辑器.h"

#define scanf scanf_s

void 用户操作界面(wen* 文本) {
    printf("欢迎使用文本编辑器！\n\n");
    printf("请选择操作：\n");
    printf("1. 打开文件（新或旧）\n");
    printf("2. 显示文件内容\n");
    printf("3. 插入行\n");
    printf("4. 删除行\n");
    printf("5. 拷贝行\n");
    printf("6. 修改行\n");
    printf("7. 查找字符串\n");
    printf("8. 替换字符串\n");
    printf("9. 存盘退出\n");
    printf("0. 放弃编辑\n");
    printf("10. 查看选项\n");
    printf("注意：在操作过程中输入'q'可以跳过当前操作\n\n");

    int 选择;
    int 继续 = 1;

    while (继续) {
        printf("请输入选项: ");

        // 处理输入错误
        if (scanf_s("%d", &选择) != 1) {
            printf("输入错误，请输入数字！\n");
            while (getchar() != '\n');  // 清空输入缓冲区
            continue;
        }

        // 清空输入缓冲区（避免换行符影响后续输入）
        while (getchar() != '\n');

        switch (选择) {
        case 1:  // 打开文件
        {
            char 文件名[100];
            printf("请输入文件名（可包括盘符、路径，不超过19个字符，输入q跳过，直接回车返回）: ");

            // 安全地读取文件名
            if (fgets(文件名, sizeof(文件名), stdin) == NULL) {
                printf("读取文件名失败！\n");
                break;
            }

            // 去除末尾的换行符
            int 长度 = my_strlen(文件名);
            if (长度 > 0 && 文件名[长度 - 1] == '\n') {
                文件名[长度 - 1] = '\0';
            }

            // 检查是否为空（直接回车）
            if (my_strlen(文件名) == 0) {
                printf("文件名不能为空，已返回主菜单！\n");
                break;
            }

            // 检查是否要跳过
            if (my_strcmp(文件名, "q") == 1 || my_strcmp(文件名, "Q") == 1) {
                printf("已跳过打开文件操作\n");
                break;
            }

            // 检查文件名长度是否符合要求
            if (my_strlen(文件名) > 19) {
                printf("错误：文件名超过19个字符！\n");
                break;
                // 其实我觉得没必要限制19个字符
                // 但老师这么要求，一定有她的道理
            }

            if (打开文件(文本, 文件名)) {
                printf("文件打开/创建成功！\n");
            }
            else {
                printf("文件打开/创建失败！\n");
            }
        }
        break;

        case 2:  // 显示文件内容
            显示内容(文本);
            break;

        case 3:  // 插入行
        {
            if (my_strlen(文本->文件名) == 0) {
                printf("请先打开一个文件！\n");
                break;
            }

            char 确认;
            printf("要插入到哪一行？请输入行号（输入q跳过）: ");

            // 检查是否输入的是'q'
            if (scanf_s("%c", &确认, 1) != 1) {
                printf("输入错误！\n");
                while (getchar() != '\n');
                break;
            }

            // 如果输入'q'则跳过
            if (确认 == 'q' || 确认 == 'Q') {
                printf("已跳过插入行操作\n");
                while (getchar() != '\n');  // 清空缓冲区
                break;
            }

            // 如果不是'q'，则将输入的字符转换回数字
            ungetc(确认, stdin);

            int 行号;
            if (scanf_s("%d", &行号) != 1) {
                printf("输入错误，请输入数字！\n");
                while (getchar() != '\n');
                break;
            }

            // 清除行号输入后的换行符
            while (getchar() != '\n');

            printf("请输入要插入的内容（输入q跳过）: ");
            char 内容[MAX_行];

            if (fgets(内容, sizeof(内容), stdin) == NULL) {
                printf("读取内容失败！\n");
                break;
            }

            // 去除末尾的换行符
            int 长度 = my_strlen(内容);
            if (长度 > 0 && 内容[长度 - 1] == '\n') {
                内容[长度 - 1] = '\0';
            }

            // 检查是否要跳过
            if (my_strcmp(内容, "q") == 1 || my_strcmp(内容, "Q") == 1) {
                printf("已跳过插入行操作\n");
                break;
            }

            if (插入行(文本, 行号, 内容)) {
                printf("插入成功！\n");
                显示内容(文本);
            }
            else {
                printf("插入失败！\n");
            }
        }
        break;

        case 4:  // 删除行
        {
            if (my_strlen(文本->文件名) == 0) {
                printf("请先打开一个文件！\n");
                break;
            }

            char 跳过选择;
            printf("要从哪一行开始删除？请输入起始行号（输入q跳过）: ");

            if (scanf_s("%c", &跳过选择, 1) != 1) {
                printf("输入错误！\n");
                while (getchar() != '\n');
                break;
            }

            // 如果输入'q'则跳过
            if (跳过选择 == 'q' || 跳过选择 == 'Q') {
                printf("已跳过删除行操作\n");
                while (getchar() != '\n');  // 清空缓冲区
                break;
            }

            ungetc(跳过选择, stdin);

            int 起始行;
            if (scanf_s("%d", &起始行) != 1) {
                printf("输入错误，请输入数字！\n");
                while (getchar() != '\n');
                break;
            }

            while (getchar() != '\n');  // 清空缓冲区

            printf("要删除多少行？请输入行数（输入q跳过）: ");
            char 行数输入[10];

            if (fgets(行数输入, sizeof(行数输入), stdin) == NULL) {
                printf("读取行数失败！\n");
                break;
            }

            // 去除末尾的换行符
            int 长度 = my_strlen(行数输入);
            if (长度 > 0 && 行数输入[长度 - 1] == '\n') {
                行数输入[长度 - 1] = '\0';
            }

            // 检查是否要跳过
            if (my_strcmp(行数输入, "q") == 1 || my_strcmp(行数输入, "Q") == 1) {
                printf("已跳过删除行操作\n");
                break;
            }

            int 行数 = atoi(行数输入);
            if (行数 <= 0) {
                printf("错误：行数必须大于0！\n");
                break;
            }

            // 调用删除行函数
            if (删除行(文本, 起始行, 行数)) {
                printf("删除成功！\n");
                显示内容(文本);
            }
            else {
                printf("删除失败！\n");
            }
        }
        break;

        case 5:  // 拷贝行
        {
            if (my_strlen(文本->文件名) == 0) {
                printf("请先打开一个文件！\n");
                break;
            }

            char 跳过选择1;
            printf("要拷贝哪一行？请输入源行号（输入q跳过）: ");

            if (scanf_s("%c", &跳过选择1, 1) != 1) {
                printf("输入错误！\n");
                while (getchar() != '\n');
                break;
            }

            if (跳过选择1 == 'q' || 跳过选择1 == 'Q') {
                printf("已跳过拷贝行操作\n");
                while (getchar() != '\n');
                break;
            }

            ungetc(跳过选择1, stdin);

            int 源行号;
            if (scanf_s("%d", &源行号) != 1) {
                printf("输入错误，请输入数字！\n");
                while (getchar() != '\n');
                break;
            }

            while (getchar() != '\n');  // 清空缓冲区

            char 跳过选择2;
            printf("要拷贝到哪一行之前？请输入目标行号（输入q跳过）: ");

            if (scanf_s("%c", &跳过选择2, 1) != 1) {
                printf("输入错误！\n");
                while (getchar() != '\n');
                break;
            }

            if (跳过选择2 == 'q' || 跳过选择2 == 'Q') {
                printf("已跳过拷贝行操作\n");
                while (getchar() != '\n');
                break;
            }

            ungetc(跳过选择2, stdin);

            int 目标行号;
            if (scanf_s("%d", &目标行号) != 1) {
                printf("输入错误，请输入数字！\n");
                while (getchar() != '\n');
                break;
            }

            while (getchar() != '\n');  // 清空缓冲区

            // 调用拷贝行函数
            if (拷贝行(文本, 源行号, 目标行号)) {
                printf("拷贝成功！\n");
                显示内容(文本);
            }
            else {
                printf("拷贝失败！\n");
            }
        }
        break;

        case 6:  // 修改行
        {
            if (my_strlen(文本->文件名) == 0) {
                printf("请先打开一个文件！\n");
                break;
            }

            printf("当前文件内容：\n");
            显示内容(文本);

            char 跳过选择;
            printf("要修改哪一行？请输入行号（输入q跳过，输入p重新查看当前内容）: ");

            if (scanf_s("%c", &跳过选择, 1) != 1) {
                printf("输入错误！\n");
                while (getchar() != '\n');
                break;
            }

            // 如果输入'q'则跳过
            if (跳过选择 == 'q' || 跳过选择 == 'Q') {
                printf("已跳过修改行操作\n");
                while (getchar() != '\n');  // 清空缓冲区
                break;
            }

            // 如果输入'p'则显示内容并重新询问
            if (跳过选择 == 'p' || 跳过选择 == 'P') {
                printf("当前文件内容：\n");
                显示内容(文本);
                while (getchar() != '\n');  // 清空缓冲区
                printf("\n");
                continue;  // 重新开始这个case
            }

            ungetc(跳过选择, stdin);

            int 行号;
            if (scanf_s("%d", &行号) != 1) {
                printf("输入错误，请输入数字！\n");
                while (getchar() != '\n');
                break;
            }

            while (getchar() != '\n');  // 清空缓冲区

            // 获取当前行的内容并显示
            hang* 当前行 = 获取行(文本, 行号);
            if (当前行 != NULL) {
                printf("第 %d 行的当前内容: %s\n", 行号, 当前行->内容);
            }
            else {
                printf("错误：找不到第 %d 行！\n", 行号);
                break;
            }

            printf("请输入新的内容（输入q跳过，输入e保持原内容不变）: ");
            char 新内容[MAX_行];

            if (fgets(新内容, sizeof(新内容), stdin) == NULL) {
                printf("读取内容失败！\n");
                break;
            }

            // 去除末尾的换行符
            int 长度 = my_strlen(新内容);
            if (长度 > 0 && 新内容[长度 - 1] == '\n') {
                新内容[长度 - 1] = '\0';
            }

            // 检查是否要跳过
            if (my_strcmp(新内容, "q") == 1 || my_strcmp(新内容, "Q") == 1) {
                printf("已跳过修改行操作\n");
                break;
            }

            // 如果输入'e'则保持原内容
            if (my_strcmp(新内容, "e") == 1 || my_strcmp(新内容, "E") == 1) {
                printf("保持原内容不变\n");
                break;
            }

            if (修改行(文本, 行号, 新内容)) {
                printf("修改成功！\n");
                显示内容(文本);
            }
            else {
                printf("修改失败！\n");
            }
        }
        break;

        case 7:  // 查找字符串
        {
            if (my_strlen(文本->文件名) == 0) {
                printf("请先打开一个文件！\n");
                break;
            }

            printf("请输入要查找的字符串（输入q跳过）: ");
            char 查找字符串[MAX_行];

            if (fgets(查找字符串, sizeof(查找字符串), stdin) == NULL) {
                printf("读取字符串失败！\n");
                break;
            }

            // 去除末尾的换行符
            int 长度 = my_strlen(查找字符串);
            if (长度 > 0 && 查找字符串[长度 - 1] == '\n') {
                查找字符串[长度 - 1] = '\0';
            }

            // 检查是否要跳过
            if (my_strcmp(查找字符串, "q") == 1 || my_strcmp(查找字符串, "Q") == 1) {
                printf("已跳过查找字符串操作\n");
                break;
            }

            if (my_strlen(查找字符串) == 0) {
                printf("错误：要查找的字符串不能为空！\n");
                break;
            }

            // 调用查找字符串函数
            if (查找字符串函数(文本, 查找字符串)) {
                printf("查找完成！\n");
            }
            else {
                printf("未找到匹配的字符串！\n");
            }
        }
        break;

        case 8:  // 替换字符串
        {
            if (my_strlen(文本->文件名) == 0) {
                printf("请先打开一个文件！\n");
                break;
            }

            printf("请输入要查找的字符串（输入q跳过）: ");
            char 查找字符串[MAX_行];

            if (fgets(查找字符串, sizeof(查找字符串), stdin) == NULL) {
                printf("读取字符串失败！\n");
                break;
            }

            // 去除末尾的换行符
            int 长度 = my_strlen(查找字符串);
            if (长度 > 0 && 查找字符串[长度 - 1] == '\n') {
                查找字符串[长度 - 1] = '\0';
            }

            // 检查是否要跳过
            if (my_strcmp(查找字符串, "q") == 1 || my_strcmp(查找字符串, "Q") == 1) {
                printf("已跳过替换字符串操作\n");
                break;
            }

            printf("请输入要替换成的字符串（输入q跳过）: ");
            char 替换字符串[MAX_行];

            if (fgets(替换字符串, sizeof(替换字符串), stdin) == NULL) {
                printf("读取字符串失败！\n");
                break;
            }

            // 去除末尾的换行符
            长度 = my_strlen(替换字符串);
            if (长度 > 0 && 替换字符串[长度 - 1] == '\n') {
                替换字符串[长度 - 1] = '\0';
            }

            // 检查是否要跳过
            if (my_strcmp(替换字符串, "q") == 1 || my_strcmp(替换字符串, "Q") == 1) {
                printf("已跳过替换字符串操作\n");
                break;
            }

            printf("即将把 \"%s\" 替换为 \"%s\"，是否确认？(y/n): ", 查找字符串, 替换字符串);
            char 确认;
            scanf_s(" %c", &确认, 1);
            while (getchar() != '\n');

            if (确认 != 'y' && 确认 != 'Y') {

                if (确认 == 'n' || 确认 == 'N') {
                    printf("操作已取消\n");
                }
                else { printf("操作已取消，下次记得输入'y'或'n'"); }

                break;
            }

            // 调用替换字符串函数
            if (替换字符串函数(文本, 查找字符串, 替换字符串)) {
                printf("替换完成！\n");
                显示内容(文本);
            }
            else {
                printf("未找到要替换的字符串！\n");
            }
        }
        break;

        case 9:  // 存盘退出
        {
            printf("是否保存文件并退出？(y/n): ");
            char 确认;
            scanf_s(" %c", &确认, 1);
            while (getchar() != '\n');

            if (确认 == 'y' || 确认 == 'Y') {
                if (保存文件(文本)) {
                    printf("文件已保存，正在退出...\n");
                    继续 = 0;
                }
                else {
                    printf("保存失败，请重试！\n");
                }
            }
            else if (确认 == 'n' || 确认 == 'N') {
                printf("退出操作已取消\n");
            }
            else { printf("操作已取消，下次记得输入'y'或'n'"); }
        }
        break;

        case 0:  // 放弃编辑
        {
            printf("是否放弃所有修改并退出？(y/n): ");
            char 确认;
            scanf_s(" %c", &确认, 1);
            while (getchar() != '\n');

            if (确认 == 'y' || 确认 == 'Y') {
                printf("放弃编辑，正在退出...\n");
                if (文本->已修改) {
                    printf("有未保存的修改，是否保存？(y/n): ");
                    scanf_s(" %c", &确认, 1);
                    while (getchar() != '\n');

                    if (确认 == 'y' || 确认 == 'Y') {
                        保存文件(文本);
                    }
                }
                继续 = 0;
            }
            else if (确认 == 'n' || 确认 == 'N') {
                printf("退出操作已取消\n");
            }
            else { printf("操作已取消，下次记得输入'y'或'n'"); }
        }
        break;

        case 10:  // 查看选项
            printf("\n请选择操作：\n");
            printf("1. 打开文件（新或旧）\n");
            printf("2. 显示文件内容\n");
            printf("3. 插入行\n");
            printf("4. 删除行\n");
            printf("5. 拷贝行\n");
            printf("6. 修改行\n");
            printf("7. 查找字符串\n");
            printf("8. 替换字符串\n");
            printf("9. 存盘退出\n");
            printf("0. 放弃编辑\n");
            printf("10. 查看选项\n");
            printf("注意：在操作过程中输入'q'可以跳过当前操作\n\n");
            break;

        default:
            printf("选项%d暂未实现或无效，请输入0-10之间的数字\n", 选择);
            break;
        }
    }

    // 释放内存
    释放内存(文本);
}