#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Hash/Hash.h"
#include "../File/File.h"

typedef struct searchingResult {
    char *KeyWord;
    int *MatchPositions;
    int NumOfMatch;
} SearchingResult;

typedef struct searchingResults {
    int NumOfLine;
    SearchingResult **Results;
    int NumOfResults;
} SearchingResults;


//KMP检测法
SearchingResults *KMPTraversal(Code *_target, HashTable *_keywordTable);

//哈希查找法
SearchingResults *HashTraversal(Code *_target, HashTable *_keywordTable);

//打印匹配结果
int WriteMatchResults(char* _name, SearchingResults *_result);

//释放结果内存
void FreeResults(SearchingResults* _results);