#include "Objects.h"
#include"Players.h"
#include"Defines.h"
#include"DxLib.h"
#include"Field.h"

Objects::Objects()
{
}


Objects::~Objects()
{
}


void Objects::HitCheck()
{
	if (checkhitflag) //通り抜け不可能設定のオブジェクト
	{
		int checkpoint = 0;
		//通り抜けできないように
		if ((Players::real_pos_x + Players::pos_x_lu < pos_x_lu && pos_x_lu < Players::real_pos_x + Players::pos_x_rd) || //オブジェクトにプレイヤーが引っ掛かった場合
			(Players::real_pos_x + Players::pos_x_lu < pos_x_rd && pos_x_rd < Players::real_pos_x + Players::pos_x_rd))
		{
			checkpoint++;
		}
		if ((Players::real_pos_y + Players::pos_y_lu < pos_y_lu && pos_y_lu < Players::real_pos_y + Players::pos_y_rd) ||
			(Players::real_pos_y + Players::pos_y_lu < pos_y_rd && pos_y_rd < Players::real_pos_y + Players::pos_y_rd))
		{
			checkpoint++;
		}
		if (Players::real_pos_x + Players::pos_x_lu >= pos_x_lu && Players::real_pos_x + Players::pos_x_rd <= pos_x_rd)//プレイヤーよりオブジェクトが大きい場合
		{
			checkpoint++;
		}
		if (Players::real_pos_y + Players::pos_y_lu >= pos_y_lu && Players::real_pos_y + Players::pos_y_rd <= pos_y_rd)
		{
			checkpoint++;
		}

		if (checkpoint >= 2)
		{
			if (!Players::ndirection)
			{
				if (Players::direction == 2) //右を向いている(左からぶつかった)場合
				{
					Players::real_pos_x = pos_x_lu - Defines::player_size_x;
					Players::real_pos_x += (Defines::player_size_x - Players::pos_x_rd); //調整
				}

				if (Players::direction == 1) //左を向いている
				{
					Players::real_pos_x = pos_x_rd;
					Players::real_pos_x -= Players::pos_x_lu;
				}

				if (Players::direction == 0) //下を向いている(上からぶつかった)場合
				{
					Players::real_pos_y = pos_y_lu - Defines::player_size_y;
					Players::real_pos_y += (Defines::player_size_y - Players::pos_y_rd);
				}

				if (Players::direction == 3) //上を向いている
				{
					Players::real_pos_y = pos_y_rd;
					Players::real_pos_y -= Players::pos_y_lu;
				}
			}
			else //斜め移動の場合
			{
				if (Players::ndirection == 1) //左上を向いている(右下からぶつかった)場合
				{
					if (Players::old_real_pos_y + Players::pos_y_lu >= pos_y_rd) //オブジェクトより下にいる場合
					{
						Players::real_pos_y = pos_y_rd;
						Players::real_pos_y -= Players::pos_y_lu;
					}
					else if (Players::old_real_pos_x + Players::pos_x_lu >= pos_x_rd) //オブジェクトより右にいる場合
					{
						Players::real_pos_x = pos_x_rd;
						Players::real_pos_x -= Players::pos_x_lu;
					}
				}

				if (Players::ndirection == 2) //右上を向いている(左下からぶつかった)場合
				{
					if (Players::old_real_pos_y + Players::pos_y_lu >= pos_y_rd) //オブジェクトより下にいる場合
					{
						Players::real_pos_y = pos_y_rd;
						Players::real_pos_y -= Players::pos_y_lu;
					}
					else if (Players::old_real_pos_x + Players::pos_x_rd <= pos_x_lu) //オブジェクトより左にいる場合
					{
						Players::real_pos_x = pos_x_lu - Defines::player_size_x;
						Players::real_pos_x += (Defines::player_size_x - Players::pos_x_rd); //調整
					}
				}

				if (Players::ndirection == 3) //左下を向いている
				{
					if (Players::old_real_pos_y + Players::pos_y_rd <= pos_y_lu) //オブジェクトより上にいる場合
					{
						Players::real_pos_y = pos_y_lu - Defines::player_size_y;
						Players::real_pos_y += (Defines::player_size_y - Players::pos_y_rd);
					}
					else if (Players::old_real_pos_x + Players::pos_x_lu >= pos_x_rd) //オブジェクトより右にいる場合
					{
						Players::real_pos_x = pos_x_rd;
						Players::real_pos_x -= Players::pos_x_lu;
					}
				}

				if (Players::ndirection == 4) //右下を向いている
				{
					if (Players::old_real_pos_y + Players::pos_y_rd <= pos_y_lu) //オブジェクトより上にいる場合
					{
						Players::real_pos_y = pos_y_lu - Defines::player_size_y;
						Players::real_pos_y += (Defines::player_size_y - Players::pos_y_rd);
					}
					else if (Players::old_real_pos_x + Players::pos_x_rd <= pos_x_lu) //オブジェクトより左にいる場合
					{
						Players::real_pos_x = pos_x_lu - Defines::player_size_x;
						Players::real_pos_x += (Defines::player_size_x - Players::pos_x_rd); //調整
					}
				}

			}
		}
	}
	
}


void Objects::Draw()
{
	if (hundle_number != -1) //-1は透明な画像
	{
		DrawGraph(pos_x - Field::left_upper_x, pos_y - Field::left_upper_y, hundle_number, TRUE); //画面がずれた時にきちんとずれる様に
	}

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透化
	DrawBox(pos_x_lu - Field::left_upper_x, pos_y_lu - Field::left_upper_y, pos_x_rd - Field::left_upper_x, pos_y_rd - Field::left_upper_y, GetColor(255, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す


	DrawFormatString(0, 160, GetColor(255, 0, 255), "pos_x:%d", Players::real_pos_x);
	DrawFormatString(0, 180, GetColor(255, 0, 255), "pos_y:%d", Players::real_pos_y);
	DrawFormatString(0, 200, GetColor(255, 0, 255), "direction:%d", Players::direction);
	DrawFormatString(0, 220, GetColor(255, 0, 255), "ndirection:%d", Players::ndirection);
	DrawFormatString(0, 240, GetColor(255, 0, 255), "o_pos(x,y):(%d,%d)", Players::old_real_pos_x, Players::old_real_pos_y);
	DrawFormatString(0, 260, GetColor(255, 0, 255), "F_l_u:(%d,%d)", Field::left_upper_x, Field::left_upper_y);
}


void Objects::MakeObject(int temporary_pos_x, int temporary_pos_y, int temporary_pos_x_lu, 
	int temporary_pos_y_lu, int temporary_pos_x_rd, int temporary_pos_y_rd,int temporary_hundle_number,int temporary_checkhitflag)
{
	pos_x = temporary_pos_x;
	pos_y = temporary_pos_y;
	pos_x_lu = temporary_pos_x_lu;
	pos_y_lu = temporary_pos_y_lu;
	pos_x_rd = temporary_pos_x_rd;
	pos_y_rd = temporary_pos_y_rd;
	hundle_number = temporary_hundle_number;
	checkhitflag = temporary_checkhitflag;
}