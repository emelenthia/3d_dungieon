#include "Battle.h"
#include "DxLib.h"
#include "Key_Input.h"
#include"Flags.h"
#include"Colors.h"

#define swap(a,b) a^=b^=a^=b

Battle::Battle()
{
	numenemy = 1;
	testgraph = LoadGraph("./pics/battle/戦闘画面背景画像/640×480/pipo-battlebg002.jpg");
	for (int i = 0; i < numenemy; i++)
	{
		monsters[i] = new Monsters(0);
	}
	party = Party::GetInstance();
	characters = Characters::GetInstance();
	for (int i = 0; i < 10; i++)
	{
		turn_active[i] = 0;
	}

	active_point[0] = 2;
	active_point[1] = 7;
	active_point[2] = -1;
	active_point[3] = -1;
	active_point[4] = -1;
	active_point[5] = 5;
	active_point[6] = -1;
	active_point[7] = -1;
	active_point[8] = -1;
	active_point[9] = -1;
	minichar_size_x = 75;
	minichar_size_y = 24;
}


Battle::~Battle()
{
}


void Battle::Draw()
{
	DrawExtendGraph(0, 0, 640, 480, testgraph, TRUE);
	DrawString(220, 120, "これは仮の戦闘シーンです", GetColor(0, 0, 255));
	DrawString(220, 160, "決定キーで戻ります", GetColor(0, 0, 255));

	for (int i = 0; i < numenemy; i++)
	{
		if (monsters[i]->Status_c.agi_scale)
		{
			monsters[i]->Draw();
		}
	}

	DrawMiniChar();
	party->Draw();
}


int Battle::Reaction()
{
	int r = 0;
	if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
	{
		Flags::nowscene = 0xf1e1d;
	}
	return r;
}


void Battle::DrawMiniChar()
{
	ActiveSort();

	for (int i = 0; i < party->GetNumMember() + numenemy; i++)
	{
		if (turn_active[i] <= 4) //isplayer
		{
			//自陣だと分かるように
			DrawBox(
				640 - minichar_size_x - 15,
				360 - (i + 1) * minichar_size_y - 4 * i,
				640,
				360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
				Colors::blue, TRUE);
			//キャラ画像の表示
			DrawExtendGraph(
				640 - minichar_size_x,
				360 - (i + 1) * minichar_size_y - 4 * i,
				640,
				360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
				characters->char_h_i[party->party_info[turn_active[i]]][characters->job[party->party_info[turn_active[i]]]], TRUE);
			//デバッグ的な
			DrawFormatString(640 - minichar_size_x - 15, 360 - (i + 1) * minichar_size_y - 4 * i, Colors::purple, "%d", active_point[turn_active[i]]);
		}
		else //!isplayer
		{
			//敵陣だと分かるように
			DrawBox(
				640 - minichar_size_x - 15,
				360 - (i + 1) * minichar_size_y - 4 * i,
				640,
				360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
				Colors::red, TRUE);
			//キャラ画像の表示
			DrawExtendGraph(
				640 - minichar_size_x,
				360 - (i + 1) * minichar_size_y - 4 * i,
				640,
				360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
				monsters[turn_active[i] - 5]->graph_m, TRUE);
			//デバッグ的な
			DrawFormatString(640 - minichar_size_x - 15, 360 - (i + 1) * minichar_size_y - 4 * i, Colors::purple, "%d", active_point[turn_active[i]]);
		}
	}

	//現在行動中のキャラを示す
	DrawBox(640 - minichar_size_x - 15 - 100, 360 - minichar_size_y, 640 - minichar_size_x - 15 - 5, 360, Colors::blue, TRUE);
	DrawFormatString(640 - minichar_size_x - 15 - 90, 360 - minichar_size_y + 4, Colors::white, "ACTIVE ⇒", TRUE);
	
}


void Battle::ActiveSort()
{
	int temp_number = 0, temp_min = 0;
	bool finishflag = 0;


	for (int n = 0; n < 10; n++)
	{
		temp_number = -1;
		temp_min = INT_MAX;
		for (int i = 0; i < 10; i++)
		{
			//既に取得したものはするー
			for (int i2 = 0; i2<n; i2++)
			{
				if (turn_active[i2] == i)
				{
					finishflag = TRUE;
					break;
				}
			}
			if (!finishflag)
			{
				if (temp_min>active_point[i] && active_point[i] >= 0) //必ず0以上
				{
					temp_min = active_point[i];
					temp_number = i;
				}
			}
			else
			{
				finishflag = FALSE;
			}
		}
		turn_active[n] = temp_number;
	}
}