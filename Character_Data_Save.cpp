#include "Character_Data_Save.h"
#include"DxLib.h"


Character_Data_Save::Character_Data_Save()
{
	fp = NULL;
	strcpy(file_name, "null");
}


Character_Data_Save::~Character_Data_Save()
{
	if (fp != NULL)
	{
		fclose(fp);
	}
}


void Character_Data_Save::Load_Char(char *file_pointer)
{
	if (!(strcmp(file_name, "null")))
	{
		strcpy(file_name, file_pointer); //元のファイル名を覚えておく。ゲーム自体には意味がない
	}
	fp = fopen(file_pointer, "r"); //指定されたファイルを開く

	if (fp == NULL) //エラー処理
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name);
		WaitKey();
		DxLib_End();				// ＤＸライブラリ使用の終了処理
		exit(1);
	}

	fscanf_s(fp, "%d", &in_team, 1);
	if (in_team)
	{
		fscanf(fp, "%d", &exp);
		fscanf(fp, "%d", &job);
		fscanf_s(fp, "%s", name, 20);
	}
}