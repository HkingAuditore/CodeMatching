#pragma once
#include <string.h>
#define PATH_LENGTH 100
#define HASH_SAVE_POSITION "HashFile/"
#define HASH_FILE_EXTENSION ".hash"
#define MAXCHAR_NODE 100
#define MAXCHAR_HASH 1000

char* GetHashFilePath(char* _fileName)
{
	char* filePath= (char*)calloc(PATH_LENGTH,sizeof(char));
	strcpy(filePath, HASH_SAVE_POSITION);
	strcat(filePath, _fileName);
	strcat(filePath, HASH_FILE_EXTENSION);
	return filePath;
}