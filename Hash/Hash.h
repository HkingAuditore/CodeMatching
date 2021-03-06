#pragma once
/*
 *	哈希表实现
 */

#include <stdio.h>
#include <stdlib.h>

/************************************************************************/
/*                            所用类型声明                                */
/************************************************************************/

typedef char *ElementType;

// 关键字类型
#define NUM_OF_KEYWORD_TYPE 10
typedef enum keywordType {
    DataTypes,                /*数据类型=0		*/
    Qualifiers,                /*类型修饰=1		*/
    Userdefined,            /*用户自定义类型=2	*/
    StorageClasses,            /*作用域修饰=3	*/
    Loop,                    /*循环=4			*/
    Decision,                /*选择=5			*/
    Jump,                    /*跳转=6			*/
    Derived,                /*派生=7			*/
    Function,                /*方法=8			*/
    Others                    /*其他=9			*/
} KeywordType;

// 关键字信息存储
typedef struct keywordInfo {
    char *Keyword;
    int HashKey;
    KeywordType Type;
} KeywordInfo;

// 哈希表单个节点
typedef struct hashTableNode {
    KeywordInfo *Info;
    int HashKey;
    int Conflict;
    int Position;
} HashTableNode;

// 哈希表
typedef struct hashTable {
    HashTableNode **Table;
    int NumOfNodes;
    int Size;
} HashTable;

/************************************************************************/
/*                            所用类型声明                                */
/************************************************************************/

/************************************************************************/
/*                               方法                                    */
/************************************************************************/

int SaveHash(const HashTable *_hash, char *_fileName);

HashTable *ReadHash(char *_fileName);

void WriteHashTable(HashTable *_hash);

int AddNode(ElementType _word, int _type, HashTable *_hash);
HashTableNode *HashSearch(char *_target, HashTable *_hash);
void FreeHash(HashTable* _hash);