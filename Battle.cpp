#include "Battle.h"
#include "DxLib.h"
#include "Key_Input.h"
#include"Flags.h"


Battle::Battle()
{
	testgraph = LoadGraph("./pics/battle/SnapCrab_Filsnown �`���ƍ��`_2013-8-12_17-9-45_No-00.png");
	monsters = new Monsters(0);
}


Battle::~Battle()
{
}


void Battle::Draw()
{
	DrawExtendGraph(0, 0, 640, 480, testgraph, TRUE);
	DrawString(120, 120, "����͉��̐퓬�V�[���ł�", GetColor(0, 0, 255));
	DrawString(120, 160, "����L�[�Ŗ߂�܂�", GetColor(0, 0, 255));

	monsters->Draw();
}


int Battle::Reaction()
{
	int r = 0;
	if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
	{
		Flags::nowscene = 0xf1e1d;
	}
	return r;
}