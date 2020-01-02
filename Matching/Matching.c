#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Hash/Hash.h"
#include "../Basic/Output.h"
#include "../Basic/Input.h"

#define  MAX_MATCHING 100;

typedef struct searchingResult
{
	char* KeyWord;
	int** MatchPositions;
	int NumOfMatch;
}SearchingResult;

typedef struct searchingResults
{
	int NumOfLine;
	SearchingResult** Results;
	int NumOfResults;
}SearchingResults;

int IsMark(char _char)
{
	char marks[] = " !@#$%^&*()-=_+{}[]|;:',<>./?.\n";
	for (int i = 0; i < strlen(marks); i++)
	{
		if (_char == marks[i])
		{
			return 1;
		}
	}
	return 0;
}


/************************************************************************/
/*                             KMP检测法                                 */
/************************************************************************/

int* GenerateMatchingInfo(char* _target)
{
	int *info = (int*)calloc(strlen(_target) + 1, sizeof(int));
	int comparePos = 0;
	for (int i = 1; i < strlen(_target); i++)
	{
		if (_target[i] == _target[comparePos])
		{
			info[i] = ++comparePos;
			continue;
		}
		if (_target[i] != _target[comparePos] && comparePos != 0)
		{
			// 回溯至最近的标记点
			comparePos = info[comparePos - 1];
			i--;
			continue;
		}
	}
	return info;
}

SearchingResult* KMPCompare(char* _target, Code* _origin)
{
	// DrawLine();
	// printf("%s:\n", _target);

	int* targetInfo = GenerateMatchingInfo(_target);
	SearchingResult* result = (SearchingResult*)malloc(sizeof(SearchingResult));
	result->KeyWord = _target;
	int** positions = (int**)calloc(MAX_CODE_LINE, sizeof(int*));
	for (int i = 0; i < MAX_CODE_LINE; i++)
	{
		positions[i] = (int*)calloc(MAX_CODE_CHAR, sizeof(int));
	}
	int num = 0;
	// 开始匹配
	int curPos = 0;
	for (int j = 0; j < _origin->NumOfLine; j++)
	{
		int lineMatch = 0;
		for (int i = 0; i < strlen(_origin->Content[j]);)
		{
			// printf("match %c : %c\n", _target[curPos], _origin->Content[j][i]);
			if (_target[curPos] == _origin->Content[j][i])
			{
				if (curPos == strlen(_target) - 1)
				{
					if (IsMark(_origin->Content[j][i + 1]))
					{
						positions[j][lineMatch++] = (i - strlen(_target) + 1) != 0 ? (i - strlen(_target) + 1) : -1;
						num++;
						// printf("GOT %s [%d]at[%d:%d]\n", _target, num,j, positions[j][num-1]);
					}
				}
				else
				{
					curPos++;
				}
				i++;
				continue;
			}
			else {
				if (curPos == 0)
				{
					i++;
					continue;
				}
				curPos = targetInfo[curPos - 1];
				continue;
			}
		}
	}
	result->MatchPositions = positions;
	result->NumOfMatch = num;
	return result;
}

SearchingResults* KMPTraversal(Code* _target, HashTable* _keywordTable)
{
	SearchingResults* results = (SearchingResults*)malloc(sizeof(SearchingResults));
	SearchingResult** allResult = (SearchingResult**)calloc(_keywordTable->Size + 1, sizeof(SearchingResult*));
	for (int i = 1; i <= _keywordTable->Size; i++)
	{
		if (!_keywordTable->Table[i]) { continue; }
		allResult[i] = KMPCompare(_keywordTable->Table[i]->Info->Keyword, _target);
	}
	results->Results = allResult;
	results->NumOfResults = _keywordTable->Size;
	results->NumOfLine = _target->NumOfLine;
	return results;
}


/************************************************************************/
/*                          哈希查找检测法                                 */
/************************************************************************/



int WriteMatchResults(SearchingResults* _result)
{
	for (int i = 1; i <= _result->NumOfResults; i++)
	{
		if (!(_result->Results[i]))continue;
		printf("%s:%d    ", _result->Results[i]->KeyWord, _result->Results[i]->NumOfMatch);
		if (_result->Results[i]->NumOfMatch != 0)
		{
			printf("Positions:");
			for (int j = 0; j < _result->NumOfLine; j++)
			{
				int k = 0;
				while ((_result->Results[i]->MatchPositions[j][k] != 0))
				{
					printf("at[%d,%d] ", j, _result->Results[i]->MatchPositions[j][k] != -1 ? _result->Results[i]->MatchPositions[j][k] : 0);
					k++;
				}
			}
		}
		printf("\n");
	}
	return 0;
}