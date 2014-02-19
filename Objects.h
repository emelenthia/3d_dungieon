#pragma once
class Objects
{
public:
	Objects();
	~Objects();
	int checkhitflag; //通り抜け不可能判定。0なら通り抜けられる
	void HitCheck(); //衝突判定
	virtual void Draw();
	void MakeObject(int temporary_pos_x, int temporary_pos_y, int temporary_pos_x_lu, int temporary_pos_y_lu, 
		int temporary_pos_x_rd, int temporary_pos_y_rd, int temporary_hundle_number, int temporary_checkhitflag = 1); //オブジェクトを初期化します
	int pos_x_lu; //オブジェクトの左上のx座標。判定用
	int pos_y_lu;
	int pos_x_rd;
	int pos_y_rd; //オブジェクトの右下のy座標
	int pos_x; //オブジェクトの左上のx座標。描画用
	int pos_y; //オブジェクトの左上のx座標。描画用
	int mapchip_h2[40]; //画像のハンドル
	int hundle_number; //オブジェクトの画像のハンドル
};

