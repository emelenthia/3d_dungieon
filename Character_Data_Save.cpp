#include "Character_Data_Save.h"
#include"DxLib.h"
#include"Defines.h"

Character_Data_Save::Character_Data_Save()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		fp[i] = NULL;
		strcpy(file_name[i], "null");
	}
	m_skill = Skill::GetInstance();
	m_ailment = Ailment::GetInstance();
}


Character_Data_Save::~Character_Data_Save()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		if (fp[i] != NULL)
		{
			fclose(fp[i]);
		}
	}
}


void Character_Data_Save::Load_Char(char *file_pointer,int n)
{
	if (!(strcmp(file_name[n], "null")))
	{
		strcpy(file_name[n], file_pointer); //元のファイル名を覚えておく。ゲーム自体には意味がない
	}
	fp[n] = fopen(file_pointer, "r"); //指定されたファイルを開く

	if (fp[n] == NULL) //エラー処理
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name[n]);
		WaitKey();
		DxLib_End();				// ＤＸライブラリ使用の終了処理
		exit(1);
	}

	//色々読み込む
	fscanf(fp[n], "%d", &in_team[n]);
	if (in_team)
	{
		fscanf(fp[n], "%d", &exp[n]);
		fscanf(fp[n], "%d", &job[n]);
		fscanf(fp[n], "%d", &Lv[n]);
		fscanf_s(fp[n], "%s", name[n], 20);
		fscanf(fp[n], "%d", &in_party[n]);
		fscanf(fp[n], "%d", &status_c[n].hp);
		fscanf(fp[n], "%d", &status_c[n].tp);
		fscanf(fp[n], "%d", &lastchoosef[n]);
		fscanf(fp[n], "%d", &lastchoosef_skill[n]);
		fgetc(fp[n]); //改行文字を捨てる
		for (int i = 0; i < SKILL_MAX_PT; i++)
		{
			m_canSkillLevel[n][i] = fgetc(fp[n]) - '0'; //文字を数字に変換する
		}
		//状態異常の残りターン数を取得
		int ail_temp[Defines::AILMENT_MAX];
		LoadInts(fp[n], ail_temp);
		for (int i = 0; i < Defines::AILMENT_MAX; i++)
		{
			ailment_turn[n][i] = ail_temp[i];
		}
		//状態異常の残り歩数を取得
		LoadInts(fp[n], ail_temp);
		for (int i = 0; i < Defines::AILMENT_MAX; i++)
		{
			ailment_walks[n][i] = ail_temp[i];
		}
		//状態異常のレベルを取得
		LoadInts(fp[n], ail_temp);
		for (int i = 0; i < Defines::AILMENT_MAX; i++)
		{
			ailment_level[n][i] = ail_temp[i];
		}
	}
}

