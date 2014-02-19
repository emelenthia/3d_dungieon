#pragma once
#include "Objects.h"
#include<stdio.h>
#include"Events.h"

class Talker :
	public Objects
{
public:
	Talker();
	~Talker();
	void talk_set(); //返答内容をセットする
	FILE *fp;
	void Draw(); //オーバーライド
	int talkmax; //会話のページ数
	char talk_mean[10][80]; //返答内容。とりあえず80文字まで
	int choosemax; //選択肢数
	char choose_mean[10][80]; //選択肢の内容。とりあえず80文字まで
	virtual int Reaction(); //オーバーライド&仮想関数
	void LoadTalk(char file_pointer[40]); //台詞のロード
	int boxcolor; //台詞欄の色のハンドル
	int talkcolor; //台詞の色
	int talkpage; //台詞のページ数
	char file_name[40];
	int chooseflag; //選択肢中のフラグ
	int choosenumber; //選択肢に対する矢印の位置
	char choose_file_name[5][40]; //各選択肢に対する返答のファイル
	int change_pattern; //会話を変える際に休憩をはさむなら2、そうでないなら1
	Events *events_t = Events::GetInstance();
	int event_number; //呼び出すイベント
};

