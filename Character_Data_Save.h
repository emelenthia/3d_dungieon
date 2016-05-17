#pragma once
#include<stdio.h>
#include"Status.h"
#include"Defines.h"
#include"Colors.h"
#include"Skill.h"
#include"Ailment.h"

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
	//スキル関係
	char m_canSkillLevel[CHARA_MAX][SKILL_MAX_PT]; //各キャラのスキル取得レベル。0なら取得していない
	void DrawSkill(int chara, int mode, int pos_x, int pos_y, int choose); //指定されたキャラのスキル一覧を表示します。charaはキャラ番号を指定。modeは使用場面によって選択、上のdefineを参照pos_xとpos_yは左上の座標。chooseは今選ばれているスキル
	char GetCanSkillNum(int chara,int mode = -1); //現在使用できるスキルの総数を取得して返す。modeも指定可能。指定しない場合は全てのスキル対象
	int GetSkillNumber(int chara, int number, int mode = -1); //指定されたcharaの指定されたmodeで上からnumber個目のスキル番号を取得
	//状態異常関係
	int ailment_turn[CHARA_MAX][Defines::AILMENT_MAX]; //各状態異常の残りターン。原理的に残りターンが1以上の状態異常にかかっていることになる
	int ailment_walks[CHARA_MAX][Defines::AILMENT_MAX]; //各状態異常の残り歩数。歩いて治らないものは-1で示す
	
private:
	Skill* m_skill;
	Ailment* m_ailment;
	char m_canSkillNum[CHARA_MAX]; //各キャラの取得スキル数
};