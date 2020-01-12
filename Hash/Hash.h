#pragma once
/*
 *	��ϣ��ʵ��
 */

#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                            ������������                                */
/************************************************************************/

typedef char *ElementType;

// �ؼ�������
#define NUM_OF_KEYWORD_TYPE 10
typedef enum keywordType {
    DataTypes,                /*��������=0		*/
    Qualifiers,                /*��������=1		*/
    Userdefined,            /*�û��Զ�������=2	*/
    StorageClasses,            /*����������=3	*/
    Loop,                    /*ѭ��=4			*/
    Decision,                /*ѡ��=5			*/
    Jump,                    /*��ת=6			*/
    Derived,                /*����=7			*/
    Function,                /*����=8			*/
    Others                    /*����=9			*/
} KeywordType;

// �ؼ�����Ϣ�洢
typedef struct keywordInfo {
    char *Keyword;
    int HashKey;
    KeywordType Type;
} KeywordInfo;

// ��ϣ�����ڵ�
typedef struct hashTableNode {
    KeywordInfo *Info;
    int HashKey;
    int Conflict;
    int Position;
} HashTableNode;

// ��ϣ��
typedef struct hashTable {
    HashTableNode **Table;
    int NumOfNodes;
    int Size;
} HashTable;

/************************************************************************/
/*                            ������������                                */
/************************************************************************/

/************************************************************************/
/*                               ����                                    */
/************************************************************************/

int SaveHash(const HashTable *_hash, char *_fileName);

HashTable *ReadHash(char *_fileName);

void WriteHashTable(HashTable *_hash);

int AddNode(ElementType _word, int _type, HashTable *_hash);
HashTableNode *HashSearch(char *_target, HashTable *_hash);
void FreeHash(HashTable* _hash);