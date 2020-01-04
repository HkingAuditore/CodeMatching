#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                               ���������                               */
/************************************************************************/
// ���Ч����_tip(����)
static void ShowLine(char* _tip)
{
	printf("%s\n", _tip);
}

// ���Ч����_intro:
static void ShowIntro(char* _intro)
{
	printf("%s:", _intro);
}

//���Ч���������У�
static void SwitchLine()
{
	printf("\n");
}

// INT ���Ч����_intro:_attr(����)
static void ShowAttribute_Int(char* _intro, int _attr)
{
	ShowIntro(_intro);
	printf("%d\n", _attr);
}

// DOUBLE ���Ч����_intro:_attr(����)
static void ShowAttribute_Double(char* _intro, double _attr)
{
	ShowIntro(_intro);
	printf("%f\n", _attr);
}

// ���Ч����*******************(����)
static void DrawLine()
{
	printf("*******************\n");
}

//�����ά���飬���Ч����_name��[x,x],[x,x],[x,x],[x,x]...(����)
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

//���һλ���飬���Ч����_name:[x,x,x....](����)
static void ShowArray(char* _name,int _dimension,const int* _array)
{
	printf("%s:[",_name);
	for (int i = 0; i < _dimension; i++)
	{
		printf("%d", _array[i]);
		if (i < _dimension - 1)printf(",");
	}
	printf("]\n");
	
}

/************************************************************************/
/*                                �ļ����                                */
/************************************************************************/
#include "../File/File.h"

//���Hash�ļ�����
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
