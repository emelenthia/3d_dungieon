#pragma once
#include "Field_Base_Data.h"
#include"Objects.h"
#include"Talker.h"
#include"In_Battle.h"

class First_Town :
	public Field_Base_Data
{
public:
	First_Town();
	~First_Town();
	void Draw();
	int mapchip_h[5]; //マップチップのハンドル
	int mapchip_h2[40];
	char map_array[30][30]; //このマップのマップチップの並び
	int Reaction();
	Talker sign;
	Talker sign2;
	Talker testteki;
	//In_Battle testteki;
};

