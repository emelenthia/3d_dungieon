#pragma once
#include"DxLib.h"
#include"Defines.h"

class Skill //�X�L���֘A��Z�߂�N���X
{
public:
	static Skill* instance;
	//// �B��̃A�N�Z�X�o�H
	static Skill* GetInstance()
	{
		if (instance == NULL)instance = new Skill();
		return instance;
	}
	char m_skillList_PT[SKILL_MAX_PT][32]; //�������g�p����X�L���̖��O�̃��X�g
	int LoadSkillList_PT(); //�������g�p����X�L���̖��O�̃��X�g�����[�h����

private:
	// ������R�s�[���֎~����
	Skill();
	Skill(const Skill& rhs);
	Skill& operator=(const Skill& rhs);
	~Skill() {};
};

