#pragma once
#include<stdio.h>

class Character_Data_Save //セーブされる各キャラの可変データ
{
public:
	Character_Data_Save();
	~Character_Data_Save();
	int exp[15]; //
	int Lv[15];
	char name[15][21];
	int job[15];
	int in_team[15]; //加入フラグ。1なら加入
	FILE *fp[15];
	void Load_Char(char *file_pointer,int n);
	int nowhp[15]; //現在の残りHP
	int nowtp[15]; //現在の残りTP
	char file_name[15][50]; //ファイル名を覚えておく
	int in_party[15]; //編成に入ってるフラグ。1なら入ってます
};