#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/************************************************************************/
/*                               ���������                               */
/************************************************************************/
// ���Ч����_tip(����)
void ShowLine(char* _tip)
{
	printf("%s\n",_tip);
}

// ���Ч����_intro:
void ShowIntro(char* _intro)
{
	printf("%s:", _intro);
}

// ���Ч����_intro:_attr(����)
void ShowAttribute(char* _intro,int _attr)
{
	ShowIntro(_intro);
	printf("%d\n",_attr);
}

// ���Ч����*******************(����)
void DrawLine()
{
	printf("*******************\n");
}


/************************************************************************/
/*                                �ļ����                                */
/************************************************************************/
#include "../File/File.h"

//���Hash�ļ�����
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