#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAXSTR 100
#define END_OF_READ 0

/************************************************************************/
/*                               ����������                               */
/************************************************************************/
// ��ȡһ������
int ReadInt()
{
	int input;
	scanf("%d", &input);
	return input;
}
// ��ȡһ���ַ���
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
/*                                �ļ�����                                */
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