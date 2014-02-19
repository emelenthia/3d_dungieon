#include "World.h"
#include"DxLib.h"
#include"Field.h"

World::World()
{
	LoadDivGraph("./pics/field/kusa1-kusa3.png", 5, 1, 5, 16, 16, mapchip_h);
	LoadDivGraph("./pics/field/[Base]640x480_SampleChip_pipo.png", 40, 8, 5, 32, 32, mapchip_h2);
	LoadDivGraph("./pics/field/[Base]WorldMap_pipo.png", 40, 8, 5, 32, 32, world_mapchip_h);
	for (int i2; i2 < 30;i2++)
	{
		for (int i; i < 30;i++)
		{
			map_array[i2][i] = GetRand(4);
			i++;
		}
	}
}


World::~World()
{
}


void World::Draw()
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
}