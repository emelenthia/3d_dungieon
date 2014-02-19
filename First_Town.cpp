#include "First_Town.h"
#include<DxLib.h>
#include"Field.h"


First_Town::First_Town()
{
	int i = 0, i2 = 0;
	LoadDivGraph("./pics/field/world_kusa-tuti.png", 5, 1, 5, 16, 16, mapchip_h);
	LoadDivGraph("./pics/field/[Base]640x480_SampleChip_pipo.png", 40, 8, 5, 32, 32, mapchip_h2);

	while (i2 < 30)
	{
		while (i < 30)
		{
			map_array[i2][i] = GetRand(4);
			i++;
		}
		i = 0;
		i2++;
	}

	sign.MakeObject(100, 100, 100, 100, 132, 132, mapchip_h2[19]); //位置情報などの決定
	sign.LoadTalk("./scn/first_town/object_sign1.cns"); //会話ファイルを読み込む
	sign2.MakeObject(164, 164, 164, 164, 196, 196, mapchip_h2[19]);
	sign2.LoadTalk("./scn/first_town/object_sign2.cns"); //会話ファイルを読み込む
	
	testteki.MakeObject(192, 32, 192, 32, 224, 64, mapchip_h2[6]);
	testteki.LoadTalk("./scn/first_town/object_teki1.cns"); //会話ファイルを読み込む
}


First_Town::~First_Town()
{
}


void First_Town::Draw()
{

	int x = 0, y = 0, i = 0;

	while (y < 30)
	{
		while (x < 30)
		{
			DrawExtendGraph(y * 32 - Field::left_upper_x, x * 32 - Field::left_upper_y, (y + 1) * 32 - Field::left_upper_x, (x + 1) * 32 - Field::left_upper_y, mapchip_h[map_array[y][x]], TRUE); //現在の左上の座標を(0,0)になるように描画
			x++;
		}
		x = 0;
		y++;
	}
	sign.Draw();
	sign2.Draw();
	testteki.Draw();
}


int First_Town::Reaction()
{
	int r = 0, i = 0;
	sign.HitCheck();
	sign.Reaction();
	sign2.HitCheck();
	sign2.Reaction();
	testteki.HitCheck();
	r = testteki.Reaction();
	return r;
}