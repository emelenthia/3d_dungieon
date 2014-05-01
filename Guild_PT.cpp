#include "Guild_PT.h"
#include"DxLib.h"
#include"Defines.h"

Guild_PT::Guild_PT()
{
	characters = Characters::GetInstance();
	party = Party::GetInstance(); 
	pos_x_lu = 2;
	pos_y_lu = 45;
	size_x = 400;
	size_y = 47;
	crevice_y = 2;
	guild_pt_flag = 0;
	mini_size_x = 55;
	mini_size_y = 44;
	mini_crevice_x = 18;
	pt_type_deside_flag = 0;
	space_on_time = 6;
	character_show_f = NULL;
	pos_x_lu2 = 460;
	pos_y_lu2 = 240;
	pos_x_rd2 = 630;
	pos_y_rd2 = 320;
	crevice_x2 = 10;
	crevice_y2 = 20;
	mini_size_x2 = (pos_x_rd2 - pos_x_lu2 - 2 * crevice_x2) / 3;
	mini_size_y2 = (pos_y_rd2 - pos_y_lu2 - crevice_y2) / 2;
}


Guild_PT::~Guild_PT()
{
	if (character_show_f != NULL)
	{
		delete character_show_f;
	}
}


void Guild_PT::Draw()
{
	int num_chara = 0;
	for (int i = 0; i < Defines::char_max; i++)
	{
		if (characters->in_team)
		{
			num_chara++;
		}
	}

	if (pt_type_deside_flag)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144);
		DrawBox(0, 0, 640, 20, Colors::blue, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		character_show_f->Draw();
		//既に選択されたキャラを黒く
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透過
		for (int i = 0; i < 5; i++)
		{
			if (temp_party_info[i] != -1)
			{
				DrawBox(character_show_f->pos_x_lu + 1,
						character_show_f->number_list[temp_party_info[i]] * 20 + character_show_f->pos_y_lu + 1, 
						character_show_f->pos_x_rd - 1, 
						(character_show_f->number_list[temp_party_info[i]] + 1) * 20 + character_show_f->pos_y_lu - 1, 
						Colors::black, TRUE); //今選ばれてるのを示す
			}
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

		if (choosing_place_flag)
		{
			DrawString(20, 0, "配置する場所を選択してください。", Colors::white);
		}
		else
		{
			DrawString(20, 0, "キャラクターを選択してください。", Colors::white);
		}
		DrawPartyType2(temp_party_type);
	}
	else
	{

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144);
		DrawBox(0, 0, 640, 20, Colors::blue, TRUE);
		for (int i = 0; i < num_chara && i < 5; i++)
		{
			DrawBox(pos_x_lu, pos_y_lu + (size_y + crevice_y) * i, pos_x_lu + size_x, pos_y_lu + (size_y + crevice_y)*i + size_y, Colors::blue, TRUE);
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

		for (int i = 0; i < num_chara && i < 5; i++)
		{
			DrawFormatString(pos_x_lu + size_x - GetDrawStringWidth("……５人パーティー  ", strlen("……５人パーティー  ")), pos_y_lu + (size_y + crevice_y) * i + 13,
				(i + 1 == (temp_party_type) / 10 ? Colors::yellow : Colors::white), "……%d人パーティー", i + 1);
		}
		DrawPartyType(20, pos_y_lu + 1, 11);
		DrawPartyType(20, pos_y_lu + size_y + crevice_y + 1, 21);
		DrawPartyType(20 + mini_size_x + mini_crevice_x, pos_y_lu + size_y + crevice_y + 1, 22);
		DrawPartyType(20, pos_y_lu + 2 * (size_y + crevice_y) + 1, 31);
		DrawPartyType(20 + mini_size_x + mini_crevice_x, pos_y_lu + 2 * (size_y + crevice_y) + 1, 32);
		DrawPartyType(20 + 2 * (mini_size_x + mini_crevice_x), pos_y_lu + 2 * (size_y + crevice_y) + 1, 33);
		DrawPartyType(20, pos_y_lu + 3 * (size_y + crevice_y) + 1, 41);
		DrawPartyType(20 + mini_size_x + mini_crevice_x, pos_y_lu + 3 * (size_y + crevice_y) + 1, 42);
		DrawPartyType(20 + 2 * (mini_size_x + mini_crevice_x), pos_y_lu + 3 * (size_y + crevice_y) + 1, 43);
		DrawPartyType(20, pos_y_lu + 4 * (size_y + crevice_y) + 1, 51);
		DrawPartyType(20 + mini_size_x + mini_crevice_x, pos_y_lu + 4 * (size_y + crevice_y) + 1, 52);

		/*//選択されてるのの上
		int pos_x2_lu = (party->party_type - (party->party_type / 10) * 10) * (mini_size_x + mini_crevice_x) + 20;
		int pos_y2_lu = 0.1 * party->party_type * (size_y + crevice_y) + pos_y_lu + 1;
		int pos_x2_rd = (party->party_type - (party->party_type / 10) * 10) * (mini_size_x + mini_crevice_x) + 20 + mini_size_x;
		int pos_y2_rd = 0.1 * party->party_type * (size_y + crevice_y) + pos_y_lu + 1 + 2;
		DrawBox(pos_x2_lu, pos_y2_lu, pos_x2_rd, pos_y2_rd, Colors::yellow, TRUE);
		//選択されてるのの下
		pos_y2_lu += mini_size_y;
		pos_y2_rd += mini_size_y;
		DrawBox(pos_x2_lu, pos_y2_lu, pos_x2_rd, pos_y2_rd, Colors::yellow, TRUE);*/


		DrawString(20, 0, "陣形を選択してください。", Colors::white);
	}
	party->Draw();

}


