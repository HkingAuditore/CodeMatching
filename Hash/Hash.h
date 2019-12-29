#pragma once
/*
 *	��ϣ��ʵ��
 */

#include <stdio.h>
#include <stdlib.h>

 /************************************************************************/
 /*                            ������������                                */
 /************************************************************************/

typedef char* ElementType;

// �ؼ�������
typedef enum keywordType {
	DataTypes,				/*��������=0		*/
	Qualifiers,				/*��������=1		*/
	Userdefined,			/*�û��Զ�������=2	*/
	StorageClasses,			/*����������=3	*/
	Loop,					/*ѭ��=4			*/
	Decision,				/*ѡ��=5			*/
	Jump,					/*��ת=6			*/
	Derived,				/*����=7			*/
	Function,				/*����=8			*/
	Others					/*����=9			*/
}KeywordType;

// �ؼ�����Ϣ�洢
typedef struct keywordInfo
{
	char* Keyword;
	int HashKey;
	KeywordType Type;
} KeywordInfo;

// ��ϣ�����ڵ�
typedef struct hashTableNode
{
	KeywordInfo* Info;
	int HashKey;
	int Conflict;
	int Next;
} HashTableNode;

// ��ϣ��
typedef struct hashTable
{
	HashTableNode** Table;
	int NumOfNodes;
} HashTable;

/************************************************************************/
/*                            ������������                                */
/************************************************************************/

/************************************************************************/
/*                               ����                                    */
/************************************************************************/

int SaveHashFile(const HashTable* _hash, char* _fileName);
int ReadHashFile(const HashTable* _hash, char* _fileName);

//************************************
// Method:    �ü������ɹ�ϣ��
// FullName:  GenerateHashTable_KEYBOARD
// Access:    public
// Returns:   HashTable*
// Qualifier:
// Parameter: int _size
//************************************
HashTable* GenerateHashTable_KEYBOARD(int _size);

void WriteHashTable(HashTable* _hash);