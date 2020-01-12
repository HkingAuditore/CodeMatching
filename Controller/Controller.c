#include <stdio.h>
#include <stdlib.h>
#include "../Hash/Hash.h"
#include "../Basic/Output.h"
#include "../Basic/Input.h"
#include "../SimilarityJudgment/SimilarityJudgment.h"

typedef enum choose {
	WriteHash,Compare,Exite
}Choose;

// �ü��̿��ƹ�ϣ�����ɣ�����������
void GenerateHashTable_KEYBOARD(int _size) {
	HashTable *hash = (HashTable *)malloc(1 * sizeof(HashTable));
	hash->Size = _size;
	hash->NumOfNodes = 0;
	hash->Table = (HashTableNode **)calloc(_size + 1, sizeof(HashTableNode *));
	for (int i = 0; i < _size; i++) {
		ShowTip("������ؼ���:");
		char *keyword = ReadStr();
		ShowTip("���������ͣ���������=0���������� = 1���û��Զ������� = 2������������ = 3��ѭ�� = 4��ѡ�� = 5����ת = 6������ = 7������ = 8������ = 9");
		int type = ReadInt();
		AddNode(keyword, type, hash);
		ShowTip("�������룿����0Ϊֹͣ,����Ϊ����:");
		if (!ReadContinue())break;
	}
	ShowTip("�������ļ���:");
	char* name = ReadStr();
	// printf("%s\n", name);
	if (SaveHash(hash, name)) {
		ShowTip("����ɹ���");
		getchar();
	}else
	{
		ShowTip("����ʧ�ܣ�");
		getchar();
	}
	FreeHash(hash);
}

//ѡ��ؼ��ֱ�
char* ChooseHashFile()
{
	int exist = 0;
	char* name = NULL;
	do
	{
		ShowTip("����ʹ�õĹ�ϣ�ļ��ǣ�������Ҫ��׺����");
		name = ReadStr();
		exist = IsFileExist(GetHashFilePath(name));
		if (!exist)
		{
			ShowTip("�ļ��Ҳ���������������");
		}
	} while (!exist);
	return name;
}

//ѡ��Ҫƥ��Ĵ���
char* ChooseCodeFile()
{
	int exist=0;
	char* name=NULL;
	do
	{
		ShowTip("����ѡ��Ĵ����ļ����ǣ�������Ҫ��׺����");
		name = ReadStr();
		exist = IsFileExist(GetCodeFilePath(name));
		if (!exist)
		{
			ShowTip("�ļ��Ҳ���������������");
		}
	} while (!exist);
	return name;
	
}

//�˵�����
int Menu()
{
	system("cls");
	DrawStarLine();
	ShowTip("�˵�");
	DrawStarLine();
	ShowTip("������ؼ��ֱ�������1");
	ShowTip("��ƥ����룬������2");
	ShowTip("�˳�����������0");
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
		ShowTip("����Ҫѡ�������ļ�");
		char* code0 = ChooseCodeFile();
		char* code1 = ChooseCodeFile();
		ShowTip("����Ҫѡ��һ����ϣ��");
		char* hashName = ChooseHashFile();
		HashTable* hash = ReadHash(hashName);
		SimilarityJudgeResult(code0, code1, hash);
		ShowTip("�����������");
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
