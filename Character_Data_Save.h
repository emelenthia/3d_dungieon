#pragma once
#include<stdio.h>

class Character_Data_Save //セーブされる各キャラの可変データ
{
public:
	Character_Data_Save();
	~Character_Data_Save();
	int exp; //
	char name[21];
	int job;
	bool in_team; //加入フラグ。1なら加入
	FILE *fp;
	void Load_Char(char *file_pointer);
	char file_name[50]; //ファイル名を覚えておく
};

