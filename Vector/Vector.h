#pragma once

typedef struct vector
{
	int Dimension;
	int* Components;
}Vector;

//��������
Vector GenerateVector(int _dimension, ...);
//ͨ��������������
Vector GenerateVector_Array(int _dimension, int* _data);
//���
double DotProduct(Vector _vect0, Vector _vect1);
//��������ģ
double GetVectorNorm(Vector _vector);
//����������������
double GetCOS(Vector _vect0, Vector _vect1);
//��������
Vector VectorSubtraction(Vector _vect0, Vector _vect1);
//�����ӷ�
Vector VectorAddition(Vector _vect0, Vector _vect1);
//�����������ξ���
double GetGeometricDistance(Vector _vect0, Vector _vect1);
//�������
void WriteVector(char* _name, Vector _vector);