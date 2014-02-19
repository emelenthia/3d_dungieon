#pragma once
#include "Field_Base_Data.h"
class World :
	public Field_Base_Data
{
public:
	World();
	~World();
	int mapchip_h[5]; //マップチップのハンドル
	int mapchip_h2[40];
	int world_mapchip_h[23*8];
	char map_array[30][30]; //このマップのマップチップの並び
	void Draw();
};