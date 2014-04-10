#pragma once
#include "Guild_Scene_Base.h"
#include"Characters.h"
#include"Party.h"
#include"Character_Show_F.h"

class Guild_PT :
	public Guild_Scene_Base
{
public:
	Guild_PT();
	~Guild_PT();
	int Reaction();
	void Draw();
	Characters *characters;
	int pos_x_lu;
	int pos_y_lu;
	int size_x;
	int size_y; //一つ当たりの縦の大きさ
	int crevice_y; //縦の隙間
	int guild_pt_flag;
	Party *party;
	void DrawHitogata(int pos_x, int pos_y, int color);
	void DrawPartyType(int pos_x, int pos_t, int party_type);
	int mini_size_x;
	int mini_size_y;
	int mini_crevice_x; //パーティータイプ表示時の横の隙間
	int temp_party_type;
	int space_on_time;
	int keep_party_type;
	int pt_type_deside_flag;
	Character_Show_F *character_show_f;
};

