#include <stdio.h>
#include <stdlib.h>
#include "../Hash/Hash.h"
#include "../Basic/Output.h"
#include "../Basic/Input.h"
#include "../SimilarityJudgment/SimilarityJudgment.h"

typedef enum choose {
	WriteHash,Compare,Exite
}Choose;

// 用键盘控制哈希表生成，并将它保存
void GenerateHashTable_KEYBOARD(int _size) {
	HashTable *hash = (HashTable *)malloc(1 * sizeof(HashTable));
	hash->Size = _size;
	hash->NumOfNodes = 0;
	hash->Table = (HashTableNode **)calloc(_size + 1, sizeof(HashTableNode *));
	for (int i = 0; i < _size; i++) {
		ShowTip("请输入关键字:");
		char *keyword = ReadStr();
		ShowTip("请输入类型：数据类型=0、类型修饰 = 1、用户自定义类型 = 2、作用域修饰 = 3、循环 = 4、选择 = 5、跳转 = 6、派生 = 7、方法 = 8、其他 = 9");
		int type = ReadInt();
		AddNode(keyword, type, hash);
		ShowTip("继续输入？输入0为停止,其他为继续:");
		if (!ReadContinue())break;
	}
	ShowTip("请输入文件名:");
	char* name = ReadStr();
	// printf("%s\n", name);
	if (SaveHash(hash, name)) {
		ShowTip("保存成功！");
		getchar();
	}else
	{
		ShowTip("保存失败！");
		getchar();
	}
	FreeHash(hash);
}

//选择关键字表
char* ChooseHashFile()
{
	int exist = 0;
	char* name = NULL;
	do
	{
		ShowTip("您想使用的哈希文件是？（不需要后缀名）");
		name = ReadStr();
		exist = IsFileExist(GetHashFilePath(name));
		if (!exist)
		{
			ShowTip("文件找不到，请重新输入");
		}
	} while (!exist);
	return name;
}

//选择要匹配的代码
char* ChooseCodeFile()
{
	int exist=0;
	char* name=NULL;
	do
	{
		ShowTip("您想选择的代码文件名是？（不需要后缀名）");
		name = ReadStr();
		exist = IsFileExist(GetCodeFilePath(name));
		if (!exist)
		{
			ShowTip("文件找不到，请重新输入");
		}
	} while (!exist);
	return name;
	
}

//菜单界面
int Menu()
{
	system("cls");
	DrawStarLine();
	ShowTip("菜单");
	DrawStarLine();
	ShowTip("想输入关键字表，请输入1");
	ShowTip("想匹配代码，请输入2");
	ShowTip("退出程序，请输入0");
	DrawStarLine();
	Choose choose = ReadInt();
	getchar();
	return choose;
}

void Controller(Choose _choose)
{
	switch (_choose)
	{

	case 1:
		GenerateHashTable_KEYBOARD(100);
		break;
	case 2:
		ShowTip("我需要选择两个文件");
		char* code0 = ChooseCodeFile();
		char* code1 = ChooseCodeFile();
		ShowTip("我需要选择一个哈希表");
		char* hashName = ChooseHashFile();
		HashTable* hash = ReadHash(hashName);
		SimilarityJudgeResult(code0, code1, hash);
		ShowTip("按任意键清屏");
		getchar();
		FreeHash(hash);
		break;
	default:
		exit(0);
		break;
	}
}

void MainController()
{
	while (1)
	{
		Controller(Menu());
	}
}
