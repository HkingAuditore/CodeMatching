#include <stdio.h>
#include <stdlib.h>
#include "Hash/Hash.h"

int main()
{
	HashTable* hash = GenerateHashTable_KEYBOARD(43);
	WriteHashTable(hash);
	SaveHashFile(hash, "myHash");
	getchar();
}