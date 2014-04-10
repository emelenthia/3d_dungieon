#include "Guild_Dungeon.h"
#include"DxLib.h"
#include"Flags.h"
#include"Key_Input.h"
#include"Defines.h"

Guild_Dungeon::Guild_Dungeon()
{
	background_h1 = LoadGraph("./pics/background/doukutu.jpg");
	if (background_h1 == -1)
	{
		DrawExtendString(0, 0, 2.0, 2.0, "Error!", GetColor(255, 0, 0));
		WaitKey();
	}
	fscanf_r("./scn/guild/dungeon_list.cns");
	choosed_number = 0;
	choose_now = 0;
	char_flag = 0;
}


Guild_Dungeon::~Guild_Dungeon()
{
}


int Guild_Dungeon::Reaction()
{
	choosed_number = 0;
	if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
	{
		choosed_number = choose_now + 1;
	}
		if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_UP] != 11)
		{
			choose_now = (choose_now > 0 ? choose_now - 1 : list_max - 1); //ÉãÅ[ÉvÇ≈Ç´ÇÈÇÊÇ§Ç…
		}
		if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_DOWN] != 11)
		{
			choose_now = (choose_now < list_max - 1 ? choose_now + 1 : 0);
		}
	return choosed_number;
}