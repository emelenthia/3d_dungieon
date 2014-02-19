#include "Guild_Scene_Base.h"
#include"DxLib.h"
#include"Defines.h"

int Guild_Scene_Base::char_ran;

Guild_Scene_Base::Guild_Scene_Base()
{
	black_h = GetColor(0, 0, 0);
	blue_h = GetColor(0, 0, 255);
	yellow_h = GetColor(255, 255, 0);
	white_h = GetColor(255, 255, 255);
	background_h1 = LoadGraph("./pics/background/201307012348260fe.png");
	if (background_h1 == -1)
	{
		DrawExtendString(0, 0, 2.0, 2.0, "Error! in Guild_Scene_Base", GetColor(255, 0, 0));
		WaitKey();
	}
	str_size_max = 0;
	fp = NULL;
	char_pt[0] = Character_Haruka::GetInstance();
	char_pt[1] = Character_02::GetInstance();
	char_pt[0]->Load_Char_n_s("./scn/char/char_DF_01.cns", "./scn/char/char_DS_01.cns");
	char_pt[1]->Load_Char_n_s("./scn/char/char_DF_02.cns", "./scn/char/char_DS_02.cns");
	char_ran = GetRand(Defines::char_max - 1) + 1;
}


Guild_Scene_Base::~Guild_Scene_Base()
{
	if (fp != NULL)
	{
		fclose(fp);
	}
}


void Guild_Scene_Base::Draw()
{
	int temp_size_x = str_size_max + 36;

	DrawExtendGraph(0, 0, 640, 480, background_h1, TRUE); //背景

	DrawBox(2 + temp_size_x, 39, 4 + temp_size_x, list_max * 20 + 42, yellow_h, TRUE); //台詞欄の周り右
	DrawBox(18, 39, 20, list_max * 20 + 42, yellow_h, TRUE); //台詞欄の周り左
	DrawBox(19, 38, 4 + temp_size_x, 40, yellow_h, TRUE); //台詞欄の周り上
	DrawBox(19, list_max * 20 + 41, 4 + temp_size_x, list_max * 20 + 43, yellow_h, TRUE); //台詞欄の周り下

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透過
	DrawBox(20, 40, 2 + temp_size_x, list_max * 20 + 40, black_h, TRUE); //台詞欄
	DrawBox(0, 0, 640, 20, blue_h, TRUE); //説明欄
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

	DrawBox(21, 41 + choose_now * 20, 2 + temp_size_x, 61 + choose_now * 20, yellow_h, TRUE); //選択中のを示す
	DrawFormatString(22, 2, white_h, "%s", menu_explanation[choose_now], TRUE); //説明しよう

	for (int i = 0; i < list_max; i++)
	{
		DrawFormatString(22, 42 + i * 20, (choose_now == i ? black_h : white_h), " %s", menu_list[i]); //選ばれたのは、黒でした
	}

	switch (char_ran)
	{
	case 1:
		DrawRotaGraph(480, 240, 0.7, 0, char_pt[0]->char_h[char_pt[0]->job-1], TRUE);
		break;
	case 2:
		DrawRotaGraph(480, 240, 0.7, 0, char_pt[1]->char_h[char_pt[1]->job - 1], TRUE);
		break;
	default:
		break;
	}

}


int Guild_Scene_Base::fscanf_r(char *file_name)
{
	int return_number = 0;

	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name);
		WaitKey();
	}

	fscanf(fp, "%d", &list_max);
	for (int i = 0; i < list_max; i++)
	{
		fscanf_s(fp, "%s", menu_list[i], 19);
		fscanf_s(fp, "%s", menu_explanation[i], 99);
		str_size_max = (GetDrawFormatStringWidth(menu_list[i]) > str_size_max ? GetDrawFormatStringWidth(menu_list[i]) : str_size_max); //横の最大の長さを求める
	}
	return return_number;
}