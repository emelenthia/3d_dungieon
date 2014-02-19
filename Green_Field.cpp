#include "Green_Field.h"
#include<DxLib.h>
#include"Field.h"


Green_Field::Green_Field()
{
	int i = 0, i2 = 0;
	LoadDivGraph("./pics/field/kusa1-kusa3.png", 5, 1, 5, 16, 16, mapchip_h);
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

	stumpobj[0].MakeObject(0, 0, 0, 0, 32, 32, mapchip_h2[8]);
	stumpobj[1].MakeObject(0, 32, 0, 32, 32, 64, mapchip_h2[8]);
	stumpobj[2].MakeObject(0, 64, 0, 64, 32, 96, mapchip_h2[8]);
	i = 3;
	while (i < numstumpobj) //¶‘¤‚Ì–Ø“™
	{
		stumpobj[i].MakeObject(0, i * 32 + 96, 0, i * 32 + 96, 32, i * 32 + 96 + 32, mapchip_h2[8]);
		i++;
	}

	stoneobj[0].MakeObject(64, 64, 64, 64, 96, 96, mapchip_h2[16]);
	stoneobj[1].MakeObject(96, 96, 96, 96, 128, 128, mapchip_h2[16]);
	exitobj.MakeObject(0, 0, 3, 96, 4, 192, -1);
}


Green_Field::~Green_Field()
{
}

void Green_Field::Draw()
{
	int x = 0, y = 0, i = 0;

	while (y < 30)
	{
		while (x < 30)
		{
			DrawExtendGraph(y * 32 - Field::left_upper_x, x * 32 - Field::left_upper_y, (y + 1) * 32 - Field::left_upper_x, (x + 1) * 32 - Field::left_upper_y, mapchip_h[map_array[y][x]], TRUE); //Œ»Ý‚Ì¶ã‚ÌÀ•W‚ð(0,0)‚É‚È‚é‚æ‚¤‚É•`‰æ
			x++;
		}
		x = 0;
		y++;
	}
	stoneobj[0].Draw();
	stoneobj[1].Draw();
	while (i < numstumpobj)
	{
		stumpobj[i].Draw();
		i++;
	}
	exitobj.Draw();

}


int Green_Field::Reaction()
{
	int r = 0, i = 0;
	stoneobj[0].HitCheck();
	stoneobj[1].HitCheck();
	while (i < numstumpobj)
	{
		stumpobj[i].HitCheck();
		i++;
	}
	r = exitobj.Reaction();

	return r;
}