#include "Battle.h"
#include "DxLib.h"
#include "Key_Input.h"
#include"Flags.h"
#include"Colors.h"
#include"Dungeon.h"

#define swap(a,b) a^=b^=a^=b

#define nfscanf(scan_target, format_text, ...) nfscanf_(__LINE__,__FILE__,scan_target, format_text,__VA_ARGS__);
void Battle::nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...)
{
	FILE* scanf_fp;
	int ret = 0;
	va_list args;

	scanf_fp = fopen("scanf_log.txt", "w");
	fprintf(scanf_fp, "%s\n行:%d\n", file, line);
	fclose(scanf_fp);

	va_start(args, format_text);
	ret = vfscanf(scan_target, format_text, args);
	va_end(args);

}

Battle::Battle(int ne,int* monster_number)
{
	randomer = Randomer::GetInstance();
	numenemy = ne;


	testgraph = LoadGraph("./pics/battle/戦闘画面背景画像/640×480/pipo-battlebg002.jpg");
	for (int i = 0; i < 5; i++)
	{
		monsters[i] = NULL;
	}
	for (int i = 0; i < numenemy; i++)
	{
		monsters[i] = new Monsters(monster_number[i]);
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
	for (int i = 0; i < numenemy; i++)
	{
		active_point[i + 5] = i * 2 + 3;
	}
	minichar_size_x = 75;
	minichar_size_y = 24;

	thickfont_h = CreateFontToHandle(NULL, 21, 5);
}


Battle::~Battle()
{
}


void Battle::Draw()
{
	DrawExtendGraph(0, 0, 640, 480, testgraph, TRUE);
	DrawString(220, 120, "これは仮の戦闘シーンです", GetColor(0, 0, 255));
	DrawString(220, 160, "決定キーで戻ります", GetColor(0, 0, 255));

	DrawMonster();
	DrawMiniChar();
	//party->Draw();
	DrawCanActive();
}


int Battle::Reaction()
{
	int r = 0;
	if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
	{
		Flags::battleflag = -1;
		for (int i = 0; i < numenemy; i++)
		{
			if (monsters[i] != NULL)
			{
				delete monsters[i];
			}
		}
	}
	for (int i = 0; i < numenemy; i++)
	{
		if (!monsters[i]->Status_c.alive)
		{
			break;
		}
		if (i == numenemy - 1)
		{
			winflag++;
		}
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


void Battle::DrawCanActive()
{
	const int pos_x_lu = 5;
	const int pos_y_lu = 480 - 30 * 6;
	const int pos_x_rd = 160 - 10;
	int i = 0;

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透化

	DrawBox(pos_x_lu + 15, pos_y_lu + nowchoosef * 30 + 5, pos_x_rd, pos_y_lu + nowchoosef * 30 + 5 + 21, Colors::yellow, TRUE); //現在選んでるの

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

	if (unionattackflag)
	{
		DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 5, Colors::white, thickfont_h, "協力攻撃");
	}
	DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 35, Colors::white, thickfont_h, "攻撃");
	DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 65, Colors::white, thickfont_h, "スキル");
	DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 95, Colors::white, thickfont_h, "防御");
	DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 125, Colors::white, thickfont_h, "アイテム");
	DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 155, Colors::white, thickfont_h, "逃げる");
}


void Battle::DrawStringsCenterToHandle(int cpos_x, int cpos_y, int color_h,int font_h, const char* str)
{
	DrawFormatStringToHandle(cpos_x - GetDrawStringWidthToHandle(str,strlen(str),font_h) / 2, cpos_y, Colors::white, font_h, str);
}


void Battle::DrawMonster()
{

	switch (numenemy)
	{
	case 1:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 2 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		break;
	case 2:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[1]->Status_c.alive)
		{
			monsters[1]->Draw(640 / 2 + 640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		break;
	case 3:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[1]->Status_c.alive)
		{
			monsters[1]->Draw(640 / 2 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[2]->Status_c.alive)
		{
			monsters[2]->Draw(640 / 2 + 640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		break;
	case 4:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[1]->Status_c.alive)
		{
			monsters[1]->Draw(640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[2]->Status_c.alive)
		{
			monsters[2]->Draw(640 / 2 + 640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[3]->Status_c.alive)
		{
			monsters[3]->Draw(640 / 2 + 640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		break;
	case 5:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[1]->Status_c.alive)
		{
			monsters[1]->Draw(640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[2]->Status_c.alive)
		{
			monsters[2]->Draw(640 / 2 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[3]->Status_c.alive)
		{
			monsters[3]->Draw(640 / 2 + 640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		if (monsters[4]->Status_c.alive)
		{
			monsters[4]->Draw(640 / 2 + 640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey);
		}
		break;
	default:
		break;
	}
}