#pragma once
#include<stdio.h>
#include"Status.h"
#include"Defines.h"
#include"Colors.h"
#include"Skill.h"
#include"Ailment.h"

class Character_Data_Save //�Z�[�u�����e�L�����̉σf�[�^
{
public:
	Character_Data_Save();
	~Character_Data_Save();
	int exp[CHARA_MAX]; //
	int Lv[CHARA_MAX];
	char name[CHARA_MAX][21];
	int job[CHARA_MAX];
	int in_team[CHARA_MAX]; //�����t���O�B1�Ȃ����
	FILE *fp[CHARA_MAX];
	void Load_Char(char *file_pointer,int n);
	//int nowhp[15]; //���݂̎c��HP
	//int nowtp[15]; //���݂̎c��TP
	status_c status_c[CHARA_MAX - 1]; //���݂̉σX�e�[�^�X
	
	char file_name[CHARA_MAX][50]; //�t�@�C�������o���Ă���
	int in_party[CHARA_MAX]; //�Ґ��ɓ����Ă�t���O�B1�Ȃ�����Ă܂�
	int lastchoosef[CHARA_MAX]; //�퓬�ɑ΂��čŌ�ɍs�����s��
	int lastchoosef_skill[CHARA_MAX]; //�Ō�Ɏg�p�����X�L��
	//�X�L���֌W
	char m_canSkillLevel[CHARA_MAX][SKILL_MAX_PT]; //�e�L�����̃X�L���擾���x���B0�Ȃ�擾���Ă��Ȃ�
	void DrawSkill(int chara, int mode, int pos_x, int pos_y, int choose); //�w�肳�ꂽ�L�����̃X�L���ꗗ��\�����܂��Bchara�̓L�����ԍ����w��Bmode�͎g�p��ʂɂ���đI���A���define���Q��pos_x��pos_y�͍���̍��W�Bchoose�͍��I�΂�Ă���X�L��
	char GetCanSkillNum(int chara,int mode = -1); //���ݎg�p�ł���X�L���̑������擾���ĕԂ��Bmode���w��\�B�w�肵�Ȃ��ꍇ�͑S�ẴX�L���Ώ�
	int GetSkillNumber(int chara, int number, int mode = -1); //�w�肳�ꂽchara�̎w�肳�ꂽmode�ŏォ��number�ڂ̃X�L���ԍ����擾
	//��Ԉُ�֌W
	int ailment_turn[CHARA_MAX][Defines::AILMENT_MAX]; //�e��Ԉُ�̎c��^�[���B�����I�Ɏc��^�[����1�ȏ�̏�Ԉُ�ɂ������Ă��邱�ƂɂȂ�
	int ailment_walks[CHARA_MAX][Defines::AILMENT_MAX]; //�e��Ԉُ�̎c������B�����Ď���Ȃ����̂�-1�Ŏ���
	
private:
	Skill* m_skill;
	Ailment* m_ailment;
	char m_canSkillNum[CHARA_MAX]; //�e�L�����̎擾�X�L����
};