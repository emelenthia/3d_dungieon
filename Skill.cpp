#include "Skill.h"

Skill* Skill::instance;

Skill::Skill()
{
	LoadSkillList_PT();
}


int Skill::LoadSkillList_PT()
{
	FILE* fp = nullptr;
	fp = fopen("./scn/skill/skillList_PT.txt", "r");
	for (int i = 0; i < SKILL_MAX_PT; i++)
	{
		char temp[1024]; //この辺雑。TODO:可変長の引数を持つ、文字列を','で分解する関数を作る。文字列と数値の判断はどうするのか?
		char keep[1024];
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
		while (temp[c] != '\0')
		{
			keep[j] = temp[c];
			c++;
			j++;
		}
		keep[j] = '\0';
		m_skill_PT[i].maxlevel = atoi(keep);


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

	}
	fclose(fp);

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
