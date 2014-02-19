#include "Talker.h"
#include<DxLib.h>
#include"Field.h"
#include"Defines.h"
#include"Key_Input.h"
#include<stdio.h>
#include"Flags.h"
#include"Events.h"

Talker::Talker()
{
	Flags::talkflag = 0;
	talkpage = 0;
	boxcolor = GetColor(0, 0, 255);
	talkcolor = GetColor(255, 0, 0);
	fp = NULL; //���ꂵ�Ȃ��Ɨ�����
	chooseflag = 0;
	choosenumber = 0;
	event_number = 0;
	strcpy(file_name, "null"); //�K���ȏ����l
	
}


Talker::~Talker()
{
	if (fp != NULL) //�`�F�b�N���Ȃ��Ɨ�����
	{
		fclose(fp);
	}
}


void Talker::Draw()
{
	//�{�̂̕\��
	if (hundle_number != -1) //-1�͓����ȉ摜
	{
		DrawGraph(pos_x - Field::left_upper_x, pos_y - Field::left_upper_y, hundle_number, TRUE); //��ʂ����ꂽ���ɂ�����Ƃ����l��
	}

	//�����蔻��̕\��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //������
	DrawBox(pos_x_lu - Field::left_upper_x, pos_y_lu - Field::left_upper_y, pos_x_rd - Field::left_upper_x, pos_y_rd - Field::left_upper_y, GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

	//�䎌�̕\��
	if (Flags::talkflag && talkpage)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����
		DrawBox(0, 240, 640, 480, boxcolor, TRUE); //�䎌��
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

		if (talkpage == talkmax && chooseflag) //�I�������L��ꍇ
		{
			for (int i = 0; i < choosemax; i++)
			{
				DrawFormatString(40, 300 + i * 20, talkcolor, "%s", choose_mean[i]);
			}
		}
		else
		{
			DrawFormatString(40, 320, talkcolor, "%s", talk_mean[talkpage - 1]); //�䎌
		}
	}
	
	//���̕\��
	if (chooseflag)
	{
		DrawString(20, 280 + choosenumber * 20, "->", talkcolor);
	}


}


int Talker::Reaction()
{
	int r = 0;
	if (((Players::real_pos_x + Players::pos_x_lu <= pos_x_rd) &&
		(Players::real_pos_x + Players::pos_x_rd >= pos_x_lu) &&
		(Players::real_pos_y + Players::pos_y_lu <= pos_y_rd) &&
		(Players::real_pos_y + Players::pos_y_rd >= pos_y_lu)) //���̃I�u�W�F�N�g�ɏd�Ȃ�����
		&& ((Players::direction == 0 && Players::real_pos_y + Players::pos_y_rd <= pos_y_lu) //���������Ă���
		||  (Players::direction == 1 && Players::real_pos_x + Players::pos_x_lu >= pos_x_rd) //���������Ă���
		||  (Players::direction == 2 && Players::real_pos_x + Players::pos_x_rd <= pos_x_lu) //�E�������Ă���
		||  (Players::direction == 3 && Players::real_pos_y + Players::pos_y_lu >= pos_y_rd)) //��������Ă���
		&&  ((Key_Input::buff_time[KEY_INPUT_Z]) == 1) //Z�{�^�����������u��
		&&  (!Flags::menuflag)) //�X�}�z���Ȃ���ł͂Ȃ�
	{
		r = 1;
		if (talkpage != talkmax)
		{
			Flags::talkflag = 1;
			talkpage++;
		}
		else
		{
			if (chooseflag || !choosemax || choosemax == -1) //�I�������Ȃ��ꍇ�B�������͑I�������I������ꍇ
			{
				if (choosemax == -1) //����H���̏ꍇ
				{
					if (fp != NULL)
					{
						fclose(fp);
					}
					talkpage = change_pattern - 1;
					Flags::talkflag = talkpage;
					LoadTalk(choose_file_name[0]); //���̑䎌�̓ǂݍ���
					choosenumber = 0;
					chooseflag = 0;
				}
				else
				{
					if (choosenumber) //�I������I�񂾏ꍇ
					{
						if (fp != NULL)
						{
							fclose(fp);
						}
						talkpage = change_pattern - 1;
						Flags::talkflag = talkpage;
						LoadTalk(choose_file_name[choosenumber - 1]); //���̑䎌�̓ǂݍ���
						choosenumber = 0;
						chooseflag = 0;
					}
					else
					{
						events_t->ev_act(event_number); //�Ō�ɃC�x���g�̌Ăяo��
						Flags::talkflag = 0;//���Z�b�g�B
						talkpage = 0;
						chooseflag = 0;
						choosenumber = 0;
					}
				}
			}
			else
			{
				chooseflag = 1;
				if (!choosenumber)
				{
					choosenumber++; //�ԍ��̊���U��𕪂���₷��
				}
			}
		}
	}

	if (Key_Input::buff_time[KEY_INPUT_R] == 1) //�ēǂݍ���
	{
		if (fp != NULL)
		{
			fclose(fp);
			LoadTalk(file_name);
		}
	}

	if (chooseflag) //�I�����̑I��
	{
		if (Key_Input::buff_time[KEY_INPUT_UP] == 1) //��{�^��
		{
			if (choosenumber > 1)
			{
				choosenumber--;
			}
		}
		if (Key_Input::buff_time[KEY_INPUT_DOWN] == 1) //���{�^��
		{
			if (choosenumber < choosemax)
			{
				choosenumber++;
			}
		}

	}
	return r;
}


void Talker::LoadTalk(char file_pointer[40])
{
	if (!(strcmp(file_name, "null")))
	{
		strcpy(file_name, file_pointer); //���̃t�@�C�������o���Ă����B�Q�[�����̂ɂ͈Ӗ����Ȃ�
	}
	fp = fopen(file_pointer,"r"); //�w�肳�ꂽ�t�@�C�����J��
	
	if (fp == NULL) //�G���[����
	{
		DrawString(10, 10, "Error", GetColor(255, 0, 0));
		WaitKey();
		DxLib_End();				// �c�w���C�u�����g�p�̏I������
		exit(1);
	}

	fscanf(fp, "%d", &talkmax); //�K�v�ȏ��̃��[�h
	for (int i = 0; i < talkmax ; i++)
	{
		fscanf_s(fp, "%s", talk_mean[i],79);
	}
	fscanf(fp, "%d", &choosemax);
	for (int i = 0; i < choosemax; i++)
	{
		fscanf_s(fp, "%s", choose_mean[i],79);
	}
	for (int i = 0; i < choosemax; i++)
	{
		fscanf_s(fp, "%s", choose_file_name[i],39);
	}
	if (choosemax == -1)
	{
		fscanf_s(fp, "%s", choose_file_name[0],39);
	}
	if (choosemax)
	{
		fscanf(fp, "%d", &change_pattern);
	}
	fscanf(fp, "%d", &event_number);
}