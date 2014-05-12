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

	FILE* listfp = NULL; //monsterlistを読み込むためのポインタ
	int monstermax = 0; //モンスターの総数
	char monsterlist[1][21]; //n番目のモンスターのファイル名の一部のリスト

private:
	MonsterList();
	~MonsterList();
	MonsterList(const MonsterList& rhs);
	MonsterList& operator=(const MonsterList& rhs);
};

