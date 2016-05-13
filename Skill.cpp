#include "Skill.h"
#include"Functions_3DD.h"

Skill* Skill::instance;

Skill::Skill()
{
	LoadSkillList_PT();
}


int Skill::LoadSkillList_PT()
{
	FILE* fp = nullptr;
	FILE* fp2 = nullptr;
	fp = fopen("./scn/skill/skillList_PT.txt", "r");
	fp2 = fopen("./scn/skill/skillvalue.txt", "r");
	for (int i = 0; i < SKILL_MAX_PT; i++)
	{
		char temp[1024]; //この辺雑。TODO:可変長の引数を持つ、文字列を','で分解する関数を作る。文字列と数値の判断はどうするのか?
		char keep[1024];
		char dammy[1024];
		fscanf(fp, "%[^\n]s", temp); //読み込んで
		fscanf(fp, "%*c"); //改行を捨てる
		int c = 0, j = 0;
		//スキル名を取得
		while (temp[c] != ',') //分解する
		{
			keep[c] = temp[c];
			 c++;
		}
		keep[c] = '\0';
		strcpy(m_skill_PT[i].m_skillList_PT, keep);
		c++; //,の隣にずらす
		//スキルタイプを取得
		while (temp[c] != ',')
		{
			keep[j] = temp[c];
			c++;
			j++;
		}
		keep[j] = '\0';
		m_skill_PT[i].m_skillType = atoi(keep);
		c++; //,の隣にずらす
		j = 0;
		//スキルの説明の取得
		while (temp[c] != ',') //分解する
		{
			keep[j] = temp[c];
			c++;
			j++;
		}
		keep[j] = '\0';
		strcpy(m_skill_PT[i].m_skillText, keep);
		c++; //,の隣にずらす
		j = 0;
		//スキル種別の取得
		while (temp[c] != ',')
		{
			keep[j] = temp[c];
			c++;
			j++;
		}
		keep[j] = '\0';
		m_skill_PT[i].type_kind = atoi(keep);
		c++; //,の隣にずらす
		j = 0;
		//スキルの最大レベルの取得
		while (temp[c] != ',')
		{
			keep[j] = temp[c];
			c++;
			j++;
		}
		keep[j] = '\0';
		m_skill_PT[i].maxlevel = atoi(keep);
		c++; //,の隣にずらす
		j = 0;
		//エフェクト番号の取得
		while (temp[c] != '\0')
		{
			keep[j] = temp[c];
			c++;
			j++;
		}
		keep[j] = '\0';
		m_skill_PT[i].effect_number = atoi(keep);


		//こっちのが楽といえば楽…のはずだけどなんか上手く行かないので上のやり方でいく
		/*fscanf(fp, "%[^,]s,%[^,]d,%[^,]s,%[^,]d,%[^,]d", 
			m_skill_PT[i].m_skillList_PT,
			&(m_skill_PT[i].m_skillType),
			m_skill_PT[i].m_skillText,
			&(m_skill_PT[i].type_kind),
			&(m_skill_PT[i].maxlevel));*/
		/*fscanf(fp, "%[^,]s", m_skill_PT[i].m_skillList_PT);
		fscanf(fp, "%c");
		fflush(stdin);
		fscanf(fp, "%[^,]d", &(m_skill_PT[i].m_skillType));
		fscanf(fp, "%c");
		fflush(stdin);
		fscanf(fp, "%[^,]s", m_skill_PT[i].m_skillText);
		fscanf(fp, "%c");
		fflush(stdin);
		fscanf(fp, "%[^,]d", &(m_skill_PT[i].type_kind));
		fscanf(fp, "%c");
		fflush(stdin);
		fscanf(fp, "%[^,\n]d", &(m_skill_PT[i].maxlevel));
		fscanf(fp, "%[\n]c");
		fflush(stdin);*/


		//次はskillvalue.txtの読み込み。この辺は数値のみなので関数で纏められる
		fscanf(fp2, "%s", dammy); //一行読み飛ばす
		if (m_skill_PT[i].m_skillType) //パッシブじゃなければ
		{
			//TPを取得
			{ //初期化するよりスコープのほうが楽…
				int temp_int[Defines::SKILL_MAX_LEVEL];
				LoadInts(fp2, temp_int, Defines::SKILL_MAX_LEVEL); //取得して
				for (int count = 0; count < Defines::SKILL_MAX_LEVEL; count++)
				{
					m_skill_PT[i].need_TP[count] = temp_int[count]; //代入
				}
			}
			//スキル威力を取得
			{
				int temp_int[Defines::SKILL_MAX_LEVEL];
				LoadInts(fp2, temp_int, Defines::SKILL_MAX_LEVEL); //取得して
				for (int count = 0; count < Defines::SKILL_MAX_LEVEL; count++)
				{
					m_skill_PT[i].value[count] = temp_int[count]; //代入
				}
			}

			//行動後速度修正を取得
			fscanf(fp2, "%s", dammy); //
		}

		
	}
	fclose(fp);
	fclose(fp2);

	return 0;
}


bool Skill::GetSkillCanUse_PT(int number, int mode)
{
	bool res = FALSE;
	switch (mode)
	{
	case Defines::GUILD:
		res = FALSE; //使えない
		break;
	case Defines::FIELD:
	{
		if (m_skill_PT[number].m_skillType != 0 && m_skill_PT[number].m_skillType != 1) //パッシブか攻撃系でなければ
		{
			res = TRUE; //使える
		}
		else //パッシブか攻撃系なら
		{
			res = FALSE; //使えない
		}
	}
		break;
	case Defines::BATTLE:
	{
		if (m_skill_PT[number].m_skillType) //パッシブでなければ
		{
			res = TRUE; //使える
		}
		else //パッシブなら
		{
			res = FALSE; //使えない
		}
	}
		break;
	default:
		break;
	}
	
	return res;
}
