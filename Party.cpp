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
	characters = Characters::GetInstance();

	party_info[0] = 0; 
	party_info[1] = 10;
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

	countdbt = 0;
	switch (party_type)
	{
	case 11:
		//前
		DrawBox_t(0, 1);
		break;
	case 21:
		//前左
		DrawBox_t(0, 0.5);
		//前右
		DrawBox_t(0, 1.5);
		break;
	case 22:
		//前
		DrawBox_t(0, 1);
		//後
		DrawBox_t(1, 1);
		break;
	case 31:
		//前左
		DrawBox_t(0, 0);
		//前
		DrawBox_t(0, 1);
		//前右
		DrawBox_t(0, 2);
		break;
	case 32:
		//前左
		DrawBox_t(0, 0.5);
		//前右
		DrawBox_t(0, 1.5);
		//後
		DrawBox_t(1, 1);
		break;
	case 33:
		//前
		DrawBox_t(0, 1);
		//後左
		DrawBox_t(1, 0.5);
		//後右
		DrawBox_t(1, 1.5);
		break;
	case 41:
		//前左
		DrawBox_t(0, 0);
		//前
		DrawBox_t(0, 1);
		//前右
		DrawBox_t(0, 2);
		//後
		DrawBox_t(1, 1);
		break;
	case 42:
		//前左
		DrawBox_t(0, 0.5);
		//前右
		DrawBox_t(0, 1.5);
		//後左
		DrawBox_t(1, 0.5);
		//後右
		DrawBox_t(1, 1.5);
		break;
	case 43:
		//前
		DrawBox_t(0, 1);
		//後左
		DrawBox_t(1, 0);
		//後
		DrawBox_t(1, 1);
		//後右
		DrawBox_t(1, 2);
		break;
	case 51:
		//前左
		DrawBox_t(0, 0);
		//前
		DrawBox_t(0, 1);
		//前右
		DrawBox_t(0, 2);
		//後左
		DrawBox_t(1, 0.5);
		//後右
		DrawBox_t(1, 1.5);
		break;
	case 52:
		//前左
		DrawBox_t(0, 0.5);
		//前右
		DrawBox_t(0, 0.5);
		//後左
		DrawBox_t(1, 0);
		//後
		DrawBox_t(1, 1);
		//後右
		DrawBox_t(1, 2);
		break;
	default:
		break;
	}
}


