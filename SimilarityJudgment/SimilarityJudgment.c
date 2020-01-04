#include <stdio.h>
#include <stdlib.h>

#include "../Vector/Vector.h"
#include "../Matching/Matching.h"

//°Ñ [SearchingResults] ×ª»»Îª [Vector]
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

