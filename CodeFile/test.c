#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                                                              */
/************************************************************************/
// 
static void ShowLine(char* _tip)
{
	printf("%s\n", _tip);
}

// 
static void ShowIntro(char* _intro)
{
	printf("%s:", _intro);
}

// 
static void ShowAttribute(char* _intro, int _attr)
{
	ShowIntro(_intro);
	printf("%d\n", _attr);
}

// 
static void DrawLine()
{
	printf("*******************\n");
}

/************************************************************************/
/*                                                                */
/************************************************************************/
#include "../File/File.h"

//
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