#pragma once
#include<stdio.h>
class SaveData
{
	/*static SaveData* instance;
	//// �B��̃A�N�Z�X�o�H
	static SaveData* GetInstance()
	{
		if (instance == NULL)instance = new SaveData();
		return instance;
	}*/

public:
	static SaveData* instance;
	// �B��̃A�N�Z�X�o�H
	static SaveData* GetInstance()
	{
	if (instance == NULL)instance = new SaveData();
	return instance;
	}

	int map_open_flag[10][10][10]; //n�ڂ̃}�b�v��(l,m)�͍s�������ǂ���
	FILE *fp;
	int x_max[10];
	int z_max[10];
	int nummap;
	void Save();
private:
	// ������R�s�[���֎~����
	SaveData();
	SaveData(const SaveData& rhs);
	SaveData& operator=(const SaveData& rhs);
	~SaveData();
};

