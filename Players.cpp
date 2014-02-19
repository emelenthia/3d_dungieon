#include "Players.h"
#include"DxLib.h"
#include"Defines.h"
#include<math.h>
#include"Field.h"
#include"Key_Input.h"
#include"Flags.h"

int Players::pos_x;
int Players::pos_y;
int Players::real_pos_x;
int Players::real_pos_y;
int Players::direction;
int Players::ndirection;
int Players::moment;
int Players::old_real_pos_x;
int Players::old_real_pos_y;

Players::Players()
{
	LoadDivGraph("./pics/player/vx_chara01_b.png", 96, 12, 8, Defines::player_size_x, Defines::player_size_y, player_h);
	fast_speed = 5;
	slow_speed = 3;
	pos_x = 200;
	pos_y = 200;
	real_pos_x = pos_x;
	real_pos_y = pos_x;
	old_real_pos_x = pos_x;
	old_real_pos_y = pos_x;
	direction = 0;
	ndirection = 0;
	moment = 0;
}


Players::~Players()
{
}


void Players::Draw()
{
		
	DrawGraph(real_pos_x - Field::left_upper_x, real_pos_y - Field::left_upper_y, player_h[12 * direction], TRUE);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //������
	DrawBox(Players::pos_x_lu + pos_x, Players::pos_y_lu + pos_y, Players::pos_x_rd + pos_x, Players::pos_y_rd + pos_y, GetColor(0, 0, 255), TRUE); //�Փ˔���̕\��
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

	DrawFormatString(0, 160, GetColor(255, 0, 255), "pos_x:%d", real_pos_x);
	DrawFormatString(0, 180, GetColor(255, 0, 255), "pos_y:%d", real_pos_y);
	DrawFormatString(0, 200, GetColor(255, 0, 255), "direction:%d", direction);
	DrawFormatString(0, 220, GetColor(255, 0, 255), "ndirection:%d", ndirection);
	DrawFormatString(0, 240, GetColor(255, 0, 255), "o_pos(x,y):(%d,%d)", old_real_pos_x, old_real_pos_y);
	DrawFormatString(0, 260, GetColor(255, 0, 255), "F_l_u:(%d,%d)", Field::left_upper_x, Field::left_upper_y);

}

void Players::Reaction()
{
	pos_x = real_pos_x - Field::left_upper_x; //�����s�K�v�ȏ����B�v����
	pos_y = real_pos_y - Field::left_upper_y;

	//ndirection = 0;
	old_real_pos_x = real_pos_x; //�Â��ʒu�����L��
	old_real_pos_y = real_pos_y;

	int speed;
	moment = 0;
	if (!Flags::talkflag && !Flags::menuflag) //��b����X�}�z��M��Ȃ�������Ȃ�
	{
		if (Key_Input::buff[KEY_INPUT_RSHIFT] || Key_Input::buff[KEY_INPUT_LSHIFT])
		{
			speed = slow_speed;
		}
		else
		{
			speed = fast_speed;
		}
		if (Key_Input::buff[KEY_INPUT_UP])
		{
			moment = (moment | 1);
			direction = 3;
		}
		if (Key_Input::buff[KEY_INPUT_DOWN])
		{
			moment = (moment | 2);
			if (moment & 1)
			{
				direction = direction;
			}
			else
			{
				direction = 0;
			}
		}
		if (Key_Input::buff[KEY_INPUT_LEFT])
		{
			moment = (moment | 4);
			direction = 1;
		}
		if (Key_Input::buff[KEY_INPUT_RIGHT])
		{
			moment = (moment | 8);
			if (moment & 4)
			{
				direction = direction;
			}
			else
			{
				direction = 2;
			}
		}

		if (moment == 1) //��
		{
			pos_y -= speed;
			ndirection = 0;
		}
		if (moment == 2) //��
		{
			pos_y += speed;
			ndirection = 0;
		}
		if (moment == 4) //��
		{
			pos_x -= speed;
			ndirection = 0;
		}
		if (moment == 8) //�E
		{
			pos_x += speed;
			ndirection = 0;
		}
		if (moment == 5) //����
		{
			pos_x -= (int)floor(round(0.7f*speed));
			pos_y -= (int)floor(round(0.7f*speed));
			ndirection = 1;
		}
		if (moment == 9) //�E��
		{
			pos_x += (int)floor(round(0.7f*speed));
			pos_y -= (int)floor(round(0.7f*speed));
			ndirection = 2;
		}
		if (moment == 6) //����
		{
			pos_x -= (int)floor(round((0.7)*speed));
			pos_y += (int)floor(round((0.7)*speed));
			ndirection = 3;
		}
		if (moment == 10) //�E��
		{
			pos_x += (int)floor(round((0.7)*speed));
			pos_y += (int)floor(round((0.7)*speed));
			ndirection = 4;
		}


		if (pos_y > 480 - Defines::player_size_y) //��ʊO�ɏo�Ȃ��悤��
		{
			Field::left_upper_y += pos_y - (480 - Defines::player_size_y); //�v���C���[���[�ɋ��āA�X�Ɉړ��������ʂ����炷����
			if (Field::left_upper_y > 30 * 32 - 480) //�}�b�v�̊O�ɏo�Ȃ��悤�ɂ��鏈���B�}�b�v�`�b�v�̌��~�}�b�v�`�b�v�̃T�C�Y�~��ʂ̑傫��
			{
				Field::left_upper_y = 30 * 32 - 480;
			}
			pos_y = 480 - Defines::player_size_y;
		}
		if (pos_y < 0)
		{
			Field::left_upper_y += pos_y;
			if (Field::left_upper_y < 0)
			{
				Field::left_upper_y = 0;
			}
			pos_y = 0;
		}
		if (pos_x > 640 - Defines::player_size_x) //��ʊO�ɏo�Ȃ��悤��
		{
			Field::left_upper_x += pos_x - (640 - Defines::player_size_x);
			if (Field::left_upper_x > 30 * 32 - 640)
			{
				Field::left_upper_x = 30 * 32 - 640;
			}
			pos_x = 640 - Defines::player_size_x;
		}
		if (pos_x < 0)
		{
			Field::left_upper_x += pos_x;
			if (Field::left_upper_x < 0)
			{
				Field::left_upper_x = 0;
			}
			pos_x = 0;
		}

		real_pos_x = pos_x + Field::left_upper_x; //���Ƃ��Ă�x���W
		real_pos_y = pos_y + Field::left_upper_y;
	}
}

