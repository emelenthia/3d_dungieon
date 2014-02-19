#pragma once
#include "Guild_Scene_Base.h"
#include"Guild_Main.h"
#include"Guild_Warehouse.h"

class Guild_Main_Scene :
	public Guild_Scene_Base
{
public:
	Guild_Main_Scene();
	~Guild_Main_Scene();
	//void Draw(int pos_x_r, int pos_y_d);
	void Draw();
	int Reaction();
	Guild_Main guild_main; //2”Ô–Ú
	Guild_Warehouse guild_warehouse; //2-01”Ô–Ú
	Guild_Scene_Base *guild_scene; //state
	int reaction_number;
};

