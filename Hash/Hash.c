/*
 *	��ϣ��ʵ��
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Basic/Input.h"
#include "../Basic/Output.h"
#include <string.h>

#define MAXCHAR_NODE 100
#define MAXCHAR_HASH 1000

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
	function,				/*����=8			*/
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
	int Position;
} HashTableNode;

// ��ϣ��
typedef struct hashTable
{
	HashTableNode** Table;
	int NumOfNodes;
	int Size;
} HashTable;

/************************************************************************/
/*                            ������������                                */
/************************************************************************/

/************************************************************************/
/*                               ����                                    */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
///�������Ի�ȡ///
//////////////////////////////////////////////////////////////////////////
// ��ȡkeyֵ
int GetHashKey(ElementType _keyword)
{
	return((_keyword[0] - 'a') * 100 + (_keyword[strlen(_keyword) - 1] - 'a')) % 41;
}

// �������ַ��ض�Ӧö������
KeywordType GetKeywordType(int _type)
{
	return (KeywordType)_type;
}

//////////////////////////////////////////////////////////////////////////
///�ؼ��ִ洢///
//////////////////////////////////////////////////////////////////////////

// �洢�ؼ�������
KeywordInfo* GenerateKeywordInfo(ElementType _keyword, int _type)
{
	KeywordInfo* keywordInfo = (KeywordInfo*)malloc(1 * sizeof(KeywordInfo));
	keywordInfo->Keyword = _keyword;
	keywordInfo->Type = GetKeywordType(_type);
	keywordInfo->HashKey = GetHashKey(_keyword);
	return keywordInfo;
}

//////////////////////////////////////////////////////////////////////////
///��ϣ��ڵ�///
//////////////////////////////////////////////////////////////////////////

// char* ConvertNode2String(const HashTableNode* _node);

void WriteHashNode(HashTableNode* _node)
{
	DrawLine();
	ShowAttribute("���λ��", _node->Position);
	ShowAttribute("HashID", _node->HashKey);
	ShowIntro("�ؼ���");
	ShowLine(_node->Info->Keyword);
	ShowAttribute("����", _node->Info->Type);
	ShowAttribute("��ͻ����", _node->Conflict);
	DrawLine();
	// printf("%s", ConvertNode2String(_node));
}

HashTableNode* GenerateNode(ElementType _keyword, int _type)
{
	HashTableNode* node = (HashTableNode*)malloc(1 * sizeof(HashTableNode));
	node->HashKey = GetHashKey(_keyword);
	node->Conflict = 0;
	node->Position = 0;
	node->Info = GenerateKeywordInfo(_keyword, _type);
	return node;
}

//////////////////////////////////////////////////////////////////////////
///��ϣ��///
//////////////////////////////////////////////////////////////////////////

// char* ConvertHash2String(const HashTable* _hash);
// ������ϣ��
void WriteHashTable(HashTable* _hash)
{
	for (int i = 1; i <= _hash->Size; i++)
	{
		if (_hash->Table[i])
		{
			WriteHashNode(_hash->Table[i]);
		}
	}
	// printf("%s", ConvertHash2String(_hash));
}

// ��ͻ�ж�
int IsConflict(ElementType _word, HashTable* _hash)
{
	if (_hash->Table[GetHashKey(_word)])
	{
		return 1;
	}
	return 0;
}

// ��ɢ�У�����̽�ⷨ��
int GetReHashKey(int _existedKey, int _conflict, int _sizeOfHash)
{
	/*quadratic probing*/
	int reHash = (_existedKey + (_conflict)*(_conflict)*(_conflict % 2 ? 1 : -1)) % 41;
	return (reHash ? reHash : _sizeOfHash);
}

// ��ȡԪ���ڹ�ϣ�������λ�ã�����Ԫ�ؼ����ϣ��
int AddNode(ElementType _word, int _type, HashTable* _hash)
{
	int conflict = 0;
	int position = GetHashKey(_word);
	while (_hash->Table[position])
	{
		position = GetReHashKey(position, ++conflict, _hash->Size);
	}
	_hash->Table[position] = GenerateNode(_word, _type);
	// printf("insert!\n");
	_hash->Table[position]->Conflict = conflict;
	// printf("conflict:%d!\n",_hash->Table[position]->Conflict);
	_hash->Table[position]->Position = position;
	// printf("position:%d!\n", _hash->Table[position]->Position);
	_hash->NumOfNodes++;

	return position;
}

// ��ϣ������
HashTable* GenerateHashTable_KEYBOARD(int _size)
{
	HashTable* hash = (HashTable*)malloc(1 * sizeof(HashTable));
	hash->Size = _size;
	hash->NumOfNodes = 0;
	hash->Table = (HashTableNode**)calloc(_size + 1, sizeof(HashTableNode*));
	for (int i = 0; i < _size; i++)
	{
		ShowLine("�������룿����0Ϊֹͣ,����Ϊ����:");
		if (!ReadContinue())break;
		ShowLine("������ؼ���:");
		char * keyword = ReadStr();
		ShowLine("���������ͣ���������=0���������� = 1���û��Զ������� = 2������������ = 3��ѭ�� = 4��ѡ�� = 5����ת = 6������ = 7������ = 8������ = 9");
		int type = ReadInt();
		AddNode(keyword, type, hash);
	}
	return hash;
}

// ��һ��node��Ϣת��Ϊ�ַ���
char* ConvertNode2String(const HashTableNode* _node)
{
	//	{ position,conflict,_hashKey,_keyWord,_type}
	char* string = (char*)calloc(MAXCHAR_NODE,sizeof(char));
	string[0] = '{';
	char tempString[10];
	strcat(string, itoa(_node->Position, tempString, 10));
	strcat(string, ",");
	strcat(string, itoa(_node->Conflict, tempString, 10));
	strcat(string, ",");
	strcat(string, itoa(_node->HashKey, tempString, 10));
	strcat(string, ",");
	strcat(string, _node->Info->Keyword);
	strcat(string, ",");
	strcat(string, itoa(_node->Info->Type, tempString, 10));
	strcat(string, "}");
	return string;
}
// ��һ����ϣ����Ϣת��Ϊ�ַ���
char* ConvertHash2String(const HashTable* _hash)
{
	//	{ position,conflict,_hashKey,_keyWord,_type}
	char* string = (char*)calloc(MAXCHAR_HASH,sizeof(char));
	string[0] = '[';
	char tempString[10];
	strcat(string, itoa(_hash->Size, tempString, 10));
	strcat(string, ",");
	strcat(string, itoa(_hash->NumOfNodes, tempString, 10));
	strcat(string, ",");
	for (int i = 1; i <= _hash->Size; i++)
	{
		if (_hash->Table[i])
		{
			strcat(string, ConvertNode2String(_hash->Table[i]));
		}
	}
	strcat(string, "]");
	return string;
}


// ����ϣ��洢Ϊconfig�ļ�
int SaveHashFile(const HashTable* _hash,char* _fileName)
{
	SaveHash(ConvertHash2String(_hash), _fileName);
}

// ��ȡconfig�ļ�����֮ת��Ϊ��ϣ��
int ReadHashFile(const HashTable* _hash, char* _fileName)
{
	
}