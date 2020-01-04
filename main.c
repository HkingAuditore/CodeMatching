#include <stdio.h>
#include <stdlib.h>
#include "Matching/Matching.h"
#include "Basic/Input.h"
#include "SimilarityJudgment/SimilarityJudgment.h"
#include "Vector/Vector.h"
#include "Basic/Output.h"

int main() {
    // HashTable* hash = GenerateHashTable_KEYBOARD(43);

    // SaveHash(hash, "myHash");
    HashTable *hash = ReadHash("myHash");
	// printf("num:%d\n", hash->NumOfNodes);

    // WriteHashTable(hash);
	
    Code *code0 = ReadCodeFile("test");
	Code *code1 = ReadCodeFile("test1");
	
    // for (int i = 0; i < code->NumOfLine; i++)
    // {
    // 	printf("%s", code->Content[i]);
    // }
    // 
    SearchingResults *result0 = HashTraversal(code0, hash);
	SearchingResults *result1 = HashTraversal(code1, hash);
	
    // WriteMatchResults(result);
	Vector vect0 = ConvertResult2Vector(result0);
	Vector vect1 = ConvertResult2Vector(result1);
	
	WriteVector("result0",vect0);
	WriteVector("result1", vect1);

	ShowAttribute_Double("cos", GetCOS(vect0, vect1));
	ShowAttribute_Double("distance", GetGeometricDistance(vect0, vect1));
	
    getchar();
}
