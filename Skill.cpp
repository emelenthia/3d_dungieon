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
		char temp[1024]; //���̕ӎG
		char keep[1024];
		fscanf(fp, "%[^\n]s", temp); //�ǂݍ����
		fscanf(fp, "%*c"); //���s���̂Ă�
		int c = 0, j = 0;
		//�X�L�������擾
		while (temp[c] != ',') //��������
		{
			keep[c] = temp[c];
			 c++;
		}
		keep[c] = '\0';
		strcpy(m_skill_PT[i].m_skillList_PT, keep);
		//�X�L���^�C�v���擾
		m_skill_PT[i].m_skillType = temp[++c] - '0';
		c += 2;
		//�X�L���̐����̏K��
		while (temp[c] != '\0') //��������
		{
			keep[j] = temp[c];
			c++;
			j++;
		}
		keep[j] = '\0';
		strcpy(m_skill_PT[i].m_skillText, keep);

		//�������̂��y�Ƃ����Ίy
		//fscanf(fp, "%s%d%s", m_skill_PT[i].m_skillList_PT, &(m_skill_PT[i].m_skillType), m_skill_PT[i].m_skillText);
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
