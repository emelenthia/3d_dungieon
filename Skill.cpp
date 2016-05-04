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
		res = FALSE; //�g���Ȃ�
		break;
	case Defines::FIELD:
	{
		if (m_skill_PT[number].m_skillType != 0 && m_skill_PT[number].m_skillType != 1) //�p�b�V�u���U���n�łȂ����
		{
			res = TRUE; //�g����
		}
		else //�p�b�V�u���U���n�Ȃ�
		{
			res = FALSE; //�g���Ȃ�
		}
	}
		break;
	case Defines::BATTLE:
	{
		if (m_skill_PT[number].m_skillType) //�p�b�V�u�łȂ����
		{
			res = TRUE; //�g����
		}
		else //�p�b�V�u�Ȃ�
		{
			res = FALSE; //�g���Ȃ�
		}
	}
		break;
	default:
		break;
	}
	
	return res;
}