int Guild_PT::Reaction()
{
	//PTの記憶
	if (already_flag)
	{
		keep_party_type = temp_party_type = party->party_type;
		for (int i = 0; i < 5; i++)
		{
			keep_party_info[i] =  party->party_info[i];
			temp_party_info[i] = -1;
		}

		already_flag = 0;
	}

	//情報の更新
	party->party_type = temp_party_type;
	for (int i = 0; i < 5; i++)
	{
		party->party_info[i] = temp_party_info[i];
	}

	//編成終わり
	int nump = 0;
	for (int i = 0; i < 5; i++)
	{
		if (temp_party_info[i] != -1)nump++;
	}
	if (nump == temp_party_type / 10) //全部埋まった
	{
		guild_pt_flag = 0;
		pt_type_deside_flag = 0;
		delete character_show_f;
		character_show_f = NULL;
		nowchoose = 0;
	}
	else //基本の処理
	{
		if (pt_type_deside_flag)
		{
			if (!choosing_place_flag)
			{
				character_show_f->Reaction();

				//PTタイプを決める場面に戻る
				if (Key_Input::buff_time[KEY_INPUT_X] == 1)
				{
					pt_type_deside_flag = 0;
					for (int i = 0; i < 5; i++)
					{
						temp_party_info[i] = -1;
					}
					delete character_show_f;
					character_show_f = NULL;
				}
				//キャラを掴む
				else if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
				{
					for (int i = 0; i < temp_party_type / 10; i++)
					{
						if (temp_party_info[i] != -1)
						{
							//既に使われているキャラは選べない
							if (character_show_f->GetCharNow() == temp_party_info[i])
							{
								goto sugusoko;
							}
						}

					}
					choosing_place_flag++;
				sugusoko:;
				}
			}
			else
			{
				if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 || Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1)
				{
					switch (temp_party_type)
					{
					case 22:
						nowchoose = 1 - nowchoose;
						break;
					case 32:
						nowchoose = nowchoose == 2 ? 0 : 2;
						break;
					case 33:
						nowchoose = nowchoose ? 0 : 1;
						break;
					case 41:
						nowchoose = nowchoose == 3 ? 1 : 3;
						break;
					case 42:
						nowchoose = (nowchoose % 2 ? 4 : 2) - nowchoose;
						break;
					case 43:
						nowchoose = nowchoose ? 0 : 2;
						break;
					case 51:
						nowchoose = nowchoose > 2 ? nowchoose - 3 : (nowchoose ? 4 : 3);
						break;
					case 52:
						nowchoose = nowchoose < 2 ? nowchoose + 2 : (nowchoose == 2 ? 0 : 1);
						break;
					default:
						break;
					}
				}
				else if (Key_Input::buff_time[KEY_INPUT_RIGHT] % 10 == 1)
				{
					nowchoose = nowchoose == (temp_party_type / 10) - 1 ? 0 : ++nowchoose;

				}
				else if (Key_Input::buff_time[KEY_INPUT_LEFT] % 10 == 1)
				{
					nowchoose = (nowchoose ? --nowchoose : temp_party_type / 10 - 1);
				}

				if (Key_Input::buff_time[KEY_INPUT_X] == 1)
				{
					//キャラを選ぶ場面に戻る
					choosing_place_flag = 0;
					nowchoose = 0;
				}
				//現在選択しているキャラを置く
				else if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
				{
					if (temp_party_info[nowchoose]!=-1) //既に置かれていたら置けない
					{
					}
					else //置かれてないなら置ける
					{
						temp_party_info[nowchoose] = character_show_f->GetCharNow();
						choosing_place_flag = 0;
						for (int i = 0; i < temp_party_type / 10; i++)
						{
							if (temp_party_info[i] == -1)
							{
								nowchoose = i;
								break;
							}
						}
					}
				}
			}
		}
		else
		{

			if (Key_Input::buff_time[KEY_INPUT_UP] % space_on_time == 1)
			{
				if (temp_party_type % 10 == 1)
				{
					temp_party_type = (temp_party_type == 11 ? 51 : temp_party_type - 10);
				}
				else if (temp_party_type % 10 == 2)
				{
					temp_party_type = (temp_party_type == 22 ? 11 : temp_party_type - 10);
				}
				else if (temp_party_type % 10 == 3)
				{
					temp_party_type = (temp_party_type == 33 ? 22 : temp_party_type - 10);
				}
			}
			else if (Key_Input::buff_time[KEY_INPUT_DOWN] % space_on_time == 1)
			{
				if (temp_party_type % 10 == 1)
				{
					temp_party_type = (temp_party_type == 51 ? 11 : temp_party_type + 10);
				}
				else if (temp_party_type % 10 == 2)
				{
					temp_party_type = (temp_party_type == 52 ? 11 : temp_party_type + 10);
				}
				else if (temp_party_type % 10 == 3)
				{
					temp_party_type = (temp_party_type == 43 ? 52 : temp_party_type + 10);
				}
			}

			if (Key_Input::buff_time[KEY_INPUT_RIGHT] % space_on_time == 1)
			{
				if (temp_party_type == 21 || temp_party_type == 31 || temp_party_type == 32 || temp_party_type == 41 || temp_party_type == 42 || temp_party_type == 51)
				{
					temp_party_type++;
				}
				else
				{
					temp_party_type = temp_party_type - temp_party_type % 10 + 1;
				}
			}
			else if (Key_Input::buff_time[KEY_INPUT_LEFT] % space_on_time == 1)
			{
				if (temp_party_type == 22 || temp_party_type == 32 || temp_party_type == 33 || temp_party_type == 42 || temp_party_type == 43 || temp_party_type == 52)
				{
					temp_party_type--;
				}
				else if (temp_party_type == 21)
				{
					temp_party_type = 22;
				}
				else if (temp_party_type == 31)
				{
					temp_party_type = 33;
				}
				else if (temp_party_type == 41)
				{
					temp_party_type = 43;
				}
				else if (temp_party_type == 51)
				{
					temp_party_type = 52;
				}
			}
			if (Key_Input::buff_time[KEY_INPUT_X] == 1)
			{
				guild_pt_flag = 0;
				//キャンセルの場合は元に戻す

				party->party_type = keep_party_type;
				for (int i = 0; i < 5; i++)
				{
					party->party_info[i] = keep_party_info[i];
				}
			}
			else if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
			{
				pt_type_deside_flag++;
				character_show_f = new Character_Show_F;
			}
		}

	}
	return 0;
}


