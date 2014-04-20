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
	void DrawPartyType2(int party_type); //決定後の選択欄
	int mini_size_x;
	int mini_size_y;
	int mini_crevice_x; //パーティータイプ表示時の横の隙間
	int space_on_time; //長押しの間隔
	int temp_party_type;
	int keep_party_type;
	int temp_party_info[5];
	int keep_party_info[5];
	int pt_type_deside_flag;
	Character_Show_F *character_show_f;
	void DrawPartyBox(int pos_x, int pos_y, int color);
	int countdpb; //1FにDrawPartyBoxを実行した回数。現在選ばれているのを示すのに使う
	int pos_x_lu2 = 0;
	int pos_y_lu2 = 0;
	int pos_x_rd2 = 0;
	int pos_y_rd2 = 0;
	int mini_size_x2 = 0;
	int mini_size_y2 = 0;
	int crevice_x2 = 0;
	int crevice_y2 = 0;
	int nowchoose = 0; //左上から0
	int already_flag = 0;
	int choosing_place_flag = 0; //キャラの置く場所を考えているフラグ
};

