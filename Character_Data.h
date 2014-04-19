#pragma once
#include "Character_Data_Save.h"
#include<stdio.h>

class Character_Data : //セーブされないキャラクターの固有データ
	public Character_Data_Save
{
public:
	Character_Data();
	~Character_Data();
	int GetStatus(int n, int want); //n番目のキャラのwant(1=atk,2=def,3=int,4=res,5=dex,6=agi,7=hp,8=tp,9=斬,10=突,11=欧,12=火,13=水,14=風,15=土,16=雷)を取得する
	char* GetJobName(int n); //n番目のキャラの現在のクラスの名前を返す
	char* GetJobNameabb(int n); //n番目のキャラの現在のクラスの名前の省略形を返す
	
	FILE *fp_n_s[15];
	void Load_Char_n_s(char *file_pointer, char *file_pointer_save,int n);
	char file_name_n_s[15][50]; //ファイル名を覚えておく
	int job_system[15]; //このキャラの職業の系統
	int char_h[15][10]; //0から順に、(0+1)の職業の画像
	int char_h_i[15][10]; //0から順に、(0+1)の職業の画像アイコン(普段表示される小さい画像)
	char char_h_name[15][10][100]; //0から順に、(0+1)の職業の画像のファイル名
	char char_h_i_name[15][10][50]; //0から順に、(0+1)の職業の画像アイコンのファイル名
};

