#include "Balloon.h"
#include<DxLib.h>

int Balloon::talkflag;
int Balloon::talkfinishflag;
char Balloon::talktext[10][80];

Balloon::Balloon()
{
	talkflag = 0;
	boxcolor = GetColor(0, 0, 255);
	talkcolor = GetColor(255, 0, 0);
}


Balloon::~Balloon()
{
}


void Balloon::Draw()
{
	if (talkflag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //“§‰»
		DrawBox(0, 240, 640, 480, boxcolor, TRUE); 
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //Œ³‚É–ß‚·

		DrawFormatString(40, 320, talkcolor, "%s", talktext[talkflag - 1]);
	}
}