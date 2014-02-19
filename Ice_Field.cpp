#include "Ice_Field.h"
#include<DxLib.h>
#include"Field.h"

Ice_Field::Ice_Field()
{
	int i = 0, i2 = 0;
	LoadDivGraph("./pics/field/[A]Ice1_pipo.png", 5, 1, 5, 16, 16, mapchip_h);
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

	stoneobj[0].MakeObject(187, 164, 187, 164, 219, 196, mapchip_h2[16]);
	stoneobj[1].MakeObject(587, 364, 587, 364, 619, 396, mapchip_h2[16]);

}


Ice_Field::~Ice_Field()
{
}


void Ice_Field::Draw()
{
	int x = 0, y = 0;

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
}


int Ice_Field::Reaction()
{
	stoneobj[0].HitCheck();
	stoneobj[1].HitCheck();
	return 0;
}