#include "In_Battle.h"
#include"Players.h"
#include"Flags.h"
#include<DxLib.h>
#include"Key_Input.h"

In_Battle::In_Battle()
{
}


In_Battle::~In_Battle()
{
}


int In_Battle::Reaction()
{
	int r = 0;
	if (((Players::real_pos_x + Players::pos_x_lu <= pos_x_rd) &&
		(Players::real_pos_x + Players::pos_x_rd >= pos_x_lu) &&
		(Players::real_pos_y + Players::pos_y_lu <= pos_y_rd) &&
		(Players::real_pos_y + Players::pos_y_rd >= pos_y_lu)) //このオブジェクトに重なったら
		&& (Key_Input::buff_time[KEY_INPUT_Z]) == 1) //Zボタンを押した瞬間
	{
		r = 1;
		if (talkpage != talkmax)
		{
			Flags::talkflag = 1;
			talkpage++;
		}
		else
		{
			Flags::talkflag = 0;
			Flags::nowscene = 0xba771e;
			talkpage = 0;
		}
	}

	return r;
}
