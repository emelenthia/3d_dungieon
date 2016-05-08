#pragma once
#include<stdio.h>
#include"Characters.h"

class Party
{
public:
	static Party* instance;
	static Party* GetInstance()
	{
		if (instance == NULL)instance = new Party;
		return instance;
	}

	void Draw();
	int party_type; //編成の形。0でキャラなし。
					//			11でキャラ1体。
					//			21でキャラ2体。かつ前列二人。
					//			22でキャラ2体。かつ前後列各一人。
					//			31でキャラ3体。かつ前列三人。
					//			32でキャラ3体。かつ前列二人、後列一人。
					//			33でキャラ3体。かつ前列一人、後列二人。
					//			41でキャラ4体。かつ前列三人、後列一人。
					//			42でキャラ4体。かつ前後列各二人。
					//			43でキャラ4体。かつ前列一人、後列三人。
					//			51でキャラ5体。かつ前列三人、後列二人。
					//			52でキャラ5体。かつ前列二人、後列三人。
	int party_info[5]; //左上から順に0番目にいるキャラの番号
	FILE* fp;
	int pos_x_lu_territory; //パーティの描写に使える範囲の左上のx座標
	int pos_y_lu_territory; //パーティの描写に使える範囲の左上のy座標
	int pos_x_rd_territory; //パーティの描写に使える範囲の右下のx座標
	int pos_y_rd_territory; //パーティの描写に使える範囲の右下のy座標
	int crevice_x; //キャラ毎の隙間の横の大きさ
	int crevice_y; //キャラ毎の隙間の縦の大きさ
	int size_x; //キャラ描画枠の横の大きさ
	int size_y; //キャラ描画枠の縦の大きさ
	int countdbt; // DrawBox_tを実行した回数
	void DrawBox_t(int front_or_back,float left_pos_number); //0で前、1で後。0で左上、1で真ん中、0.5単位で2まで
	int testgraph, testgraph2;
	Characters *characters;
	void Save();
	void DrawPartyType();
	int GetNumMember();
private:
	// 生成やコピーを禁止する
	Party();
	~Party();
	Party(const Party& rhs);
	Party& operator=(const Party& rhs);
};

