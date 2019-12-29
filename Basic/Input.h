#pragma once

#include <stdio.h>
#include <stdlib.h>

#define MAXSTR 100
#define END_OF_READ 0

int ReadInt()
{
	int input;
	scanf("%d", &input);
	return input;
}

char* ReadStr()
{
	char* input = (char*)malloc(MAXSTR * sizeof(char));
	char temp;
	int i = 0;
	while (scanf("%c", &temp) && temp != '\n' && temp != ' ')
	{
		input[i++] = temp;
	}
	input[i] = '\0';
	return input;
}

int ReadContinue()
{
	int input;
	scanf_s("%d", &input);
	if (input != END_OF_READ)
	{
		while (getchar() != '\n') {};
		return 1;
	}
	else
	{
		while (getchar() != '\n') {};
		return 0;
	}
}