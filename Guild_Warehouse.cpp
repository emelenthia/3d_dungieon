#include "Guild_Warehouse.h"
#include"DxLib.h"
#include"Key_Input.h"
#include"Flags.h"

Guild_Warehouse::Guild_Warehouse()
{

	fscanf_r("./scn/guild/guild_warehouse_list.cns");
	
	choosed_number = -1;
	choose_now = 0;
}


Guild_Warehouse::~Guild_Warehouse()
{
}


int Guild_Warehouse::Reaction()
{
	choosed_number = 0;
	//if (Flags::nowscene == 0x8011d && Flags::guild_now == 2)
	{
		if (Key_Input::buff_time[KEY_INPUT_X] == 1)
		{
			choosed_number = 2;
		}
		else if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
		{
			choosed_number = choose_now + 2011;//2-01-(n+1)
		}
	}


	//if (Flags::nowscene == 0x8011d && Flags::guild_now == 2) //メニューを選択する
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