void Guild_PT::DrawHitogata(int pos_x, int pos_y, int color)
{
	DrawExtendString(pos_x, pos_y, 0.5, 0.5, "●", color);
	DrawExtendString(pos_x, pos_y + 5, 0.45, 0.45, "▲", color);
}


void Guild_PT::DrawPartyType(int pos_x, int pos_y, int party_type)
{
	int color_temp = (temp_party_type == party_type ? Colors::yellow : Colors::aqua);

	DrawBox(pos_x, pos_y, pos_x + mini_size_x, pos_y + 2, color_temp, TRUE); //上
	DrawBox(pos_x + mini_size_x - 2, pos_y, pos_x + mini_size_x, pos_y + mini_size_y, color_temp, TRUE); //右
	DrawBox(pos_x, pos_y + mini_size_y - 2, pos_x + mini_size_x, pos_y + mini_size_y, color_temp, TRUE); //下
	DrawBox(pos_x, pos_y, pos_x + 2, pos_y + mini_size_y, color_temp, TRUE); //左
	for (int i = pos_x; i < pos_x + mini_size_x - 2; i++)
	{
		if (i % 5 < 3)
		{
			DrawLine(i, pos_y + 0.5 * mini_size_y - 1, i + 1, pos_y + 0.5 * mini_size_y - 1, Colors::aqua);
		}
	}
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144);
	//DrawExtendString(pos_x + 6, pos_y + 5, 0.7, 0.7, "FORGARD", Colors::dark_aqua);
	//DrawExtendString(pos_x + 14, pos_y + 25, 0.8, 0.8, "BACK", Colors::dark_aqua);
	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	switch (party_type)
	{
	case 11:
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5, Colors::red);
		break;
	case 21:
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * GetDrawStringWidth(("●"), strlen("●")) - 5, pos_y + 5, Colors::red);
		DrawHitogata(pos_x + 0.5 * mini_size_x + 5, pos_y + 5, Colors::red);
		break;
	case 22:
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5, Colors::red);
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5 + 22, Colors::aqua);
		break;
	case 31:
		//左
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1 - 5 - 0.5 * GetDrawStringWidth(("●"), strlen("●")), pos_y + 5, Colors::red);
		//真ん中
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5, Colors::red);
		//右
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 5 + 1, pos_y + 5, Colors::red);
		break;
	case 32:
		//左
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * GetDrawStringWidth(("●"), strlen("●")) - 5, pos_y + 5, Colors::red);
		//右
		DrawHitogata(pos_x + 0.5 * mini_size_x + 5, pos_y + 5, Colors::red);
		//後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5 + 22, Colors::aqua);
		break;
	case 33:
		//真ん中
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5, Colors::red);
		//左後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * GetDrawStringWidth(("●"), strlen("●")) - 5, pos_y + 5 + 22, Colors::aqua);
		//右後
		DrawHitogata(pos_x + 0.5 * mini_size_x + 5, pos_y + 5 + 22, Colors::aqua);
		break;
	case 41:
		//左
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1 - 5 - 0.5 * GetDrawStringWidth(("●"), strlen("●")), pos_y + 5, Colors::red);
		//真ん中
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5, Colors::red);
		//右
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 5 + 1, pos_y + 5, Colors::red);
		//後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5 + 22, Colors::aqua);
		break;
	case 42:
		//左
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * GetDrawStringWidth(("●"), strlen("●")) - 5, pos_y + 5, Colors::red);
		//右
		DrawHitogata(pos_x + 0.5 * mini_size_x + 5, pos_y + 5, Colors::red);
		//左後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * GetDrawStringWidth(("●"), strlen("●")) - 5, pos_y + 5 + 22, Colors::aqua);
		//右後
		DrawHitogata(pos_x + 0.5 * mini_size_x + 5, pos_y + 5 + 22, Colors::aqua);
		break;
	case 43:
		//真ん中
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5 ,Colors::red);
		//左後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1 - 5 - 0.5 * GetDrawStringWidth(("●"), strlen("●")), pos_y + 5 + 22, Colors::aqua);
		//後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5 + 22, Colors::aqua);
		//右後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 5 + 1, pos_y + 5 + 22, Colors::aqua);
		break;
	case 51:
		//左
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1 - 5 - 0.5 * GetDrawStringWidth(("●"), strlen("●")), pos_y + 5, Colors::red);
		//真ん中
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5, Colors::red);
		//右
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 5 + 1, pos_y + 5, Colors::red);
		//左後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * GetDrawStringWidth(("●"), strlen("●")) - 5, pos_y + 5 + 22, Colors::aqua);
		//右後
		DrawHitogata(pos_x + 0.5 * mini_size_x + 5, pos_y + 5 + 22, Colors::aqua);
		break;
	case 52:
		//左
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * GetDrawStringWidth(("●"), strlen("●")) - 5, pos_y + 5, Colors::red);
		//右
		DrawHitogata(pos_x + 0.5 * mini_size_x + 5, pos_y + 5, Colors::red);
		//左後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1 - 5 - 0.5 * GetDrawStringWidth(("●"), strlen("●")), pos_y + 5 + 22, Colors::aqua);
		//後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 1, pos_y + 5 + 22, Colors::aqua);
		//右後
		DrawHitogata(pos_x + 0.5 * mini_size_x - 0.5 * 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 0.5 * GetDrawStringWidth(("●"), strlen("●")) + 5 + 1, pos_y + 5 + 22, Colors::aqua);
		break;
	default:
		break;
	}
}


