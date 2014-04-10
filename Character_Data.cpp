#include "Character_Data.h"
#include<stdio.h>
#include"DxLib.h"
#include"Defines.h"

Character_Data::Character_Data()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		fp_n_s[i] = NULL;
		strcpy(file_name_n_s[i], "null");
	}
}


Character_Data::~Character_Data()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		if (fp_n_s[i] != NULL)
		{
			fclose(fp_n_s[i]);
		}
	}
}


void Character_Data::Load_Char_n_s(char *file_pointer, char *file_pointer_save,int n)
{
	if (!(strcmp(file_name_n_s[n], "null")))
	{
		strcpy(file_name_n_s[n], file_pointer); //元のファイル名を覚えておく。ゲーム自体には意味がない
	}
	fp_n_s[n] = fopen(file_pointer, "r"); //指定されたファイルを開く

	if (fp_n_s[n] == NULL) //エラー処理
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name_n_s[n]);
		WaitKey();
		DxLib_End();				// ＤＸライブラリ使用の終了処理
		exit(1);
	}

	fscanf(fp_n_s[n], "%d", &job_system[n]);
	fscanf_s(fp_n_s[n], "%s", char_h_name[n][0], 99);
		//fscanf_s(fp_n_s[n], "%s", char_h_i_name[n][i], 49);
	char_h[n][0] = LoadGraph(char_h_name[n][0]);
		//char_h_i[i] = LoadGraph(char_h_i_name[i]);
	if (char_h[n][0] == -1) //エラー処理
		{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", char_h_name[n][0]);
			WaitKey();
			DxLib_End();				// ＤＸライブラリ使用の終了処理
			exit(1);
		}
		//fscanf_s(fp, "%s", char_h_i_name[i], 49);
	
	//継承元でファイルを開く
	Load_Char(file_pointer_save, n);
}


int Character_Data::GetStatus(int n,int want)
{
	int temp = 0; //返り値

	switch (job_system[n])
	{
	case 1: //ファイター系
		switch (job[n])
		{
		case 1: //ファイター
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //パラディン
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //バーサーカー
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //ヴァルキリー
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //侍
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //ダークロード
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 2: //マジックユーザー系
		switch (job[n])
		{
		case 1: //マジックユーザー
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //ソーサレス
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //エンチャントレス
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //プリーステス
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //ウィッチ
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //マジカルプリンセス
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 7: //セージ
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 8: //ビショップ
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 3: //スカウト系
		switch (job[n])
		{
		case 1: //スカウト
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //アーチャー
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //アサシン
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //スナイパー
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //トレジャーハンター
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //くノ一
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 4: //メイド系
		switch (job[n])
		{
		case 1: //メイド
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //バード
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //ダンサー
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //ディーヴァ
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //ミストレス
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //エトワール
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 5: //スピエラー系
		switch (job[n])
		{
		case 1: //スピエラー
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //ドールマスター
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //トリックスター
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //ソウルサモナー
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //パピヨン
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //ジョーカー
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
	return temp;
}


char* Character_Data::GetJobName(int n)
{
	char job_name[20];
	switch (job_system[n])
	{
	case 1: //ファイター系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "ファイター");
			break;
		case 2:
			strcpy(job_name, "パラディン");
			break;
		case 3:
			strcpy(job_name, "バーサーカー");
			break;
		case 4:
			strcpy(job_name, "ヴァルキリー");
			break;
		case 5:
			strcpy(job_name, "侍");
			break;
		case 6:
			strcpy(job_name, "ダークロード");
			break;
		default:
			break;
		}
		break;
	case 2: //マジックユーザー系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "マジックユーザー");
			break;
		case 2:
			strcpy(job_name, "ソーサレス");
			break;
		case 3:
			strcpy(job_name, "エンチャントレス");
			break;
		case 4:
			strcpy(job_name, "プリーステス");
			break;
		case 5:
			strcpy(job_name, "ウィッチ");
			break;
		case 6:
			strcpy(job_name, "マジカルプリンセス");
			break;
		case 7:
			strcpy(job_name, "セージ");
			break;
		case 8:
			strcpy(job_name, "ビショップ");
			break;
		default:
			break;
		}
		break;
	case 3: //スカウト系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "スカウト");
			break;
		case 2:
			strcpy(job_name, "アーチャー");
			break;
		case 3:
			strcpy(job_name, "アサシン");
			break;
		case 4:
			strcpy(job_name, "スナイパー");
			break;
		case 5:
			strcpy(job_name, "トレジャーハンター");
			break;
		case 6:
			strcpy(job_name, "くノ一");
			break;
		default:
			break;
		}
		break;
	case 4: //メイド系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "メイド");
			break;
		case 2:
			strcpy(job_name, "バード");
			break;
		case 3:
			strcpy(job_name, "ダンサー");
			break;
		case 4:
			strcpy(job_name, "ディーヴァ");
			break;
		case 5:
			strcpy(job_name, "ミストレス");
			break;
		case 6:
			strcpy(job_name, "エトワール");
			break;
		default:
			break;
		}
		break;
	case 5: //スピエラー系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "スピエラー");
			break;
		case 2:
			strcpy(job_name, "ドールマスター");
			break;
		case 3:
			strcpy(job_name, "トリックスター");
			break;
		case 4:
			strcpy(job_name, "ソウルサモナー");
			break;
		case 5:
			strcpy(job_name, "パピヨン");
			break;
		case 6:
			strcpy(job_name, "ジョーカー");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}


	return job_name;
}