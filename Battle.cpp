#include "Battle.h"
#include "DxLib.h"
#include "Key_Input.h"
#include"Flags.h"


Battle::Battle()
{
	testgraph = LoadGraph("./pics/battle/SnapCrab_Filsnown �`���ƍ��`_2013-8-12_17-9-45_No-00.png");
}


Battle::~Battle()
{
}

void Battle::Draw()
{
	DrawExtendGraph(0, 0, 640, 480, testgraph, TRUE);
	DrawString(120, 120, "����͉��̐퓬�V�[���ł�", GetColor(0, 0, 255));
	DrawString(120, 160, "Enter�L�[�Ŗ߂�܂�", GetColor(0, 0, 255));
}

int Battle::Reaction()
{
	int r = 0;
	if (Key_Input::buff[KEY_INPUT_RETURN])
	{
		Flags::nowscene = 0xf1e1d;
	}
	return r;
}