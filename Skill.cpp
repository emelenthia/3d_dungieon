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
		fscanf(fp, "%s%d", m_skill_PT[i].m_skillList_PT, &(m_skill_PT[i].m_skillType));
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