void Party::DrawBox_t(int front_or_back, float left_pos_number)
{
	int pos_x_lu = 0;
	int pos_y_lu = 0;
	int pos_x_rd = 0;
	int pos_y_rd = 0;

	pos_x_lu = pos_x_lu_territory + size_x * left_pos_number + 0.5 * crevice_x;
	pos_y_lu = pos_y_lu_territory + size_y * front_or_back + 0.5 * crevice_y;
	pos_x_rd = pos_x_lu + size_x - 2 * 0.5 * crevice_x;
	pos_y_rd = pos_y_lu + size_y - 2 * 0.5 * crevice_y;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透化

	DrawBox(pos_x_lu, pos_y_lu, pos_x_rd, pos_y_rd, Colors::black, TRUE); //この上に情報を描画

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

	//個人情報の表示
	/*if (!countdbt)
	{
		DrawExtendGraph(pos_x_lu + 2, pos_y_lu + 2, pos_x_lu + 2 + size_x / 2, pos_y_lu + 2 + size_y / 2, testgraph, TRUE);
		DrawFormatString(pos_x_lu + 3 * size_x / 4 - GetDrawStringWidth("ハルカ", strlen("ハルカ")) / 2, pos_y_lu, Colors::white, "%s", "ハルカ");
		DrawExtendString(pos_x_lu + 2, pos_y_lu + size_y / 4, 1.0, 1.0, "MU", Colors::white);
		DrawExtendString(pos_x_lu + GetDrawStringWidth("FT", 2) / 2, pos_y_lu + size_y / 2 + 5, 1.0, 0.7, "HP", Colors::yellow);
		DrawString(pos_x_lu + size_x / 2 - GetDrawStringWidth("10", 2), pos_y_lu + size_y / 2, "10", Colors::white);
		DrawString(pos_x_lu + size_x - GetDrawStringWidth("10", 2) - 5, pos_y_lu + size_y / 2, "14", Colors::white);
		DrawBox(pos_x_lu + GetDrawStringWidth("FT", 2) / 2 - 1, pos_y_lu + size_y - 6, pos_x_lu + size_x / 2 - 2, pos_y_lu + size_y - 1, Colors::yellow, TRUE);
		DrawBox(pos_x_lu + GetDrawStringWidth("FT", 2) / 2 - 1 + size_x / 2, pos_y_lu + size_y - 6, pos_x_lu + size_x - 2, pos_y_lu + size_y - 1, Colors::green, TRUE);
		DrawExtendString(pos_x_lu + GetDrawStringWidth("FT", 2) / 2 + size_x / 2, pos_y_lu + size_y / 2 + 5, 1.0, 0.7, "TP", Colors::green);
	}
	else
	{
		DrawExtendGraph(pos_x_lu + 2, pos_y_lu + 2, pos_x_lu + 2 + size_x / 2, pos_y_lu + 2 + size_y / 2, testgraph2, TRUE);
		DrawFormatString(pos_x_lu + 3 * size_x / 4 - GetDrawStringWidth("ミキ", strlen("ミキ")) / 2, pos_y_lu, Colors::white, "%s", "ミキ");
		DrawExtendString(pos_x_lu + 2, pos_y_lu + size_y / 4, 1.0, 1.0, "FT", Colors::white);
		DrawExtendString(pos_x_lu + GetDrawStringWidth("FT", 2) / 2, pos_y_lu + size_y / 2 + 5, 1.0, 0.7, "HP", Colors::yellow);
		DrawString(pos_x_lu + size_x / 2 - GetDrawStringWidth("10", 2), pos_y_lu + size_y / 2, "16", Colors::white);
		DrawString(pos_x_lu + size_x - GetDrawStringWidth("10", 2) - 5, pos_y_lu + size_y / 2, "10", Colors::white);
		DrawBox(pos_x_lu + GetDrawStringWidth("FT", 2) / 2 - 1, pos_y_lu + size_y - 6, pos_x_lu + size_x / 2 - 2, pos_y_lu + size_y - 1, Colors::yellow, TRUE);
		DrawBox(pos_x_lu + GetDrawStringWidth("FT", 2) / 2 - 1 + size_x / 2, pos_y_lu + size_y - 6, pos_x_lu + size_x - 2, pos_y_lu + size_y - 1, Colors::green, TRUE);
		DrawExtendString(pos_x_lu + GetDrawStringWidth("FT", 2) / 2 + size_x / 2, pos_y_lu + size_y / 2 + 5, 1.0, 0.7, "TP", Colors::green);
	}*/


	int charnumb = party_info[countdbt];

	//画像の表示
	DrawExtendGraph(pos_x_lu + 2, pos_y_lu + 2, pos_x_lu + 2 + size_x / 2, pos_y_lu + 2 + size_y / 2,characters->char_h_i[charnumb][characters->job[charnumb]], TRUE);

	char c_name[21];
	strcpy(c_name, characters->name[charnumb]);
	DrawFormatString(pos_x_lu + 3 * size_x / 4 - GetDrawStringWidth(c_name, strlen(c_name)) / 2, pos_y_lu, Colors::white, "%s", c_name);
	
	char j_name[5];
	strcpy(j_name, characters->GetJobNameabb(charnumb));
	DrawExtendString(pos_x_lu + 2, pos_y_lu + size_y / 4, 1.0, 1.0, j_name, Colors::white);
	
	int job_size = GetDrawStringWidth(j_name, strlen(j_name));
	DrawExtendString(pos_x_lu +job_size / 2, pos_y_lu + size_y / 2 + 5, 1.0, 0.7, "HP", Colors::yellow);

	char str_hp[9];
	sprintf(str_hp, "%d", characters->nowhp[charnumb]); //長さを測るために文字列に変換
	DrawFormatString(pos_x_lu + size_x / 2 - GetDrawStringWidth(str_hp, strlen(str_hp)), pos_y_lu + size_y / 2, Colors::white, "%d", characters->nowhp[charnumb]);
	
	DrawBox(pos_x_lu + job_size / 2 - 1, pos_y_lu + size_y - 6, pos_x_lu + size_x / 2 - 2, pos_y_lu + size_y - 1, Colors::yellow, TRUE);
	
	DrawExtendString(pos_x_lu + job_size / 2 + size_x / 2, pos_y_lu + size_y / 2 + 5, 1.0, 0.7, "TP", Colors::green);

	char str_tp[9];
	sprintf(str_tp, "%d", characters->nowtp[charnumb]);
	DrawFormatString(pos_x_lu + size_x - GetDrawStringWidth(str_tp, strlen(str_tp)) - 5, pos_y_lu + size_y / 2, Colors::white, "%d", characters->nowtp[charnumb]);

	DrawBox(pos_x_lu + job_size / 2 - 1 + size_x / 2, pos_y_lu + size_y - 6, pos_x_lu + size_x - 2, pos_y_lu + size_y - 1, Colors::green, TRUE);
	

	countdbt++;

}


