#pragma once
#include "PlayerBase.h"
class Players :
	public PlayerBase
{
public:
	Players();
	~Players();
	void Draw();
	void Reaction();
	int player_h[96];
	int fast_speed;
	int slow_speed;
	static int moment; //入力されている向き情報
	static int old_real_pos_x; //一歩前の位置情報
	static int old_real_pos_y; //一歩前の位置情報
	static const int pos_x_lu = 3; //接触判定の左上の座標。プレイヤーの描画位置から見た相対座標
	static const int pos_y_lu = 8; //接触判定の左上の座標
	static const int pos_x_rd = 29; //接触判定の右下の座標
	static const int pos_y_rd = 48; //接触判定の右下の座標
	static int pos_x; //描画する際のx座標
	static int pos_y;
	static int direction;
	static int ndirection; //斜めの方向。応急処置
	static int real_pos_x; //ゲーム内のx座標。640を超えてもいい方
	static int real_pos_y; //ゲーム内のx座標。480を超えてもいい方
};

