#include "Objects.h"
#include"Players.h"
#include"Defines.h"
#include"DxLib.h"
#include"Field.h"

Objects::Objects()
{
}


Objects::~Objects()
{
}


void Objects::HitCheck()
{
	if (checkhitflag) //�ʂ蔲���s�\�ݒ�̃I�u�W�F�N�g
	{
		int checkpoint = 0;
		//�ʂ蔲���ł��Ȃ��悤��
		if ((Players::real_pos_x + Players::pos_x_lu < pos_x_lu && pos_x_lu < Players::real_pos_x + Players::pos_x_rd) || //�I�u�W�F�N�g�Ƀv���C���[�������|�������ꍇ
			(Players::real_pos_x + Players::pos_x_lu < pos_x_rd && pos_x_rd < Players::real_pos_x + Players::pos_x_rd))
		{
			checkpoint++;
		}
		if ((Players::real_pos_y + Players::pos_y_lu < pos_y_lu && pos_y_lu < Players::real_pos_y + Players::pos_y_rd) ||
			(Players::real_pos_y + Players::pos_y_lu < pos_y_rd && pos_y_rd < Players::real_pos_y + Players::pos_y_rd))
		{
			checkpoint++;
		}
		if (Players::real_pos_x + Players::pos_x_lu >= pos_x_lu && Players::real_pos_x + Players::pos_x_rd <= pos_x_rd)//�v���C���[���I�u�W�F�N�g���傫���ꍇ
		{
			checkpoint++;
		}
		if (Players::real_pos_y + Players::pos_y_lu >= pos_y_lu && Players::real_pos_y + Players::pos_y_rd <= pos_y_rd)
		{
			checkpoint++;
		}

		if (checkpoint >= 2)
		{
			if (!Players::ndirection)
			{
				if (Players::direction == 2) //�E�������Ă���(������Ԃ�����)�ꍇ
				{
					Players::real_pos_x = pos_x_lu - Defines::player_size_x;
					Players::real_pos_x += (Defines::player_size_x - Players::pos_x_rd); //����
				}

				if (Players::direction == 1) //���������Ă���
				{
					Players::real_pos_x = pos_x_rd;
					Players::real_pos_x -= Players::pos_x_lu;
				}

				if (Players::direction == 0) //���������Ă���(�ォ��Ԃ�����)�ꍇ
				{
					Players::real_pos_y = pos_y_lu - Defines::player_size_y;
					Players::real_pos_y += (Defines::player_size_y - Players::pos_y_rd);
				}

				if (Players::direction == 3) //��������Ă���
				{
					Players::real_pos_y = pos_y_rd;
					Players::real_pos_y -= Players::pos_y_lu;
				}
			}
			else //�΂߈ړ��̏ꍇ
			{
				if (Players::ndirection == 1) //����������Ă���(�E������Ԃ�����)�ꍇ
				{
					if (Players::old_real_pos_y + Players::pos_y_lu >= pos_y_rd) //�I�u�W�F�N�g��艺�ɂ���ꍇ
					{
						Players::real_pos_y = pos_y_rd;
						Players::real_pos_y -= Players::pos_y_lu;
					}
					else if (Players::old_real_pos_x + Players::pos_x_lu >= pos_x_rd) //�I�u�W�F�N�g���E�ɂ���ꍇ
					{
						Players::real_pos_x = pos_x_rd;
						Players::real_pos_x -= Players::pos_x_lu;
					}
				}

				if (Players::ndirection == 2) //�E��������Ă���(��������Ԃ�����)�ꍇ
				{
					if (Players::old_real_pos_y + Players::pos_y_lu >= pos_y_rd) //�I�u�W�F�N�g��艺�ɂ���ꍇ
					{
						Players::real_pos_y = pos_y_rd;
						Players::real_pos_y -= Players::pos_y_lu;
					}
					else if (Players::old_real_pos_x + Players::pos_x_rd <= pos_x_lu) //�I�u�W�F�N�g��荶�ɂ���ꍇ
					{
						Players::real_pos_x = pos_x_lu - Defines::player_size_x;
						Players::real_pos_x += (Defines::player_size_x - Players::pos_x_rd); //����
					}
				}

				if (Players::ndirection == 3) //�����������Ă���
				{
					if (Players::old_real_pos_y + Players::pos_y_rd <= pos_y_lu) //�I�u�W�F�N�g����ɂ���ꍇ
					{
						Players::real_pos_y = pos_y_lu - Defines::player_size_y;
						Players::real_pos_y += (Defines::player_size_y - Players::pos_y_rd);
					}
					else if (Players::old_real_pos_x + Players::pos_x_lu >= pos_x_rd) //�I�u�W�F�N�g���E�ɂ���ꍇ
					{
						Players::real_pos_x = pos_x_rd;
						Players::real_pos_x -= Players::pos_x_lu;
					}
				}

				if (Players::ndirection == 4) //�E���������Ă���
				{
					if (Players::old_real_pos_y + Players::pos_y_rd <= pos_y_lu) //�I�u�W�F�N�g����ɂ���ꍇ
					{
						Players::real_pos_y = pos_y_lu - Defines::player_size_y;
						Players::real_pos_y += (Defines::player_size_y - Players::pos_y_rd);
					}
					else if (Players::old_real_pos_x + Players::pos_x_rd <= pos_x_lu) //�I�u�W�F�N�g��荶�ɂ���ꍇ
					{
						Players::real_pos_x = pos_x_lu - Defines::player_size_x;
						Players::real_pos_x += (Defines::player_size_x - Players::pos_x_rd); //����
					}
				}

			}
		}
	}
	
}


void Objects::Draw()
{
	if (hundle_number != -1) //-1�͓����ȉ摜
	{
		DrawGraph(pos_x - Field::left_upper_x, pos_y - Field::left_upper_y, hundle_number, TRUE); //��ʂ����ꂽ���ɂ�����Ƃ����l��
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����
	DrawBox(pos_x_lu - Field::left_upper_x, pos_y_lu - Field::left_upper_y, pos_x_rd - Field::left_upper_x, pos_y_rd - Field::left_upper_y, GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�


	DrawFormatString(0, 160, GetColor(255, 0, 255), "pos_x:%d", Players::real_pos_x);
	DrawFormatString(0, 180, GetColor(255, 0, 255), "pos_y:%d", Players::real_pos_y);
	DrawFormatString(0, 200, GetColor(255, 0, 255), "direction:%d", Players::direction);
	DrawFormatString(0, 220, GetColor(255, 0, 255), "ndirection:%d", Players::ndirection);
	DrawFormatString(0, 240, GetColor(255, 0, 255), "o_pos(x,y):(%d,%d)", Players::old_real_pos_x, Players::old_real_pos_y);
	DrawFormatString(0, 260, GetColor(255, 0, 255), "F_l_u:(%d,%d)", Field::left_upper_x, Field::left_upper_y);
}


void Objects::MakeObject(int temporary_pos_x, int temporary_pos_y, int temporary_pos_x_lu, 
	int temporary_pos_y_lu, int temporary_pos_x_rd, int temporary_pos_y_rd,int temporary_hundle_number,int temporary_checkhitflag)
{
	pos_x = temporary_pos_x;
	pos_y = temporary_pos_y;
	pos_x_lu = temporary_pos_x_lu;
	pos_y_lu = temporary_pos_y_lu;
	pos_x_rd = temporary_pos_x_rd;
	pos_y_rd = temporary_pos_y_rd;
	hundle_number = temporary_hundle_number;
	checkhitflag = temporary_checkhitflag;
}