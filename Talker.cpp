#include "Talker.h"
#include<DxLib.h>
#include"Field.h"
#include"Defines.h"
#include"Key_Input.h"
#include<stdio.h>
#include"Flags.h"
#include"Events.h"

Talker::Talker()
{
	Flags::talkflag = 0;
	talkpage = 0;
	boxcolor = GetColor(0, 0, 255);
	talkcolor = GetColor(255, 0, 0);
	fp = NULL; //これしないと落ちる
	chooseflag = 0;
	choosenumber = 0;
	event_number = 0;
	strcpy(file_name, "null"); //適当な初期値
	
}


Talker::~Talker()
{
	if (fp != NULL) //チェックしないと落ちる
	{
		fclose(fp);
	}
}


void Talker::Draw()
{
	//本体の表示
	if (hundle_number != -1) //-1は透明な画像
	{
		DrawGraph(pos_x - Field::left_upper_x, pos_y - Field::left_upper_y, hundle_number, TRUE); //画面がずれた時にきちんとずれる様に
	}

	//当たり判定の表示
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透明化
	DrawBox(pos_x_lu - Field::left_upper_x, pos_y_lu - Field::left_upper_y, pos_x_rd - Field::left_upper_x, pos_y_rd - Field::left_upper_y, GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

	//台詞の表示
	if (Flags::talkflag && talkpage)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透過
		DrawBox(0, 240, 640, 480, boxcolor, TRUE); //台詞欄
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

		if (talkpage == talkmax && chooseflag) //選択肢が有る場合
		{
			for (int i = 0; i < choosemax; i++)
			{
				DrawFormatString(40, 300 + i * 20, talkcolor, "%s", choose_mean[i]);
			}
		}
		else
		{
			DrawFormatString(40, 320, talkcolor, "%s", talk_mean[talkpage - 1]); //台詞
		}
	}
	
	//矢印の表示
	if (chooseflag)
	{
		DrawString(20, 280 + choosenumber * 20, "->", talkcolor);
	}


}


int Talker::Reaction()
{
	int r = 0;
	if (((Players::real_pos_x + Players::pos_x_lu <= pos_x_rd) &&
		(Players::real_pos_x + Players::pos_x_rd >= pos_x_lu) &&
		(Players::real_pos_y + Players::pos_y_lu <= pos_y_rd) &&
		(Players::real_pos_y + Players::pos_y_rd >= pos_y_lu)) //このオブジェクトに重なったら
		&& ((Players::direction == 0 && Players::real_pos_y + Players::pos_y_rd <= pos_y_lu) //下を向いている
		||  (Players::direction == 1 && Players::real_pos_x + Players::pos_x_lu >= pos_x_rd) //左を向いている
		||  (Players::direction == 2 && Players::real_pos_x + Players::pos_x_rd <= pos_x_lu) //右を向いている
		||  (Players::direction == 3 && Players::real_pos_y + Players::pos_y_lu >= pos_y_rd)) //上を向いている
		&&  ((Key_Input::buff_time[KEY_INPUT_Z]) == 1) //Zボタンを押した瞬間
		&&  (!Flags::menuflag)) //スマホしながらではない
	{
		r = 1;
		if (talkpage != talkmax)
		{
			Flags::talkflag = 1;
			talkpage++;
		}
		else
		{
			if (chooseflag || !choosemax || choosemax == -1) //選択肢がない場合。もしくは選択肢が終わった場合
			{
				if (choosemax == -1) //既定路線の場合
				{
					if (fp != NULL)
					{
						fclose(fp);
					}
					talkpage = change_pattern - 1;
					Flags::talkflag = talkpage;
					LoadTalk(choose_file_name[0]); //次の台詞の読み込み
					choosenumber = 0;
					chooseflag = 0;
				}
				else
				{
					if (choosenumber) //選択肢を選んだ場合
					{
						if (fp != NULL)
						{
							fclose(fp);
						}
						talkpage = change_pattern - 1;
						Flags::talkflag = talkpage;
						LoadTalk(choose_file_name[choosenumber - 1]); //次の台詞の読み込み
						choosenumber = 0;
						chooseflag = 0;
					}
					else
					{
						events_t->ev_act(event_number); //最後にイベントの呼び出し
						Flags::talkflag = 0;//リセット。
						talkpage = 0;
						chooseflag = 0;
						choosenumber = 0;
					}
				}
			}
			else
			{
				chooseflag = 1;
				if (!choosenumber)
				{
					choosenumber++; //番号の割り振りを分かりやすく
				}
			}
		}
	}

	if (Key_Input::buff_time[KEY_INPUT_R] == 1) //再読み込み
	{
		if (fp != NULL)
		{
			fclose(fp);
			LoadTalk(file_name);
		}
	}

	if (chooseflag) //選択肢の選択
	{
		if (Key_Input::buff_time[KEY_INPUT_UP] == 1) //上ボタン
		{
			if (choosenumber > 1)
			{
				choosenumber--;
			}
		}
		if (Key_Input::buff_time[KEY_INPUT_DOWN] == 1) //下ボタン
		{
			if (choosenumber < choosemax)
			{
				choosenumber++;
			}
		}

	}
	return r;
}


void Talker::LoadTalk(char file_pointer[40])
{
	if (!(strcmp(file_name, "null")))
	{
		strcpy(file_name, file_pointer); //元のファイル名を覚えておく。ゲーム自体には意味がない
	}
	fp = fopen(file_pointer,"r"); //指定されたファイルを開く
	
	if (fp == NULL) //エラー処理
	{
		DrawString(10, 10, "Error", GetColor(255, 0, 0));
		WaitKey();
		DxLib_End();				// ＤＸライブラリ使用の終了処理
		exit(1);
	}

	fscanf(fp, "%d", &talkmax); //必要な情報のロード
	for (int i = 0; i < talkmax ; i++)
	{
		fscanf_s(fp, "%s", talk_mean[i],79);
	}
	fscanf(fp, "%d", &choosemax);
	for (int i = 0; i < choosemax; i++)
	{
		fscanf_s(fp, "%s", choose_mean[i],79);
	}
	for (int i = 0; i < choosemax; i++)
	{
		fscanf_s(fp, "%s", choose_file_name[i],39);
	}
	if (choosemax == -1)
	{
		fscanf_s(fp, "%s", choose_file_name[0],39);
	}
	if (choosemax)
	{
		fscanf(fp, "%d", &change_pattern);
	}
	fscanf(fp, "%d", &event_number);
}