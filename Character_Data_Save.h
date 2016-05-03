#pragma once
#include<stdio.h>
#include"Status.h"
#include"Defines.h"


class Character_Data_Save //セーブされる各キャラの可変データ
{
public:
	Character_Data_Save();
	~Character_Data_Save();
	int exp[CHARA_MAX]; //
	int Lv[CHARA_MAX];
	char name[CHARA_MAX][21];
	int job[CHARA_MAX];
	int in_team[CHARA_MAX]; //加入フラグ。1なら加入
	FILE *fp[CHARA_MAX];
	void Load_Char(char *file_pointer,int n);
	//int nowhp[15]; //現在の残りHP
	//int nowtp[15]; //現在の残りTP
	status_c status_c[CHARA_MAX - 1]; //現在の可変ステータス
	
	char file_name[CHARA_MAX][50]; //ファイル名を覚えておく
	int in_party[CHARA_MAX]; //編成に入ってるフラグ。1なら入ってます
	int lastchoosef[CHARA_MAX]; //戦闘に対して最後に行った行動
	int lastchoosef_skill[CHARA_MAX]; //最後に使用したスキル
	char m_canSkillLevel[CHARA_MAX][SKILL_MAX_PT]; //各キャラのスキル取得レベル。0なら取得していない
};