void Character_Data_Save::DrawSkill(int chara, int mode, int pos_x, int pos_y,int choose)
{
	int count = 0;
	const int SIZE_X = 280; //枠の背景の大きさを基準にする
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透化

	//DrawBox(pos_x, pos_y - 5, pos_x + 303, pos_y + GetCanSkillNum(chara, mode) * 20 , Colors::dark_yellow, TRUE); //周りの枠を表示
	DrawBox(pos_x , pos_y, pos_x + SIZE_X, pos_y + GetCanSkillNum(chara, mode) * 20, Colors::gray, TRUE); //枠の背景を表示

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

	//上に文字表示
	DrawStringToHandle(pos_x + 20, pos_y - 14, "SKILL", Colors::yellow, Colors::fh_half);
	DrawStringToHandle(pos_x + SIZE_X - 20, pos_y - 14, "TP", Colors::yellow, Colors::fh_half);
	for (int i = 0; i < SKILL_MAX_PT; i++)
	{
		if (m_canSkillLevel[chara][i] >= 1 && m_skill->m_skill_PT[i].m_skillType >= 1) //そのスキルのレベルが1以上で、そのスキルがパッシブじゃない場合
		{
			if (count == choose) //左側にiを使わないのは、右側の数字の最大は使用できるスキル数なため
			{
				DrawBox(pos_x + 2, pos_y + count * 20, pos_x + SIZE_X, pos_y + count * 20 + 20, Colors::yellow, TRUE); //約15文字分の幅
				DrawFormatString(5, 1, Colors::white, "%s", m_skill->m_skill_PT[i].m_skillText); //スキルの説明の表示
				DrawFormatString(pos_x + 20, pos_y + count * 20 + 2, Colors::black, "%s", m_skill->m_skill_PT[i].m_skillList_PT);
				DrawFormatString(pos_x + SIZE_X - 20, pos_y + count * 20 + 2, Colors::black, "%d", m_skill->m_skill_PT[i].need_TP[m_canSkillLevel[chara][i]]); //必要TPの表示
			}
			else //現在選択されているスキル以外は白色で表示する
			{
				DrawFormatString(pos_x + 20, pos_y + count * 20, Colors::white, "%s", m_skill->m_skill_PT[i].m_skillList_PT);
				DrawFormatString(pos_x + SIZE_X - 20, pos_y + count * 20, Colors::white, "%d", m_skill->m_skill_PT[i].need_TP[m_canSkillLevel[chara][i]]); //必要TPの表示
			}
			count++;
		}
	}

	DrawBox(pos_x + SIZE_X, pos_y, pos_x + SIZE_X + 2, pos_y + count * 20 + 2, Colors::dark_yellow, TRUE); //台詞欄の周り右
	DrawBox(pos_x, pos_y, pos_x + 2, pos_y + count * 20 + 2, Colors::dark_yellow, TRUE); //台詞欄の周り左
	DrawBox(pos_x, pos_y - 2, pos_x + SIZE_X + 2, pos_y, Colors::dark_yellow, TRUE); //台詞欄の周り上
	DrawBox(pos_x, pos_y + count * 20, pos_x + SIZE_X + 2, pos_y + count * 20 + 2, Colors::dark_yellow, TRUE); //台詞欄の周り下

	if (!count) //表示すべきスキルがない場合…まあ無いだろうけど
	{
	}
	else
	{

	}
}

char Character_Data_Save::GetCanSkillNum(int chara, int mode)
{
	int count = 0;
	for (int i = 0; i < SKILL_MAX_PT; i++)
	{
		if (m_canSkillLevel[chara][i] >= 1) //そのスキルのレベルが1以上
		{
			if (mode != -1)
			{
				if (m_skill->GetSkillCanUse_PT(i, mode)) //指定したmodeで使えるならば
				{
					count++;
				}
			}
			else //特にmodeを指定しない場合
			{
				count++;
			}
		}
	}
	return count;
}

int Character_Data_Save::GetSkillNumber(int chara, int number, int mode)
{
	int count = -1; //numberは0の可能性もあるので、-1からスタートする
	for (int i = 0; i < SKILL_MAX_PT; i++)
	{
		if (m_canSkillLevel[chara][i] >= 1) //i番目のスキルを覚えていて
		{
			if (m_skill->GetSkillCanUse_PT(i, mode)) //それが指定されたmodeで使用可能ならば
			{
				count++; //それは上からcount個目にあるスキル
				if (count == number) //上からnumber個目に来たら
				{
					return i; //そのスキルの番号を返す
				}
			}
		}
	}
	return -1; //なんにも見当たらなかった場合は一応エラーとするs
}


int Character_Data_Save::GetAilNumber(int chara, int number)
{
	int count = 0, i = 0;

	if (number <= 0)
	{
		return -1; //保険
	}
	for (; i < Defines::AILMENT_MAX; i++)
	{
		if (ailment_turn[chara][i])
		{
			count++;
			if (count == number)
			{
				return i;
			}
		}
	}
	return -1; //見つからなかったらここに来る
}


int Character_Data_Save::GetAilNum(int chara)
{
	int count = 0;
	for (int i = 0; i < Defines::AILMENT_MAX; i++)
	{
		if (ailment_turn[chara][i]) //よく考えたら-1もある…?
		{
			count++;
		}
	}
	return count;
}
