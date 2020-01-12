#include <stdio.h>
#include <stdlib.h>
#include "Random.h"

#define  DEFAULTMAXNUM 30

//TODOCLAB#0 现在只有对于x的单项式
//TODOCLAB#1 输出多项式没有按次数排序
//TODOCLAB#2 整理算法不够优雅


typedef struct monomial{
	int		Index;
	char	Base;
	int		Coefficient;

}Monomial;



typedef struct polynomial{
	Monomial*	Monos;
	int			Length;

	
}Polynomial;


//生成一单项式
int GenerateMonomial(Monomial* _monamial,int _indexMin,int _indexMax,int _coeMin,int _coeMax)
{
	_monamial->Index = GetRandom(_indexMin, _indexMax);
	_monamial->Base = 'x';
	_monamial->Coefficient = GetRandom(_coeMin, _coeMax);
	return 0;
}

//输出一单项式
int WriteMonomial(Monomial _monamial)
{
	printf("%d%c(%d)", _monamial.Coefficient, _monamial.Base, _monamial.Index);
	return 1;
}


//生成一个多项式
int GeneratePolynomial(Polynomial* _poly,int _numOfMonomials,int _indexMin,int _indexMax,int _coeMin, int _coeMax)
{
	
	_poly->Monos = (Monomial*)malloc(_numOfMonomials*sizeof(Monomial));
	_poly->Length = _numOfMonomials;
	for(int i=0;i<_numOfMonomials;i++)
	{
		GenerateMonomial(&(_poly->Monos[i]), _indexMin, _indexMax,_coeMin,_coeMax);
	}
	return 1;
}

//输出一个多项式
int WritePolynomial(Polynomial _poly)
{
	printf("LENGTH:%d\n", _poly.Length);
	for(int i=0;i<_poly.Length;i++)
	{
		WriteMonomial(_poly.Monos[i]);
		if(i!=_poly.Length-1)
		{
			printf("+");
		}
	}
	printf("\n");
	return 1;
}

//按次数给多项式排序
int SoftPolynomialByIndex(Polynomial _poly)
{
	for (int i = 0; i < _poly.Length; i++)
	{
		for (int j = i; j < _poly.Length; j++)
		{
			if (_poly.Monos[i].Index > _poly.Monos[j].Index)
			{
				Monomial temp;
				temp = _poly.Monos[i], _poly.Monos[i] = _poly.Monos[j], _poly.Monos[j] = temp;
			}
		}
	}
	return 0;
}

//整理多项式
Polynomial* SoftAndCreatePolynomial(Polynomial _poly)
{
	// printf("IN!\n");
	Polynomial* newPoly;
	newPoly = (Polynomial*)calloc(DEFAULTMAXNUM, sizeof(Monomial));
	newPoly->Monos = (Monomial*)calloc(DEFAULTMAXNUM, sizeof(Monomial));
	for(int loopInOrigin=0;loopInOrigin<_poly.Length;loopInOrigin++)
	{
		int temp=1;
		// printf("IN 1ST LOOP!\n");
		for(int loopInNew=0;loopInNew<newPoly->Length;loopInNew++)
		{
			// printf("IN 2ND LOOP!\n");
			if (_poly.Monos[loopInOrigin].Index == newPoly->Monos[loopInNew].Index )
			{
				newPoly->Monos[loopInNew].Coefficient += _poly.Monos[loopInOrigin].Coefficient;
				temp = 0;
				break;
			}	
		}
		newPoly->Monos[newPoly->Length].Index = _poly.Monos[loopInOrigin].Index;
		newPoly->Monos[newPoly->Length].Coefficient = _poly.Monos[loopInOrigin].Coefficient;
		newPoly->Monos[newPoly->Length].Base = _poly.Monos[loopInOrigin].Base;
		newPoly->Length+=temp;
		// printf("soft!");

	}
	SoftPolynomialByIndex(*newPoly);
	return newPoly;
}



int main()
{
	srand((unsigned)time(NULL));
	// Monomial _Mono;
	// for (int i = 0; i < 20; i++) {
	// 	GenerateMonomial(&_Mono, 1, 10);
	// 	WriteMonomial(_Mono);
	// }
	Polynomial test;
	Polynomial* out;
	GeneratePolynomial(&test, 10, 1, 10,1,10);
	WritePolynomial(test);
	out = SoftAndCreatePolynomial(test);
	printf("*********\nSOFT:\n");
	// SoftPolynomialByIndex(*out);
	WritePolynomial(*out);
	free(out);
	
	
}