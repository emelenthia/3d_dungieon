#pragma once
#include"DxLib.h"
#include"Characters.h" //キャラの絵などを表示するため
#include"Options.h"
#include"Guild_PT.h"
#include"Character_Show.h"
#include"Key_Input.h"

//基本的にGuild_Mainを流用…というか、ちゃんと作ってこれをGuild_Mainとかで使いまわすべきだよね
class Camp
{
public:
	Camp();
	~Camp();

	void Draw();
	int Reaction();

private:
	int str_size_max; //文字列の最大の大きさ(描画の)
	bool m_char_flag;
	Characters *char_pt;
	int char_ran; //ランダムに表示させている今のキャラの番号。1から
	Options *m_options;
	Guild_PT *guild_pt;
	int list_max; //menu_listの数
	Party *m_party;
	int m_choose_now;
	char m_menu_explanation[20][100];
	char m_menu_list[20][20]; //行先の一覧
	Character_Show *m_character_show;
	int choosed_number; //選択した行為
	int fscanf_r(char *file_name); //まとめたfscan_s
	bool m_1f_flag; //1F目の行動であることを示したい(キャンプから入ってきた瞬間にキャンプボタンで抜けないように)
	typedef enum camp_list_ //こういう番号指定って後で直しにくいからよくなさ気だけど(直接ソースに書いてるからRPGエディタみたいに出来ない)…
	{
		BAG = 0,
		EQUIP,
		CSUTOM,
		STATES,
		QUEST,
		OTHER,
		SAVE,
		LOAD,
		OPTION,
		TITLE,
		CLOSE
	}camp_list;
	/*
	
#include"Party.h" //PTの表示

class Guild_Scene_Base //ギルドクラスから行ける各画面のクラスの共通型
{
public:
	virtual void Draw();
	virtual int Reaction() = 0;
	int background_h1;
	FILE *fp;
	int str_size_max; //文字列の最大サイズ
	int char_flag = 1; //キャラの表示フラグ
	*/
};

