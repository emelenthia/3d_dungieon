#include "Character_Data_Save.h"
#include"DxLib.h"
#include"Defines.h"

Character_Data_Save::Character_Data_Save()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		fp[i] = NULL;
		strcpy(file_name[i], "null");
	}
}


Character_Data_Save::~Character_Data_Save()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		if (fp[i] != NULL)
		{
			fclose(fp[i]);
		}
	}
}


void Character_Data_Save::Load_Char(char *file_pointer,int n)
{
	if (!(strcmp(file_name[n], "null")))
	{
		strcpy(file_name[n], file_pointer); //元のファイル名を覚えておく。ゲーム自体には意味がない
	}
	fp[n] = fopen(file_pointer, "r"); //指定されたファイルを開く

	if (fp[n] == NULL) //エラー処理
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name[n]);
		WaitKey();
		DxLib_End();				// ＤＸライブラリ使用の終了処理
		exit(1);
	}

	fscanf(fp[n], "%d", &in_team[n]);
	if (in_team)
	{
		fscanf(fp[n], "%d", &exp[n]);
		fscanf(fp[n], "%d", &job[n]);
		fscanf(fp[n], "%d", &Lv[n]);
		fscanf_s(fp[n], "%s", name[n], 20);
		fscanf(fp[n], "%d", &in_party[n]);
		fscanf(fp[n], "%d", &status_c[n].hp);
		fscanf(fp[n], "%d", &status_c[n].tp);
		fscanf(fp[n], "%d", &lastchoosef[n]);
		fscanf(fp[n], "%d", &lastchoosef_skill[n]);
	}
}