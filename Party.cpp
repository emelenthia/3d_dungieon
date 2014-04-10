#include "Party.h"
#include"DxLib.h"
#include"Colors.h"
//#include<stdio.h>

Party* Party::instance;

Party::Party()
{
	fp = fopen("./scn/party/party.cns", "r");
	if (fp == NULL)
	{
		DrawString(0, 0, "Error. I can not open file.", Colors::red);
		WaitKey();
	}

	fscanf(fp, "%d", &party_type);
	for (int i = 0; i < party_type / 10; i++)
	{
		fscanf(fp, "%d", &party_info[i]);
		if (i > 5)
		{
			DrawString(0, 0, "Error. I miss opening file.", Colors::red);
			WaitKey();
		}
	}

	pos_x_lu_territory = 160;
	pos_y_lu_territory = 380;
	pos_x_rd_territory = 640;
	pos_y_rd_territory = 480;

	size_x = (pos_x_rd_territory - pos_x_lu_territory) / 3;
	size_y = (pos_y_rd_territory - pos_y_lu_territory) / 2;
	crevice_x = 4;
	crevice_y = 3;
}


Party::~Party()
{
	if (fp != NULL)
	{
		fclose(fp);
	}
}


void Party::Draw()
{
	int pos_x_lu = 0;
	int pos_y_lu = 0;
	int pos_x_rd = 0;
	int pos_y_rd = 0;

	switch (party_type)
	{
	case 11:
		//�O
		DrawBox_t(0, 1);
		break;
	case 21:
		//�O��
		DrawBox_t(0, 0.5);
		//�O�E
		DrawBox_t(0, 1.5);
		break;
	case 22:
		//�O
		DrawBox_t(0, 1);
		//��
		DrawBox_t(1, 1);
		break;
	case 31:
		//�O��
		DrawBox_t(0, 0);
		//�O
		DrawBox_t(0, 1);
		//�O�E
		DrawBox_t(0, 2);
		break;
	case 32:
		//�O��
		DrawBox_t(0, 0.5);
		//�O�E
		DrawBox_t(0, 1.5);
		//��
		DrawBox_t(1, 1);
		break;
	case 33:
		//�O
		DrawBox_t(0, 1);
		//�㍶
		DrawBox_t(1, 0.5);
		//��E
		DrawBox_t(1, 1.5);
		break;
	case 41:
		//�O��
		DrawBox_t(0, 0);
		//�O
		DrawBox_t(0, 1);
		//�O�E
		DrawBox_t(0, 2);
		//��
		DrawBox_t(1, 1);
		break;
	case 42:
		//�O��
		DrawBox_t(0, 0.5);
		//�O�E
		DrawBox_t(0, 1.5);
		//�㍶
		DrawBox_t(1, 0.5);
		//��E
		DrawBox_t(1, 1.5);
		break;
	case 43:
		//�O
		DrawBox_t(0, 1);
		//�㍶
		DrawBox_t(1, 0);
		//��
		DrawBox_t(1, 1);
		//��E
		DrawBox_t(1, 2);
		break;
	case 51:
		//�O��
		DrawBox_t(0, 0);
		//�O
		DrawBox_t(0, 1);
		//�O�E
		DrawBox_t(0, 2);
		//�㍶
		DrawBox_t(1, 0.5);
		//��E
		DrawBox_t(1, 1.5);
		break;
	case 52:
		//�O��
		DrawBox_t(0, 0.5);
		//�O�E
		DrawBox_t(0, 0.5);
		//�㍶
		DrawBox_t(1, 0);
		//��
		DrawBox_t(1, 1);
		//��E
		DrawBox_t(1, 2);
		break;
	default:
		break;
	}
}


void Party::DrawBox_t(int front_or_back,float left_pos_number)
{
	int pos_x_lu = 0;
	int pos_y_lu = 0;
	int pos_x_rd = 0;
	int pos_y_rd = 0;

	pos_x_lu = pos_x_lu_territory + size_x * left_pos_number + 0.5 * crevice_x;
	pos_y_lu = pos_y_lu_territory + size_y * front_or_back + 0.5 * crevice_y;
	pos_x_rd = pos_x_lu + size_x - 2 * 0.5 * crevice_x;
	pos_y_rd = pos_y_lu + size_y - 2 * 0.5 * crevice_y;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����

	DrawBox(pos_x_lu, pos_y_lu, pos_x_rd, pos_y_rd, Colors::black, TRUE); //���̏�ɏ���`��

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

}