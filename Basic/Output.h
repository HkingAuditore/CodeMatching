#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                               命令行输出                               */
/************************************************************************/
// 输出效果：_tip(换行)
void ShowLine(char* _tip)
{
	printf("%s\n",_tip);
}

// 输出效果：_intro:
void ShowIntro(char* _intro)
{
	printf("%s:", _intro);
}

// 输出效果：_intro:_attr(换行)
void ShowAttribute(char* _intro,int _attr)
{
	ShowIntro(_intro);
	printf("%d\n",_attr);
}

// 输出效果：*******************(换行)
void DrawLine()
{
	printf("*******************\n");
}


/************************************************************************/
/*                                文件输出                                */
/************************************************************************/
#include "../File/File.h"

//输出Hash文件保存
int SaveHash(char* _content,char* _fileName)
{
	char* filePath[PATH_LENGTH];
	strcpy(filePath, CONFIG_SAVE_POSITION);
	strcat(filePath, _fileName);
	strcat(filePath, HASH_FILE_EXTENSION);


	FILE *hash = fopen(filePath, "w");
	if (!hash)return 0;
	printf("OPEN!!\n");
	fputs(_content, hash);
	printf("SAVE!!\n");
	fclose(hash);
	return 1;
}