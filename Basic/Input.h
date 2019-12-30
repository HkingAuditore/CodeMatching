#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAXSTR 100
#define END_OF_READ 0

/************************************************************************/
/*                               命令行输入                               */
/************************************************************************/
// 读取一个整型
int ReadInt()
{
	int input;
	scanf("%d", &input);
	return input;
}
// 读取一个字符串
char* ReadStr()
{
	char* input = (char*)malloc(MAXSTR * sizeof(char));
	char temp;
	int i = 0;
	while (scanf("%c", &temp) && temp != '\n' && temp != ' ')
	{
		input[i++] = temp;
	}
	input[i] = '\0';
	return input;
}

int ReadContinue()
{
	int input;
	scanf_s("%d", &input);
	if (input != END_OF_READ)
	{
		while (getchar() != '\n') {};
		return 1;
	}
	else
	{
		while (getchar() != '\n') {};
		return 0;
	}
}


/************************************************************************/
/*                                文件输入                                */
/************************************************************************/
#include "../File/File.h"
char* ReadHashFile(char* _fileName)
{
	char* filePath = GetHashFilePath(_fileName);
	FILE *hash = fopen(filePath, "r");
	if (!hash)return NULL;
	char* content = (char*)calloc(MAXCHAR_HASH, sizeof(char));
	fgets(content, MAXCHAR_HASH, hash);
	free(filePath);
	return content;
}