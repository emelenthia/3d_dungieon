#pragma once
#include "SceneBase.h"
#include"Field_Base_Data.h"
#include"Green_Field.h"
#include"Players.h"
#include"Ice_Field.h"
#include"First_Town.h"
#include"Menu.h"

class Field :
	public SceneBase
{
public:
	Field();
	~Field();
	void Draw();
	int Reaction();
	Field_Base_Data *now_field_pointa;
	Green_Field g_field;
	Ice_Field i_field;
	First_Town f_town;
	Players players;
	PlayerBase *now_player_pointa;
	Menu menu; //ƒƒjƒ…[‰æ–Ê
	static int now_field;
	static int left_upper_x; //¶ã‚ÌÀ•W
	static int left_upper_y; //“¯
};

