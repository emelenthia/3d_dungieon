#include "Guild_Main.h"
#include"DxLib.h"
#include"Flags.h"
#include"Key_Input.h"
#include"SaveData.h"
//#include"Character_Show.h"

Guild_Main::Guild_Main()
{
	fscanf_r("./scn/guild/guild_main_list.cns");
	choosed_number = -1;
	choose_now = 0;
	savedata = SaveData::GetInstance();
	options = Options::GetInstance();
	guild_pt = new Guild_PT;
	character_show = NULL;
}


Guild_Main::~Guild_Main()
{
	if (character_show != NULL)
	{
		delete character_show;
	}
	delete guild_pt;
}


void Guild_Main::Draw()
{
		int temp_size_x = str_size_max + 36;

		DrawExtendGraph(0, 0, 640, 480, background_h1, TRUE); //背景
		if (char_flag)
		{
			DrawRotaGraph(480, 240, 0.7, 0, char_pt->char_h[char_ran][char_pt->job[char_ran] - 1], TRUE);
		}

		if (!(options->optionflag || Flags::character_show_flag || guild_pt->guild_pt_flag)) //オプション等表示中でない
		{
			DrawBox(2 + temp_size_x, 39, 4 + temp_size_x, list_max * 20 + 42, yellow_h, TRUE); //台詞欄の周り右
			DrawBox(18, 39, 20, list_max * 20 + 42, yellow_h, TRUE); //台詞欄の周り左
			DrawBox(19, 38, 4 + temp_size_x, 40, yellow_h, TRUE); //台詞欄の周り上
			DrawBox(19, list_max * 20 + 41, 4 + temp_size_x, list_max * 20 + 43, yellow_h, TRUE); //台詞欄の周り下

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透過
			DrawBox(20, 40, 2 + temp_size_x, list_max * 20 + 40, black_h, TRUE); //台詞欄
			DrawBox(0, 0, 640, 20, blue_h, TRUE); //説明欄
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

			DrawBox(21, 41 + choose_now * 20, 1 + temp_size_x, 60 + choose_now * 20, yellow_h, TRUE); //選択中のを示す
			DrawFormatString(22, 2, white_h, "%s", menu_explanation[choose_now], TRUE); //説明しよう

			for (int i = 0; i < list_max; i++)
			{
				DrawFormatString(22, 42 + i * 20, (choose_now == i ? black_h : white_h), " %s", menu_list[i]); //選ばれたのは、黒でした
			}

			//パーティの描画
			party->Draw();
		}
		else if (options->optionflag)
		{
			options->Draw();
		}
		else if (Flags::character_show_flag)
		{
			character_show->Draw();
		}
		else if (guild_pt->guild_pt_flag)
		{
			guild_pt->Draw();
		}
}


int Guild_Main::Reaction()
{
	choosed_number = 0;
	if (!(options->optionflag || Flags::character_show_flag || guild_pt->guild_pt_flag))
	{
		if (Flags::nowscene == 0x8011d && Flags::guild_now == 2)
		{
			if (Key_Input::buff_time[KEY_INPUT_X] == 1)
			{
				choosed_number = 1;
			}
			else if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
			{
				choosed_number = choose_now + 201;//2-(n+1)
			}
		}

		if (choosed_number == 211)
		{
			savedata->Save();
		}
		if (choosed_number == 213)
		{
			options->optionflag++;
		}
		if (choosed_number == 207)
		{
			Flags::character_show_flag++;
			character_show = new Character_Show;
		}
		if (choosed_number == 202)
		{
			guild_pt->guild_pt_flag++;
		}

		if (Flags::nowscene == 0x8011d && Flags::guild_now == 2) //メニューを選択する
		{
			if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_UP] != 11)
			{
				choose_now = (choose_now > 0 ? choose_now - 1 : list_max - 1); //ループできるように
			}
			if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_DOWN] != 11)
			{
				choose_now = (choose_now < list_max - 1 ? choose_now + 1 : 0);
			}
		}
	}
	else if (options->optionflag)
	{
		options->Reaction();
	}
	else if (Flags::character_show_flag)
	{
		character_show->Reaction();
		if (Key_Input::buff_time[KEY_INPUT_X] == 1)
		{
			Flags::character_show_flag = 0;
			delete character_show;
			character_show = NULL;
		}
	}
	else if (guild_pt->guild_pt_flag)
	{
		guild_pt->Reaction();
	}

	return choosed_number;
}