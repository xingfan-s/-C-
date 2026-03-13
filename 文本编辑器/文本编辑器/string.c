
#include <stdio.h>
#define scanf scanf_s
char my_strcpy(char* 粘贴到, const char* 被复制的) {
	//报错
	if (粘贴到 == NULL || 被复制的 == NULL) {
		printf("\nEOF\tstrcpy使用错误\n");
		return EOF;
	}
	char* 返回值 = 粘贴到;
	// 复制字符串
	while (*被复制的 != '\0') {
		*粘贴到 = *被复制的;
		粘贴到++;
		被复制的++;
	}
	*粘贴到 = '\0'; // 添加字符串结束符
	return *返回值;
}
char my_strcat(char* 追加到, const char* 要添加的) {

	//报错
	if (追加到 == NULL || 要添加的 == NULL) {
		printf("\nEOF\tstrcat使用错误\n");
		return EOF;
	}
	char* 返回值 = 追加到;
	// 移动到追加位置
	while (*追加到 != '\0') {
		追加到++;
	}
	// 追加字符串
	while (*要添加的 != '\0') {
		*追加到 = *要添加的;
		追加到++;
		要添加的++;
	}
	*追加到 = '\0'; // 添加字符串结束符
	return *返回值;
}
int my_strcmp(const char* s1, const char* s2) {
	if (s1 == NULL || s2 == NULL) {
		printf("\nEOF\tstrcmp使用错误\n");
		return EOF;
	}
	while (*s1 != '\0' && *s2 != '\0') {
		if (*s1 != *s2) {
			return 0; // 字符不相等
		}
		s1++;
		s2++;
	}
	return (*s1 == '\0' && *s2 == '\0') ? 1 : 0; // 两字符串相等返回1，否则返回0
}
int my_strlen(const char* 字符串) {
	if (字符串 == NULL) {
		printf("\nEOF\tstrlen使用错误\n");
		return EOF;
	}
	int 长度 = 0;
	if (字符串 != NULL) {
		while (*字符串 != '\0') {
			长度++;
			字符串++;
		}
	}
	return 长度;
}
void* my_memset(void* str, int c, int n) {
	if (str == NULL) {
		printf("\nNULL\tmemset使用错误\n");
		return NULL;
	}
	unsigned char* ptr = (unsigned char*)str;
	for (int i = 0; i < n; i++) {
		ptr[i] = (unsigned char)c;
	}
	return str;
}
