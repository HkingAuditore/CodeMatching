#pragma once
#include "../Vector/Vector.h"
#include "../Matching/Matching.h"

//�� [SearchingResults] ת��Ϊ [Vector]
Vector ConvertResult2Vector(SearchingResults* _results);

//��ÿ�����͹ؼ��ֳ��ֵĴ�������ͳ�ƣ���ת��Ϊ[Vector]
Vector GetKeywordsStatistics(SearchingResults* _results, HashTable* _keywordHash);
//��ӡ������������ƶȱ���
void WriteSimilarityResult(SearchingResults* _results0, SearchingResults* _results1, HashTable* _keywordHash);
//���������ļ������֣�������ǵ�ƥ����
void SimilarityJudgeResult(char* _code0, char* _code1, HashTable* _keywordHash);