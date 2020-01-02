#pragma once
#include <string.h>
#define PATH_LENGTH 100
#define HASH_SAVE_POSITION "HashFile/"
#define CODE_SAVE_POSITION "CodeFile/"
#define HASH_FILE_EXTENSION ".hash"
#define CODE_FILE_EXTENSION ".c"
#define MAXCHAR_NODE 100
#define MAXCHAR_HASH 1000

typedef struct code
{
	char** Content;
	int NumOfLine;
}Code;

static char* GetHashFilePath(char* _fileName)
{
	char* filePath = (char*)calloc(PATH_LENGTH, sizeof(char));
	strcpy(filePath, HASH_SAVE_POSITION);
	strcat(filePath, _fileName);
	strcat(filePath, HASH_FILE_EXTENSION);
	return filePath;
}
static char* GetCodeFilePath(char* _fileName)
{
	char* filePath = (char*)calloc(PATH_LENGTH, sizeof(char));
	strcpy(filePath, CODE_SAVE_POSITION);
	strcat(filePath, _fileName);
	strcat(filePath, CODE_FILE_EXTENSION);
	return filePath;
}