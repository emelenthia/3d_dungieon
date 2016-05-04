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
	}
}

void Character_Data_Save::DrawSkill(int chara, int mode, int pos_x, int pos_y,int choose)
{
	int count = 0;
	for (int i = 0; i < SKILL_MAX_PT; i++)
	{
		if (m_canSkillLevel[chara][i] >= 1 && m_skill->m_skill_PT[i].m_skillType >= 1) //そのスキルのレベルが1以上で、そのスキルがパッシブじゃない場合
		{
			if (count == choose) //左側にiを使わないのは、右側の数字の最大は使用できるスキル数なため
			{
				DrawBox(pos_x, pos_y + count * 20 - 3, pos_x + 200, pos_y + count * 20 + 20 - 3, Colors::yellow, TRUE);
				DrawFormatString(pos_x + 20, pos_y + count * 20, Colors::black, "%s", m_skill->m_skill_PT[i].m_skillList_PT);
			}
			else
			{
				DrawFormatString(pos_x + 20, pos_y + count * 20, Colors::white, "%s", m_skill->m_skill_PT[i].m_skillList_PT);
			}
			count++;
		}
	}
	if (!count) //表示すべきスキルがない場合
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
