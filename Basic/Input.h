#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAXSTR 100
#define END_OF_READ 0
#define MAX_CODE_CHAR 10000
#define MAX_CODE_LINE 1000

/************************************************************************/
/*                               命令行输入                               */
/************************************************************************/
// 读取一个整型
static int ReadInt()
{
	int input;
	scanf("%d", &input);
	return input;
}
// 读取一个字符串
static char* ReadStr()
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

static int ReadContinue()
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
static char* ReadHashFile(char* _fileName)
{
	char* filePath = GetHashFilePath(_fileName);
	FILE *hash = fopen(filePath, "r");
	if (!hash)return NULL;
	char* content = (char*)calloc(MAXCHAR_HASH, sizeof(char));
	fgets(content, MAXCHAR_HASH, hash);
	free(filePath);
	return content;
}

static Code* ReadCodeFile(char* _fileName)
{
	char* filePath = GetCodeFilePath(_fileName);
	FILE *codeFile = fopen(filePath, "r");
	Code* code = (Code*)malloc(sizeof(Code));
	if (!codeFile)return NULL;
	char** content = (char**)calloc(MAX_CODE_LINE, sizeof(char*));
	for (int i = 0; i < MAX_CODE_LINE; i++)
	{
		content[i] = (char*)calloc(MAX_CODE_CHAR, sizeof(char));
	}
	char curPos=0;
	char tempRead;

	// while ((tempRead = fgetc(code))!=EOF)
	// {
	// 	// printf("%c", tempRead);
	// 	content[curPos++] = tempRead;
	// }
	while (!feof(codeFile))
	{
		fgets(content[curPos++], MAX_CODE_CHAR, codeFile);
	}

	code->Content = content;
	code->NumOfLine = curPos;
	
	// printf("******************************************\n");
	
	free(filePath);
	return code;
}