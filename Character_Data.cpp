#include"Character_Data.h"
#include<stdio.h>
#include"DxLib.h"
#include"Defines.h"
#include"Character_Data_Save.h"

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
	
	
	//画像の読み込み
	for (int i = 0; i < 1; i++) //画像が増えた時の対処ができるようにする
	{
		fscanf_s(fp_n_s[n], "%s", char_h_name[n][i], 99);
		char_h[n][i] = LoadGraph(char_h_name[n][i]);


		fscanf_s(fp_n_s[n], "%s", char_h_i_name[n][i], 99);
		char_h_i[n][i] = LoadGraph(char_h_i_name[n][i]);
	}
	//とりあえず全部同じ画像を使う
	for (int i = 0; i < 10; i++)
	{
		char_h[n][i] = char_h[n][0];
		char_h_i[n][i] = char_h_i[n][0];
	}



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
	double temp = 0; //返り値。doubleなのは警告がめんどくさいから

	switch (job_system[n])
	{
	case 1: //ファイター系
		switch (job[n])
		{
		case 1: //ファイター
			switch (want)
			{
			case 1:
				temp = Lv[n] * 0.96 + 5;
				break;
			case 2:
				temp = Lv[n] * 0.9 + 3;
				break;
			case 3:
				temp = Lv[n] * 0.56 + 3;
				break;
			case 4:
				temp = Lv[n] * 0.74 + 2;
				break;
			case 5:
				temp = Lv[n] * 0.84 + 7;
				break;
			case 6:
				temp = Lv[n] * 0.66 + 5;
				break;
			case 7:
				temp = Lv[n] * 12.32 + 42;
				break;
			case 8:
				temp = Lv[n] * 2.46 + 12;
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
	return (int)temp;
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


char* Character_Data::GetJobNameabb(int n)
{
	char job_name[5];
	switch (job_system[n])
	{
	case 1: //ファイター系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "FT");
			break;
		case 2:
			strcpy(job_name, "PL");
			break;
		case 3:
			strcpy(job_name, "BE");
			break;
		case 4:
			strcpy(job_name, "VL");
			break;
		case 5:
			strcpy(job_name, "SA");
			break;
		case 6:
			strcpy(job_name, "DL");
			break;
		default:
			break;
		}
		break;
	case 2: //マジックユーザー系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "MU");
			break;
		case 2:
			strcpy(job_name, "SO");
			break;
		case 3:
			strcpy(job_name, "EN");
			break;
		case 4:
			strcpy(job_name, "PR");
			break;
		case 5:
			strcpy(job_name, "WT");
			break;
		case 6:
			strcpy(job_name, "MP");
			break;
		case 7:
			strcpy(job_name, "SG");
			break;
		case 8:
			strcpy(job_name, "BS");
			break;
		default:
			break;
		}
		break;
	case 3: //スカウト系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "SC");
			break;
		case 2:
			strcpy(job_name, "AR");
			break;
		case 3:
			strcpy(job_name, "AS");
			break;
		case 4:
			strcpy(job_name, "SN");
			break;
		case 5:
			strcpy(job_name, "TH");
			break;
		case 6:
			strcpy(job_name, "KN");
			break;
		default:
			break;
		}
		break;
	case 4: //メイド系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "MD");
			break;
		case 2:
			strcpy(job_name, "BD");
			break;
		case 3:
			strcpy(job_name, "DN");
			break;
		case 4:
			strcpy(job_name, "DI");
			break;
		case 5:
			strcpy(job_name, "MI");
			break;
		case 6:
			strcpy(job_name, "ET");
			break;
		default:
			break;
		}
		break;
	case 5: //スピエラー系
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "SP");
			break;
		case 2:
			strcpy(job_name, "DM");
			break;
		case 3:
			strcpy(job_name, "TS");
			break;
		case 4:
			strcpy(job_name, "SS");
			break;
		case 5:
			strcpy(job_name, "PA");
			break;
		case 6:
			strcpy(job_name, "JO");
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


status Character_Data::GetStatus(int n)
{
	status Status_; //返り値
	double temp_atk = 0; //警告の為にキャストするのが面倒なため
	double temp_def = 0;
	double temp_int_s = 0;
	double temp_res = 0;
	double temp_dex = 0;
	double temp_agi = 0;
	double temp_hpmax = 0;
	double temp_tpmax = 0;

	switch (job_system[n])
	{
	case 1: //ファイター系
		switch (job[n])
		{
		case 1: //ファイター
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 2: //パラディン
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 3: //バーサーカー
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 4: //ヴァルキリー
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 5: //侍
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 6: //ダークロード
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		}
	case 2: //マジックユーザー系
		switch (job[n])
		{
		case 1: //マジックユーザー
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 2: //ソーサレス
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 3: //エンチャントレス
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 4: //プリーステス
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 5: //ウィッチ
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 6: //マジカルプリンセス
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 7: //セージ
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 8: //ビショップ
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		default:
			break;
		}
		break;
	case 3: //スカウト系
		switch (job[n])
		{
		case 1: //スカウト
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 2: //アーチャー
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 3: //アサシン
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 4: //スナイパー
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 5: //トレジャーハンター
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 6: //くノ一
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		default:
			break;
		}
		break;
	case 4: //メイド系
		switch (job[n])
		{
		case 1:
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 2: //バード
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 3: //ダンサー
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 4: //ディーヴァ
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 5: //ミストレス
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 6: //エトワール
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
		default:
			break;
		}
		break;
	case 5: //スピエラー系
		switch (job[n])
		{
		case 1: //スピエラー
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 2: //ドールマスター
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 3: //トリックスター
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 4: //ソウルサモナー
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 5: //パピヨン
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		case 6: //ジョーカー
			temp_atk = Lv[n] * 0.96 + 5;
			temp_def = Lv[n] * 0.9 + 3;
			temp_int_s = Lv[n] * 0.56 + 3;
			temp_res = Lv[n] * 0.74 + 2;
			temp_dex = Lv[n] * 0.84 + 7;
			temp_agi = Lv[n] * 0.66 + 5;
			temp_hpmax = Lv[n] * 12.32 + 42;
			temp_tpmax = Lv[n] * 2.46 + 12;
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
	Status_.atk = (int)temp_atk;
	Status_.def = (int)temp_def;
	Status_.int_s = (int)temp_int_s;
	Status_.res = (int)temp_res;
	Status_.dex = (int)temp_dex;
	Status_.agi = (int)temp_agi;
	Status_.hpmax = (int)temp_hpmax;
	Status_.tpmax = (int)temp_tpmax;

	return Status_;
}