#include <stdio.h>
#include <stdlib.h>
#include "Matching/Matching.h"
#include "Basic/Input.h"

int main()
{
	// HashTable* hash = GenerateHashTable_KEYBOARD(43);

	// SaveHash(hash, "myHash");
	HashTable* hash = ReadHash("myHash");
	// printf("num:%d\n", hash->NumOfNodes);

	// WriteHashTable(hash);
	Code* code = ReadCodeFile("test");
	// for (int i = 0; i < code->NumOfLine; i++)
	// {
	// 	printf("%s", code->Content[i]);
	// }
	SearchingResults* result = HashTraversal(code, hash);
	WriteMatchResults(result);
	getchar();
}