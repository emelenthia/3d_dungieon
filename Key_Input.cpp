#include "Key_Input.h"
#include<DxLib.h>
#include"Flags.h"

char Key_Input::buff[256];
int Key_Input::buff_time[256];

Key_Input::Key_Input()
{
}


Key_Input::~Key_Input()
{
}


void Key_Input::KeyUpdate()
{
	GetHitKeyStateAll(buff);
	i = 0;
	while (i < 256) //‰Ÿ‚µ‰ºŽžŠÔ‚ð’²‚×‚é
	{
		if (buff[i])
		{
			buff_time[i]++;
		}
		else
		{
			buff_time[i] = 0;
		}
		i++;
	}

	/*if (Flags::talkflag) //‰ï˜b’†‚ÍŒˆ’èƒL[‚Ì‚Ý
	{
		if (buff[KEY_INPUT_Z])
		{
			talkingflag++;
		}
		for (int i = 0; i < 256; i++)
		{
			buff[i] = 0;
		}
		if (talkingflag)
		{
			buff[KEY_INPUT_Z] = 1;
			talkingflag = 0;
		}
	}*/
}