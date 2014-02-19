#pragma once
#include "Field_Base_Data.h"
#include"Objects.h"

class Ice_Field :
	public Field_Base_Data
{
public:
	Ice_Field();
	~Ice_Field();
	void Draw();
	int mapchip_h[5]; //マップチップのハンドル
	int mapchip_h2[40];
	char map_array[30][30]; //このマップのマップチップの並び
	Objects stoneobj[2];
	int Reaction();
};

