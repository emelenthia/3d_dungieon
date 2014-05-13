#include "Character_Show_F.h"
#include<DxLib.h>
#include"Flags.h"
#include"Defines.h"
#include"Key_Input.h"
#include"Guild_Scene_Base.h"


Character_Show_F::Character_Show_F()
{
	characters = Characters::GetInstance();

	black = GetColor(0, 0, 0);
	yellow = GetColor(255, 255, 0);
	darkyellow = GetColor(255, 205, 0);
	white = GetColor(255, 255, 255);
	blue = GetColor(0, 0, 255);
	darkblue = GetColor(0, 0, 80);
	lightblue = GetColor(24, 127, 196);
	green = GetColor(153, 204, 0);
	brown = GetColor(153, 51, 0);
	red = GetColor(255, 0, 0);
	fp = fopen("./scn/char/char_show.cns", "r");

	if (fp == NULL)
	{
		DrawString(0, 0, "Error. I can not open file.", yellow);
		WaitKey();
	}

	//ステータスの表現方法を読み込む
	fscanf(fp, "%d", &namemax);
	for (int i = 0; i < namemax; i++)
	{
		fscanf(fp, "%s", names[i]);
	}

}


void Character_Show_F::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透過
	DrawBox(0, 0, 640, 20, blue, TRUE); //説明欄
	numchar = 0;
	if (Flags::nowscene == 0x8011d) //ギルド画面
	{
		for (int i = 0; i < Defines::char_max; i++)
		{
			if (characters->in_team[i])
			{
				number_list[i] = numchar;
				numchar++;
			}
			else
			{
				number_list[i] = -1;
			}
		}
	}
	else //ダンジョン画面
	{
		for (int i = 0; i < Defines::char_max; i++)
		{
			if (characters->in_party[i])
			{
				number_list[i] = numchar;
				numchar++;
			}
			else
			{
				number_list[i] = -1;
			}
		}
	}

	pos_y_rd = pos_y_lu + numchar * 20;

	DrawBox(pos_x_lu, pos_y_lu, pos_x_rd, pos_y_rd, black, TRUE);

	int db_x_lu = pos_x_rd + 10;
	int db_y_lu = pos_y_lu + 22;
	int db_x_rd = pos_x_rd + 300;
	int db_y_rd = pos_y_lu + 22 + 140;
	DrawBox(db_x_rd, db_y_lu, db_x_lu, db_y_rd, darkblue, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

	DrawBox(db_x_lu - 2, db_y_lu - 22, db_x_rd + 2, db_y_lu - 2, lightblue, TRUE); //HPとか名前とか
	DrawBox(db_x_rd, db_y_lu, db_x_rd + 2, db_y_rd, lightblue, TRUE); //ステータスの周り右
	DrawBox(db_x_lu - 2, db_y_lu, db_x_lu, db_y_rd, lightblue, TRUE); //ステータスの周り左
	DrawBox(db_x_lu - 2, db_y_lu - 2, db_x_rd + 2, db_y_lu, lightblue, TRUE); //ステータスの周り上
	DrawBox(db_x_lu - 2, db_y_rd, db_x_rd + 2, db_y_rd + 2, lightblue, TRUE); //ステータスの周り下

	DrawFormatString(db_x_lu + 5, db_y_lu + 2 - 20, yellow, "%s", names[0]); //Lv
	DrawFormatString(db_x_lu + 5, db_y_lu + 2, darkyellow, "%s", names[1]); //HP
	DrawFormatString((db_x_rd - db_x_lu)*0.5 + db_x_lu + 5, db_y_lu + 2, green, "%s", names[2]); //TP
	DrawFormatString(db_x_lu + 5, db_y_lu + 22, yellow, "%s", names[3]); //ATK
	DrawFormatString(db_x_lu + 5, db_y_lu + 42, yellow, "%s", names[4]); //DEF
	DrawFormatString(db_x_lu + 5, db_y_lu + 62, yellow, "%s", names[5]); //INT
	DrawFormatString(db_x_lu + 5, db_y_lu + 82, yellow, "%s", names[6]); //RES
	DrawFormatString(db_x_lu + 5, db_y_lu + 102, yellow, "%s", names[7]); //DEX
	DrawFormatString(db_x_lu + 5, db_y_lu + 122, yellow, "%s", names[8]); //AGI

	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 42, yellow, "%s", names[9]); //EXP
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 62, yellow, "%s", names[10]); //NEXT
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 82, yellow, "%s", names[11]); //斬耐性
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 102, yellow, "%s", names[12]); //突耐性
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 122, yellow, "%s", names[13]); //欧耐性

	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 42, red, "%s", names[14]); //火耐性
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 62, blue, "%s", names[14]); //水耐性
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 82, green, "%s", names[14]); //風耐性
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 102, brown, "%s", names[14]); //土耐性
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 122, yellow, "%s", names[14]); //雷耐性

	DrawBox(pos_x_rd, pos_y_lu, pos_x_rd + 2, pos_y_rd, yellow, TRUE); //キャラクター群の周り右
	DrawBox(pos_x_lu - 2, pos_y_lu, pos_x_lu, pos_y_rd, yellow, TRUE); //キャラクター群の周り左
	DrawBox(pos_x_lu - 2, pos_y_lu - 2, pos_x_rd + 2, pos_y_lu, yellow, TRUE); //キャラクター群の周り上
	DrawBox(pos_x_lu - 2, pos_y_rd, pos_x_rd + 2, pos_y_rd + 2, yellow, TRUE); //キャラクター群の周り下
	
	DrawBox(pos_x_lu + 1, choosenow * 20 + pos_y_lu + 1, pos_x_rd - 1, (choosenow + 1) * 20 + pos_y_lu - 1, yellow, TRUE); //今選ばれてるのを示す
	int already = 0; //名前を書き終わったキャラの総数
	for (int i = 0; i < Defines::char_max; i++)
	{
		if (Flags::nowscene == 0x8011d)
		{
			if (characters->in_team[i])
			{
				DrawFormatString(pos_x_lu + 2, pos_y_lu + 2 + already * 20, (choosenow == number_list[i] ? black : white), "%s", characters->name[i]);
				if (choosenow == number_list[i])
				{
					Guild_Scene_Base::char_ran = i; //現在選ばれているキャラを表示する
					Status_ = characters->GetStatus(i);

					//現在選択されているヒロインの情報を表示
					DrawFormatString(db_x_lu + 5 + GetDrawStringWidth(names[0], strlen(names[0])) + 5, db_y_lu + 2 - 20, white, "%d", characters->Lv[i]);
					DrawFormatString(db_x_lu + 5 + GetDrawStringWidth(names[0], strlen(names[0])) + 20, db_y_lu + 2 - 20, white, "%s", characters->name[i]);
					char jobname_temp[20]; //戻り値では長さを取得できなさそうなので一時的に保存
					strcpy(jobname_temp, characters->GetJobName(i));
					DrawFormatString(db_x_lu + 200 - 0.5 * GetDrawStringWidth(jobname_temp, strlen(jobname_temp)), db_y_lu + 2 - 20, white, "%s", jobname_temp);

					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, characters->nowhp[i], white);
					DrawString(db_x_lu + 15 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, "/", white);
					DrawIntRight(db_x_lu + 20 + GetDrawFormatStringWidth("ATK9999") + GetDrawFormatStringWidth("/%d", 9999), db_y_lu + 2, Status_.hpmax, white);

					DrawIntRight((db_x_rd - db_x_lu)*0.5 + db_x_lu + 5 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, characters->nowtp[i], white);
					DrawString((db_x_rd - db_x_lu)*0.5 + db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, "/", white);
					DrawIntRight((db_x_rd - db_x_lu)*0.5 + db_x_lu + 15 + GetDrawFormatStringWidth("/%d", 9999) + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, Status_.tpmax, white);


					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 22, Status_.atk, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 42, Status_.def, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 62, Status_.int_s, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 82, Status_.res, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 102, Status_.dex, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 122, Status_.agi, white);

					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999"), db_y_lu + 42, characters->exp[i], white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999"), db_y_lu + 62, characters->Lv[i] * 10 - characters->exp[i], white);
				}
				already++;
			}
		}
	}

}


int Character_Show_F::Reaction()
{
	if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_UP] != 11)
	{
		choosenow = (choosenow > 0 ? choosenow - 1 : numchar - 1); //ループできるように
	}
	if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_DOWN] != 11)
	{
		choosenow = (choosenow < numchar - 1 ? choosenow + 1 : 0);
	}

	if (Key_Input::buff_time[KEY_INPUT_X] == 1 || (Key_Input::buff_time[KEY_INPUT_Z] == 1 && choosenow == numchar))
	{
		Flags::character_show_flag = 0;
	}
	return 0;
}


void Character_Show_F::DrawIntRight(int x, int y, int num, int color)
{
	DrawFormatString(x - GetDrawFormatStringWidth("%d", num), y, color, "%d", num);
}


int Character_Show_F::GetCharNow()
{
	int number = -1;

	for (int i = 0; i < 13; i++)
	{
		//現在選択しているキャラが見つかった場合
		if (choosenow == number_list[i])
		{
			number = i;
			break;
		}
	}

	return number;
}