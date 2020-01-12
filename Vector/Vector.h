#pragma once

typedef struct vector
{
	int Dimension;
	int* Components;
}Vector;

//生成向量
Vector GenerateVector(int _dimension, ...);
//通过数组生成向量
Vector GenerateVector_Array(int _dimension, int* _data);
//点乘
double DotProduct(Vector _vect0, Vector _vect1);
//计算向量模
double GetVectorNorm(Vector _vector);
//计算向量广义余弦
double GetCOS(Vector _vect0, Vector _vect1);
//向量减法
Vector VectorSubtraction(Vector _vect0, Vector _vect1);
//向量加法
Vector VectorAddition(Vector _vect0, Vector _vect1);
//计算向量几何距离
double GetGeometricDistance(Vector _vect0, Vector _vect1);
//输出向量
void WriteVector(char* _name, Vector _vector);
//释放向量内存
void FreeVector(Vector* _vector);
double DoubleAbs(double _x);
double GetGeoDistanceRadio(Vector _vect0, Vector _vect1);