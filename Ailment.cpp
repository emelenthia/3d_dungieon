#include "Ailment.h"
#include"DxLib.h"

Ailment* Ailment::instance;

Ailment::Ailment()
{
	LoadAilment();
}


Ailment::~Ailment()
{
}


void Ailment::LoadAilment()
{
	FILE* fp, *fp2;
	char dammy[256];
	int temp[Defines::AILMENT_MAX_LEVEL];
	fp = fopen("./scn/status_ailment/status_ailment.txt", "r"); //状態異常名を記したファイル
	fp2 = fopen("./scn/status_ailment/ailment_value.txt", "r"); //状態異常の詳細を記したファイル
	if (fp == NULL || fp2 == NULL)
	{
		//TODO:エラー表示をきちんとできるようにする
		DrawFormatString(0, 0, Colors::white, "Error in LoadAilMent()");
		ScreenFlip();
		WaitKey();
		return;
	}

	//まずは状態異常名を読み込む
	for (int i = 0; i < Defines::AILMENT_MAX; i++)
	{
		fscanf(fp, "%s", m_ailment[i].name);
	}

	for (int i = 0; i < Defines::AILMENT_MAX; i++)
	{
		//読み飛ばす
		fscanf(fp2, "%s", dammy);
		//バフデバフ
		fscanf(fp2, "%d", &(m_ailment[i].de_buff));
		//改行文字を読み飛ばす…必要はないらしい
		//fscanf(fp2, "%s", dammy);
		//ターン数
		LoadInts(fp2, temp, Defines::AILMENT_MAX_LEVEL);
		for (int level = 0; level < Defines::AILMENT_MAX_LEVEL; level++)
		{
			m_ailment[i].turns[level] = temp[level];
		}
		//歩数
		LoadInts(fp2, temp, Defines::AILMENT_MAX_LEVEL);
		for (int level = 0; level < Defines::AILMENT_MAX_LEVEL; level++)
		{
			m_ailment[i].walks[level] = temp[level];
		}
	}
	
	fclose(fp);
	fclose(fp2);
}


