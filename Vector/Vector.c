#include <stdio.h>
#include <stdlib.h>
// #include <cstdarg>
#include <math.h>
#include <stdarg.h>
#include "../Basic/Output.h"

#define ERROR_VECTOR (-99999)

typedef struct vector
{
	int Dimension;
	int* Components;
}Vector;

//��������
Vector GenerateVector(int _dimension, ...)
{
	Vector vector;
	vector.Components = (int*)malloc(_dimension * sizeof(int));
	vector.Dimension = _dimension;
	va_list vl;
	va_start(vl, _dimension);
	for (int i = 0; i < _dimension; i++)
	{
		vector.Components[i] = va_arg(vl, int);
	}
	va_end(vl);
	return vector;
}

//ͨ��������������
Vector GenerateVector_Array(int _dimension, int* _data)
{
	Vector vector;
	vector.Components = (int*)malloc(_dimension * sizeof(int));
	vector.Dimension = _dimension;
	for (int i = 0; i < _dimension; i++)
	{
		vector.Components[i] = _data[i];
	}
	return vector;
}

//�������
double DotProduct(Vector _vect0,Vector _vect1)
{
	if(_vect0.Dimension != _vect1.Dimension)
	{
		return ERROR_VECTOR;
	}
	double result=.0;
	for (int i = 0; i < _vect0.Dimension; i++)
	{
		result += _vect0.Components[i] * _vect1.Components[i];
	}
	return result;
}

//����������ģ
double GetVectorNorm(Vector _vector)
{
	double norm = .0;
	for (int i = 0; i < _vector.Dimension; i++)
	{
		norm += _vector.Components[i] * _vector.Components[i];
	}
	return sqrt(norm);
}

//�����������ƶ�
double GetCOS(Vector _vect0,Vector _vect1)
{
	return (DotProduct(_vect0, _vect1) / (GetVectorNorm(_vect0)*GetVectorNorm(_vect1)));
}

//������������
Vector VectorSubtraction(Vector _vect0,Vector _vect1)
{
	if (_vect0.Dimension != _vect1.Dimension)
	{
		return (Vector){-1,NULL};
	}
	Vector result;
	result.Components = (int*)malloc(_vect0.Dimension * sizeof(int));
	result.Dimension = _vect0.Dimension;

	for (int i = 0; i < _vect0.Dimension; i++)
	{
		result.Components[i] = _vect0.Components[i] - _vect1.Components[i];
	}

	return result;
}
//���������ӷ�
Vector VectorAddition(Vector _vect0,Vector _vect1)
{
	if (_vect0.Dimension != _vect1.Dimension)
	{
		Vector result = {-1,NULL};
		return result;
	}
	Vector result;
	result.Components = (int*)malloc(_vect0.Dimension * sizeof(int));
	result.Dimension = _vect0.Dimension;

	for (int i = 0; i < _vect0.Dimension; i++)
	{
		result.Components[i] = _vect0.Components[i] + _vect1.Components[i];
	}

	return result;
}

//���㼸�ξ���
double GetGeometricDistance(Vector _vect0,Vector _vect1)
{
	return GetVectorNorm(VectorSubtraction(_vect0, _vect1));
}

//�������������
void WriteVector(char* _name,Vector _vector)
{
	ShowArray(_name,_vector.Dimension, _vector.Components);
}

//�ͷ�Vector�ڴ�
void FreeVector(Vector* _vector)
{
	free(_vector->Components);
	free(_vector);
}
//��ȡ����ֵ
double DoubleAbs(double _x)
{
	return _x > 0 ? _x : (-_x);
}

//��ȡ���ξ���ƫ��ϵ�������ξ�����ͬģ�����ξ���ı�ֵ��
double GetGeoDistanceRadio(Vector _vect0, Vector _vect1)
{
	double vectCos = GetCOS(_vect0, _vect1);
	double vect0Norm = GetVectorNorm(_vect0);
	double vect1Norm = GetVectorNorm(_vect1);
	double geoDistance = GetGeometricDistance(_vect0, _vect1);
	double normalDistance = (sqrt(2.0 * vect0Norm*vect0Norm*(1.0 - vectCos)));
	double geoNormalDistance = (sqrt(2.0 * vect1Norm*vect1Norm*(1.0 - vectCos)));
	return normalDistance / geoNormalDistance;
}