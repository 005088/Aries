#include "stdio.h"
#include "stdlib.h"

int CountcCharacter(FILE* fp)  //文件中字符数 
{
	char c; 
	int count = 0;
	while ((c = fgetc(fp)) != EOF)
		count++;
	return count;  //返回字符数 
}

int CountWord(FILE* fp) { //文件中词数 
	char c;
	int count = 0, mark = 0;	//标记：mark为0不是词，mark为1是词
	while ((c = fgetc(fp)) != EOF) {
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			if (mark == 0) {
				mark = 1;
				count++;
			}
		}
		else {
			if (mark == 1)
				mark = 0;
		}
	}
	return count;
}

int CountLine(FILE* fp) //文件中行数 
{
	char c;
	int count = 0;
	if (fp == NULL)return 0;	//判断文件内是否为空
	count = 1;		//不为空，首行为1
	while ((c = fgetc(fp)) != EOF)
		if (c == '\n')  //用数换行符的方式计算文件中的行数 
			count++;
	return count; //返回行数
}

int main() {
	while (1) {
		FILE* fp;
		errno_t err = 0;
		int count, order;	//count：计数，order：控制命令 
		err = fopen_s(&fp, "E:\\test.c", "r");	// 测试文件位置
		if (err) {			 
			printf("文件读取失败！\n");
			exit(0);
		}
		printf("wc.exe模仿功能: 1.-c（获取字符数）2.-w（获取词数）3.-l（获取行数）0.exit\n请选择您要进行的操作: ");
		scanf_s("%d", &order);	//命令输入
		do {
			switch (order) {
			case 1: count = CountcCharacter(fp); printf("该文件字符数为%d。\n", count); break;
			case 2: count = CountWord(fp); printf("该文件词数为%d。\n", count); break;
			case 3: count = CountLine(fp); printf("该文件行数为%d。\n", count); break;
			default:if (order == 0)exit(0); printf("输入错误，请重新选择您要进行的操作: "); scanf_s("%d", &order); break;
			}
		} while (order != 1 && order != 2 && order != 3 && order != 0);
		printf("\n");
		fclose(fp);
	}
}
