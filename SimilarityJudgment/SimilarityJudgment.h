#pragma once
#include "../Vector/Vector.h"
#include "../Matching/Matching.h"

//把 [SearchingResults] 转换为 [Vector]
Vector ConvertResult2Vector(SearchingResults* _results);

//将每种类型关键字出现的次数进行统计，并转换为[Vector]
Vector GetKeywordsStatistics(SearchingResults* _results, HashTable* _keywordHash);
//打印最后完整的相似度报表
void WriteSimilarityResult(SearchingResults* _results0, SearchingResults* _results1, HashTable* _keywordHash);
//输入两个文件的名字，输出他们的匹配结果
void SimilarityJudgeResult(char* _code0, char* _code1, HashTable* _keywordHash);