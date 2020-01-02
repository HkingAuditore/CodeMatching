#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Hash/Hash.h"
#include "../File/File.h"

typedef struct searchingResult
{
	char* KeyWord;
	int* MatchPositions;
	int NumOfMatch;
}SearchingResult;

typedef struct searchingResults
{
	int NumOfLine;
	SearchingResult** Results;
	int NumOfResults;
}SearchingResults;

SearchingResults* KMPTraversal(Code* _target, HashTable* _keywordTable);
int WriteMatchResults(SearchingResults* _result);