void Guild_PT::DrawPartyType2(int party_type)
{
	countdpb = 0;
	switch (party_type)
	{
	case 11:
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2, Colors::red);
		break;
	case 21:
		//左
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 - mini_size_x, pos_y_lu2, Colors::red);
		//右
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 + crevice_x2 / 2, pos_y_lu2, Colors::red);
		break;
	case 22:
		//左
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2, Colors::red);
		//後
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue); 
		break;
	case 31:
		//左
		DrawPartyBox(pos_x_lu2, pos_y_lu2, Colors::red);
		//真ん中
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2, Colors::red);
		//右
		DrawPartyBox(pos_x_lu2 + 2 * (mini_size_x + crevice_x2), pos_y_lu2, Colors::red);
		break;
	case 32:
		//左
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 - mini_size_x, pos_y_lu2, Colors::red);
		//右
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 + crevice_x2 / 2, pos_y_lu2, Colors::red);
		//後
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		break;
	case 33:
		//真ん中
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2, Colors::red);
		//左後
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 - mini_size_x, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		//右後
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 + crevice_x2 / 2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		break;
	case 41:
		//左
		DrawPartyBox(pos_x_lu2, pos_y_lu2, Colors::red);
		//真ん中
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2, Colors::red);
		//右
		DrawPartyBox(pos_x_lu2 + 2 * (mini_size_x + crevice_x2), pos_y_lu2, Colors::red);
		//後
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		break;
	case 42:
		//左
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 - mini_size_x, pos_y_lu2, Colors::red);
		//右
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 + crevice_x2 / 2, pos_y_lu2, Colors::red);
		//左後
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 - mini_size_x, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		//右後
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 + crevice_x2 / 2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		break;
	case 43:
		//真ん中
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2, Colors::red);
		//左後
		DrawPartyBox(pos_x_lu2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		//後
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		//右後
		DrawPartyBox(pos_x_lu2 + 2 * (mini_size_x + crevice_x2), pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		break;
	case 51:
		//左
		DrawPartyBox(pos_x_lu2, pos_y_lu2, Colors::red);
		//真ん中
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2, Colors::red);
		//右
		DrawPartyBox(pos_x_lu2 + 2 * (mini_size_x + crevice_x2), pos_y_lu2, Colors::red);
		//左後
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 - mini_size_x, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		//右後
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 + crevice_x2 / 2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		break;
	case 52:
		//左
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 - mini_size_x, pos_y_lu2, Colors::red);
		//右
		DrawPartyBox(pos_x_lu2 + (pos_x_rd2 - pos_x_lu2 + crevice_x2) / 2 + crevice_x2 / 2, pos_y_lu2, Colors::red);
		//左後
		DrawPartyBox(pos_x_lu2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		//後
		DrawPartyBox(pos_x_lu2 + mini_size_x + crevice_x2, pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		//右後
		DrawPartyBox(pos_x_lu2 + 2 * (mini_size_x + crevice_x2), pos_y_lu2 + (mini_size_y2 + crevice_y2), Colors::blue);
		break;
	default:
		break;
	}
}


