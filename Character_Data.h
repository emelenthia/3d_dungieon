#pragma once
#include "Character_Data_Save.h"
#include<stdio.h>

class Character_Data : //セーブされないキャラクターの固有データ
	public Character_Data_Save
{
public:
	Character_Data();
	~Character_Data();
	int hp;
	int atk;
	int def;
	int int_s;
	int res;
	int agi;
	FILE *fp_n_s;
	void Load_Char_n_s(char *file_pointer, char *file_pointer_save);
	char file_name_n_s[50]; //ファイル名を覚えておく
	int job_max; //このキャラの職業数
	int char_h[10]; //0から順に、(0+1)の職業の画像
	int char_h_i[10]; //0から順に、(0+1)の職業の画像アイコン
	char char_h_name[10][100]; //0から順に、(0+1)の職業の画像のファイル名
	char char_h_i_name[10][50]; //0から順に、(0+1)の職業の画像アイコンのファイル名
};

