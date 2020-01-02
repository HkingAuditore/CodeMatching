#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                               命令行输出                               */
/************************************************************************/
// 输出效果：_tip(换行)
static void ShowLine(char* _tip)
{
	printf("%s\n", _tip);
}

// 输出效果：_intro:
static void ShowIntro(char* _intro)
{
	printf("%s:", _intro);
}

//输出效果：（换行）
static void SwitchLine()
{
	printf("\n");
}

// 输出效果：_intro:_attr(换行)
static void ShowAttribute(char* _intro, int _attr)
{
	ShowIntro(_intro);
	printf("%d\n", _attr);
}

// 输出效果：*******************(换行)
static void DrawLine()
{
	printf("*******************\n");
}

//输出二维数组，输出效果：_name：[x,x],[x,x],[x,x],[x,x]...(换行)
static int Write2DArray(char* _name, int** _array, int _numOfLine)
{
	int numOfOutput = 0;
	printf("%s:", _name);
	for (int j = 0; j < _numOfLine; j++)
	{
		int k = 0;
		while ((_array[j][k] != 0))
		{
			if (numOfOutput)printf(",");
			printf("[%d,%d]", j, _array[j][k] != -1 ? _array[j][k] : 0);
			numOfOutput++;
			k++;
		}
	}
	SwitchLine();
	return numOfOutput;
}

/************************************************************************/
/*                                文件输出                                */
/************************************************************************/
#include "../File/File.h"

//输出Hash文件保存
static int SaveHashFile(char* _content, char* _fileName)
{
	char* filePath = GetHashFilePath(_fileName);
	FILE *hash = fopen(filePath, "w");
	if (!hash)return 0;
	printf("OPEN!!\n");
	fputs(_content, hash);
	printf("SAVE!!\n");
	fclose(hash);
	free(filePath);
	return 1;
}
