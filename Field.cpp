#include "Field.h"
#include "DxLib.h"
#include"Green_Field.h"

int Field::now_field;
int Field::left_upper_x = 0;
int Field::left_upper_y = 0;

Field::Field()
{
	//Green_Field g_field;
	now_field_pointa = &f_town;
	now_player_pointa = &players;
	now_field = 3; //Green_Field��1�B������ƍ��Ƃ��̓t�B�[���h�̔ԍ��ꗗ�����߂Ă����B�}�b�v�̌`���ł���΂��ׂČ��߂Ă���
}


Field::~Field()
{
}


void Field::Draw()
{
	now_field_pointa->Draw();
	now_player_pointa->Draw();
	menu.Draw();
}


int Field::Reaction()
{
	int r = 0;
	now_player_pointa->Reaction();
	r = now_field_pointa->Reaction();
	menu.Reaction();

	if (r) //�t�B�[���h�̈ړ�����
	{
		if (now_field_pointa == &g_field) //�����t�B�[���h�ł���
		{
			switch (r)
			{
			case 1:
				now_field_pointa = &i_field;
				Players::real_pos_x = 960;
				Players::pos_x = 480;
				Players::old_real_pos_x = 960;
				left_upper_x = 320; //������ƍ���̍��W�����킹��
				now_field = 2; //Ice_Field��2
				break;
			}
		}
	}
	return r;
}