void Guild_PT::DrawPartyBox(int pos_x,int pos_y,int color)
{
	int frontcolor = Colors::red; //前列であることの条件判断の為
	int backcolor = Colors::blue;

	//現在選ばれてるのを表す
	if (countdpb==nowchoose && choosing_place_flag)
	{
		DrawBox(pos_x - 2, pos_y - 2, pos_x + mini_size_x2 + 2, pos_y + mini_size_y2 + 2, Colors::yellow, TRUE);
	}

	DrawBox(pos_x, pos_y, pos_x + mini_size_x2, pos_y + mini_size_y2, color, TRUE);
	if (frontcolor == color)
	{
		DrawString(pos_x + mini_size_x2 / 2 - GetDrawStringWidth("前衛", strlen("前衛")) / 2, pos_y + 2, "前衛", Colors::white);
	}
	else if (backcolor == color)
	{
		DrawString(pos_x + mini_size_x2 / 2 - GetDrawStringWidth("後衛", strlen("後衛")) / 2, pos_y + 2, "後衛", Colors::white);
	}

	//すでに埋まってるのを暗く
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144);
	if (temp_party_info[countdpb] != -1)
	{
		DrawBox(pos_x, pos_y, pos_x + mini_size_x2, pos_y + mini_size_y2, Colors::black, TRUE);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	countdpb++;
}