/*
 *	哈希表实现
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Basic/Input.h"
#include "../Basic/Output.h"
#include <string.h>

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

//////////////////////////////////////////////////////////////////////////
///基本属性获取///
//////////////////////////////////////////////////////////////////////////
// 获取key值
int GetHashKey(ElementType _keyword) {
    return ((_keyword[0] - 'a') * 100 + (_keyword[strlen(_keyword) - 1] - 'a')) % 41;
}

// 再散列（二次探测法）
int GetReHashKey(int _existedKey, int _conflict, int _sizeOfHash) {
    /*quadratic probing*/
    int reHash = (_existedKey + (_conflict) * (_conflict) * (_conflict % 2 ? 1 : -1)) % 41;
    return (reHash ? reHash : _sizeOfHash);
}

// 根据数字返回对应枚举类型
KeywordType GetKeywordType(int _type) {
    return (KeywordType) _type;
}

//////////////////////////////////////////////////////////////////////////
///关键字存储///
//////////////////////////////////////////////////////////////////////////

// 存储关键字数据
KeywordInfo *GenerateKeywordInfo(ElementType _keyword, int _type) {
    KeywordInfo *keywordInfo = (KeywordInfo *) malloc(1 * sizeof(KeywordInfo));
    keywordInfo->Keyword = _keyword;
    keywordInfo->Type = GetKeywordType(_type);
    keywordInfo->HashKey = GetHashKey(_keyword);
    return keywordInfo;
}

//////////////////////////////////////////////////////////////////////////
///哈希表节点///
//////////////////////////////////////////////////////////////////////////

// char* ConvertNode2String(const HashTableNode* _node);

void WriteHashNode(HashTableNode *_node) {
    DrawStarLine();
    ShowAttribute_Int("存放位置", _node->Position);
    ShowAttribute_Int("HashID", _node->HashKey);
    ShowIntro("关键词");
    ShowTip(_node->Info->Keyword);
    ShowAttribute_Int("类型", _node->Info->Type);
    ShowAttribute_Int("冲突次数", _node->Conflict);
    DrawStarLine();
    // printf("%s", ConvertNode2String(_node));
}

HashTableNode *GenerateNode(ElementType _keyword, int _type) {
    HashTableNode *node = (HashTableNode *) malloc(1 * sizeof(HashTableNode));
    node->HashKey = GetHashKey(_keyword);
    node->Conflict = 0;
    node->Position = 0;
    node->Info = GenerateKeywordInfo(_keyword, _type);
    return node;
}

//////////////////////////////////////////////////////////////////////////
///哈希表///
//////////////////////////////////////////////////////////////////////////

// char* ConvertHash2String(const HashTable* _hash);
// 遍历哈希表
void WriteHashTable(HashTable *_hash) {
    for (int i = 1; i <= _hash->Size; i++) {
        if (_hash->Table[i]) {
            WriteHashNode(_hash->Table[i]);
        }
    }
    // printf("%s", ConvertHash2String(_hash));
}

// 冲突判断
int IsConflict(ElementType _word, HashTable *_hash) {
    if (_hash->Table[GetHashKey(_word)]) {
        return 1;
    }
    return 0;
}

