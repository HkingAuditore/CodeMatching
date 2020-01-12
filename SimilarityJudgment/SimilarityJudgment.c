#include <stdio.h>
#include <stdlib.h>

#include "../Vector/Vector.h"
#include "../Matching/Matching.h"
#include "../Basic/Output.h"
#include "../Basic/Input.h"
#include <math.h>


//把 [SearchingResults] 转换为 [Vector]
Vector ConvertResult2Vector(SearchingResults* _results)
{
	int* vectorArray = (int*)malloc(_results->NumOfResults * sizeof(int));
	for (int i = 0; i < _results->NumOfResults; i++)
	{
		vectorArray[i] = _results->Results[i] ? _results->Results[i]->NumOfMatch : 0;
	}
	Vector vector = GenerateVector_Array(_results->NumOfResults, vectorArray);
	free(vectorArray);
	return vector;
}

//将每种类型关键字出现的次数进行统计，并转换为[Vector]
Vector GetKeywordsStatistics(SearchingResults* _results,HashTable* _keywordHash)
{
	int* keywordData = (int*)calloc(NUM_OF_KEYWORD_TYPE , sizeof(int));
	for (int i = 0; i < _results->NumOfResults; i++)
	{
		if(!_results->Results[i])continue;
		KeywordType type = _keywordHash->Table[i]->Info->Type;
		if (type > 9 || type <0)continue;
		keywordData[type] += _results->Results[i]->NumOfMatch;
	}
	return GenerateVector_Array(NUM_OF_KEYWORD_TYPE, keywordData);
}


//总相似性判断
double JudgeSimilarity(Vector _keywordVect0, Vector _keywordVect1,Vector _typeVect0,Vector _typeVect1)
{
	
	double keywordDistRatio = GetGeoDistanceRadio(_keywordVect0, _keywordVect1);
	double typeDistRatio = GetGeoDistanceRadio(_typeVect0, _typeVect1);
	//计算两个广义余弦的平均值乘以exp（-0.5|1-几何距离系数|平均值）
	return (GetCOS(_keywordVect0,_keywordVect1) + GetCOS(_typeVect0,_typeVect1))/2.0 * (exp(-0.5*(DoubleAbs(1.0-keywordDistRatio)+DoubleAbs(1.0-typeDistRatio))));
}

//打印最后完整的相似度报表
void WriteSimilarityResult(SearchingResults* _results0, SearchingResults* _results1, HashTable* _keywordHash)
{
	Vector keywordVect0 = ConvertResult2Vector(_results0);
	Vector keywordVect1 = ConvertResult2Vector(_results1);
	double keywordCos = GetCOS(keywordVect0, keywordVect1);
	double keywordDistance = GetGeometricDistance(keywordVect0, keywordVect1);
	Vector typeVect0 = GetKeywordsStatistics(_results0, _keywordHash);
	Vector typeVect1 = GetKeywordsStatistics(_results1, _keywordHash);
	double typeCos = GetCOS(typeVect0, typeVect1);
	double typeDistance = GetGeometricDistance(typeVect0, typeVect1);

	ShowAttribute_Double("对单个关键字的匹配S", keywordCos);
	ShowAttribute_Double("对单个关键字的匹配D", keywordDistance);
	
	ShowAttribute_Double("对类型关键字的匹配S", typeCos);
	ShowAttribute_Double("对类型关键字的匹配D", typeDistance);
	
	ShowAttribute_Double("单个关键字系数", GetGeoDistanceRadio(keywordVect0,keywordVect1));
	ShowAttribute_Double("类型关键字系数", GetGeoDistanceRadio(typeVect0, typeVect1));
	
	ShowAttribute_Double("总相似性判断：", JudgeSimilarity(keywordVect0,keywordVect1,typeVect0,typeVect1));
	
}




//输入两个文件的名字，输出他们的匹配结果
void SimilarityJudgeResult(char* _code0,char* _code1,HashTable* _keywordHash)
{
	Code *code0 = ReadCodeFile(_code0);
	Code *code1 = ReadCodeFile(_code1);

	SearchingResults *result0 = HashTraversal(code0, _keywordHash);
	SearchingResults *result1 = HashTraversal(code1, _keywordHash);


	WriteMatchResults("result0", result0);

	WriteMatchResults("result1", result1);

	WriteSimilarityResult(result0, result1, _keywordHash);
	
	FreeCode(code0);
	FreeCode(code1);
	FreeResults(result0);
	FreeResults(result1);
}