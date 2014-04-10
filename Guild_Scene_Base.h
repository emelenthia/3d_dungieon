#pragma once
#include<stdio.h>
#include"Characters.h" //キャラの絵などを表示するため
#include"Party.h" //PTの表示
#include"Colors.h"
#include"Key_Input.h"

class Guild_Scene_Base //ギルドクラスから行ける各画面のクラスの共通型
{
public:
	Guild_Scene_Base();
	~Guild_Scene_Base();
	virtual void Draw();
	virtual int Reaction() = 0;
	int black_h;
	int blue_h;
	int yellow_h;
	int white_h;
	int background_h1;
	char menu_list[20][20]; //行先の一覧
	int list_max; //menu_listの数
	int choose_now;
	char menu_explanation[20][100];
	FILE *fp;
	int choosed_number; //選択した行為
	int str_size_max; //文字列の最大サイズ
	int fscanf_r(char *file_name); //まとめたfscan_s
	Characters *char_pt;
	static int char_ran; //ランダムに表示させている今のキャラの番号。1から
	int char_flag = 1; //キャラの表示フラグ
	Party *party;
};