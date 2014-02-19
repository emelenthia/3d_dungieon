#include "Guild_Main.h"
#include"DxLib.h"
#include"Flags.h"
#include"Key_Input.h"

Guild_Main::Guild_Main()
{
	fscanf_r("./scn/guild/guild_main_list.cns");
	choosed_number = -1;
	choose_now = 0;

}


Guild_Main::~Guild_Main()
{
}


int Guild_Main::Reaction()
{
	choosed_number = 0;
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
	return choosed_number;
}