#include "Menu.h"
#include"Flags.h"
#include<DxLib.h>
#include"Key_Input.h"
#include<stdio.h>


Menu::Menu()
{
	fp = NULL; //�ی�

	fp = fopen("./scn/menu/menu.cns", "r"); //�w�肳�ꂽ�t�@�C�����J��

	if (fp == NULL) //�G���[����
	{
		DrawString(10, 10, "Error", GetColor(255, 0, 0));
		WaitKey(); //�L�[���͑҂�
		DxLib_End();				// �c�w���C�u�����g�p�̏I������
		exit(1);
	}
	fscanf(fp, "%d", &menumax);
	for (int i = 0; i < menumax; i++)
	{
		fscanf_s(fp, "%s", menu_mean[i],19);
		fscanf_s(fp, "%s", menu_explanation[i],39);
	}

	boxcolor = GetColor(0, 0, 0); //��
	textcolor = GetColor(255, 255, 255); //��
	boxcolor2 = GetColor(255, 255, 0); //���F
	textcolor2 = GetColor(0, 0, 0); //��
	boxcolor3 = GetColor(0, 0, 255); //��
	choosecolor = GetColor(0, 255, 255); //���F

	choose_now = 0;
	menu_act_number = -1;

	test = LoadGraph("./pics/player/�A�C�}�X�Q�t��_�͂�.png");
}


Menu::~Menu()
{
	if (fp != NULL)
	{
		fclose(fp);
	}
}


void Menu::Draw()
{
	if (Flags::menuflag)
	{
		DrawBox(120, 39, 122, 402, boxcolor2, TRUE); //�䎌���̎���E
		DrawBox(18, 39, 20, 402, boxcolor2, TRUE); //�䎌���̎��荶
		DrawBox(19, 39, 121, 40, boxcolor2, TRUE); //�䎌���̎����
		DrawBox(19, 400, 121, 401, boxcolor2, TRUE); //�䎌���̎��艺

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����
		DrawBox(20, 40, 120, 400, boxcolor, TRUE); //�䎌��
		DrawBox(0, 0, 320, 20, boxcolor3, TRUE); //������
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

		DrawBox(21, 41 + choose_now * 20, 119, 61 + choose_now * 20, boxcolor2, TRUE); //�I�𒆂̂�����
		DrawFormatString(2, 2,textcolor , "%s", menu_explanation[choose_now], TRUE); //�������悤

		for (int i = 0; i < menumax; i++)
		{
			DrawFormatString(22, 42 + i * 20, (choose_now == i ? textcolor2 : textcolor), " %s", menu_mean[i]); //�I�΂ꂽ�̂́A���ł���
		}

		DrawRotaGraph(360, 180,0.5,0, test, TRUE);

	}

}


int Menu::Reaction()
{
	if (!Flags::talkflag && Key_Input::buff_time[KEY_INPUT_X] == 1 && !Flags::nowscene)
	{
		if (!Flags::menuflag)
		{
			Flags::menuflag++;
		}
		else
		{
			Flags::menuflag = 0;
		}
	}

	if (Flags::menuflag && menu_act_number == -1) //���j���[��I������
	{
		if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_UP] != 11)
		{
			choose_now = (choose_now > 0 ? choose_now - 1 : menumax - 1); //���[�v�ł���悤��
		}
		if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_DOWN] != 11)
		{
			choose_now = (choose_now < menumax - 1 ? choose_now + 1 : 0);
		}
	}
	return 0;
}