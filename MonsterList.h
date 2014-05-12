#pragma once
#include<stdio.h>

class MonsterList
{
public:
	static MonsterList* instance;
	static MonsterList* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new MonsterList;
		}
		return instance;
	}

	FILE* listfp = NULL; //monsterlist��ǂݍ��ނ��߂̃|�C���^
	int monstermax = 0; //�����X�^�[�̑���
	char monsterlist[1][21]; //n�Ԗڂ̃����X�^�[�̃t�@�C�����̈ꕔ�̃��X�g

private:
	MonsterList();
	~MonsterList();
	MonsterList(const MonsterList& rhs);
	MonsterList& operator=(const MonsterList& rhs);
};