// 获取元素在哈希表的最终位置，并将元素加入哈希表
int AddNode(ElementType _word, int _type, HashTable *_hash) {
    int conflict = 0;
    int position = GetHashKey(_word);
    while (_hash->Table[position]) {
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

// // 哈希表生成
// HashTable *GenerateHashTable_KEYBOARD(int _size) {
//     HashTable *hash = (HashTable *) malloc(1 * sizeof(HashTable));
//     hash->Size = _size;
//     hash->NumOfNodes = 0;
//     hash->Table = (HashTableNode **) calloc(_size + 1, sizeof(HashTableNode *));
//     for (int i = 0; i < _size; i++) {
//         ShowTip("继续输入？输入0为停止,其他为继续:");
//         if (!ReadContinue())break;
//         ShowTip("请输入关键字:");
//         char *keyword = ReadStr();
//         ShowTip("请输入类型：数据类型=0、类型修饰 = 1、用户自定义类型 = 2、作用域修饰 = 3、循环 = 4、选择 = 5、跳转 = 6、派生 = 7、方法 = 8、其他 = 9");
//         int type = ReadInt();
//         AddNode(keyword, type, hash);
//     }
//     return hash;
// }

// 将一条node信息转换为字符串
char *ConvertNode2String(const HashTableNode *_node) {
    //	{ position,conflict,_hashKey,_keyWord,_type}
    char *string = (char *) calloc(MAXCHAR_NODE, sizeof(char));
    string[0] = '{';
    char tempString[100];
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

// 将一个哈希表信息转换为字符串
char *ConvertHash2String(const HashTable *_hash) {
    //	[ size,numOfNodes,{node1Info},{node2Info},...]
    char *string = (char *) calloc(MAXCHAR_HASH, sizeof(char));
    string[0] = '[';
    char tempString[100];
    strcat(string, itoa(_hash->Size, tempString, 10));
    strcat(string, ",");
    strcat(string, itoa(_hash->NumOfNodes, tempString, 10));
    strcat(string, ",");
    for (int i = 1; i <= _hash->Size; i++) {
        if (_hash->Table[i]) {
            strcat(string, ConvertNode2String(_hash->Table[i]));
        }
    }
    strcat(string, "]");
    return string;
}

// 将哈希表存储为.hash文件
int SaveHash(const HashTable *_hash, char *_fileName) {
    int result = SaveHashFile(ConvertHash2String(_hash), _fileName);
	return result;
}

// 获取.hash中的节点数据并以之生成节点返回
HashTableNode *ConvertString2Node(char *_content) {
    //	{ position,conflict,_hashKey,_keyWord,_type}
    if (_content == NULL) { return NULL; }
    // printf("%s\n", _content);
    _content[strlen(_content) - 1] = '\0';
    int position = atoi(strtok_s(_content, ",", &_content));
    int conflict = atoi(strtok_s(_content, ",", &_content));
    int hashKey = atoi(strtok_s(_content, ",", &_content));
    char *keyWord = strtok_s(_content, ",", &_content);
    int type = atoi(strtok_s(_content, ",", &_content));
    HashTableNode *node = GenerateNode(keyWord, type);
    node->Position = position;
    node->Conflict = conflict;
    node->HashKey = hashKey;
    return node;
}

// 读取.hash文件并将之转换为哈希表
HashTable *ReadHash(char *_fileName) {
    //	[ size,numOfNodes,{node1Info},{node2Info},...]
    //TODO 将position、conflict、hashKey、keyWord、type各读取至数据，再创建哈希表。
    char *file = ReadHashFile(_fileName);
    if (!file) {
        exit(0);
    }
    // printf("%s\n",file);
    strcpy(file, file + 1);
    file[strlen(file) - 1] = '\0';
    char *tempSaver;
    char *temp;
    temp = strtok_s(file, "{", &tempSaver);
    int size = atoi(strtok_s(temp, ",", &temp));
    // printf("%d\n", size);
    int numOfNodes = atoi(strtok_s(temp, ",", &temp));
    // printf("%d\n", numOfNodes);
    HashTable *hash = (HashTable *) malloc(1 * sizeof(HashTable));
    hash->Size = size;
    hash->NumOfNodes = numOfNodes;
    hash->Table = (HashTableNode **) calloc(size + 1, sizeof(HashTableNode *));
    for (int i = 0; i < numOfNodes; i++) {
        HashTableNode *node = ConvertString2Node(strtok_s(tempSaver, "{", &tempSaver));
        if (!node)break;
        hash->Table[node->Position] = node;
    }
    return hash;
}

//哈希查找
HashTableNode *HashSearch(char *_target, HashTable *_hash) {
    int key = GetHashKey(_target);
    int confilc = 0;
    // printf("%s:\n", _target);
    if (key < 1) {
        // printf("404 NOT FOUND\n");
        return NULL;
    }
    while (_hash->Table[key] != NULL && _hash->Table[key]->Info != NULL &&
           strcmpi(_hash->Table[key]->Info->Keyword, _target) != 0) {
        // printf("  at key:%d,compare with %s\n", key, _hash->Table[key]->Info->Keyword);
        key = GetReHashKey(key, ++confilc, _hash->Size);
        if (key < 1) {
            // printf("404 NOT FOUND\n");
            return NULL;
        }
        // printf("  refresh to key:%d\n", key);
    }
    if (_hash->Table[key]) {
        return _hash->Table[key];
    } else {
        // printf("404 NOT FOUND\n");
        return NULL;
    }
}

void FreeHash(HashTable* _hash)
{
	for (int i = 0; i < _hash->Size; i++)
	{
		if(!_hash->Table[i])continue;
		free(_hash->Table[i]);
	}
	free(_hash);
}
