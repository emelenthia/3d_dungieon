#include "Guild_Entrance.h"
#include"DxLib.h"
#include"Flags.h"
#include"Key_Input.h"
#include"Defines.h"

Guild_Entrance::Guild_Entrance()
{
	background_h1 = LoadGraph("./pics/background/20130701234522fad.png");
	if (background_h1 == -1)
	{
		DrawExtendString(0, 0, 2.0, 2.0, "Error!", GetColor(255, 0, 0));
		WaitKey();
	}
	fscanf_r("./scn/guild/guild_list.cns");
	choosed_number = 0;
	choose_now = 0;
}


Guild_Entrance::~Guild_Entrance()
{
}


int Guild_Entrance::Reaction()
{
	choosed_number = 0;
	if (Flags::nowscene == 0x8011d && Key_Input::buff_time[KEY_INPUT_Z] == 1 && Flags::guild_now == 1)
	{
		choosed_number = choose_now + 2;
		char_ran = GetRand(Defines::char_max - 1) + 1;
	}

	if (Flags::nowscene == 0x8011d && Flags::guild_now == 1) //メニューを選択する
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
	return choosed_number;
}