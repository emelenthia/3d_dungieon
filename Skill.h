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
	enum skillType { PASSIVE = 0, ATTACK, HEAL, HELP };
	typedef struct //�X�L���^�̍\����
	{
		char m_skillList_PT[32]; //�������g�p����X�L���̖��O�̃��X�g
		char m_skillType; //�e�X�L���̎g�p�����B0�Ȃ�p�b�V�u�A1�Ȃ�U���n�A2�Ȃ�񕜌n�A3�Ȃ�⏕�n�Benum skillType�Q��
		char m_skillText[128]; //�X�L���̐������BTODO:�ϐ�������m_skill�𔲂��Ă��ǂ�����
	}t_skills;
	t_skills m_skill_PT[SKILL_MAX_PT];
	int LoadSkillList_PT(); //�������g�p����X�L���̖��O�̃��X�g�����[�h����
	bool GetSkillCanUse_PT(int number, int mode); //�w�肵���X�L�����w�肵��mode�Ŏg�p�ł��邩�ǂ�����Ԃ��B�g�p�ł���Ȃ�TRUE�Bmode��defines�Q��
	

private:
	// ������R�s�[���֎~����
	Skill();
	Skill(const Skill& rhs);
	Skill& operator=(const Skill& rhs);
	~Skill() {};
};

