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


//KMP��ⷨ
SearchingResults *KMPTraversal(Code *_target, HashTable *_keywordTable);

//��ϣ���ҷ�
SearchingResults *HashTraversal(Code *_target, HashTable *_keywordTable);

//��ӡƥ����
int WriteMatchResults(char* _name, SearchingResults *_result);

//�ͷŽ���ڴ�
void FreeResults(SearchingResults* _results);