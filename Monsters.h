#pragma once
//#include"studio.h"
#include"MonsterList.h"
#include"Status.h"
#include"Ailment.h"
#include"Defines.h"
#include"Party.h"
#include"Randomer.h"

//�����X�^�[�I�u�W�F�N�g
//�t�@�C���������ǂݍ��݁A�I�u�W�F�N�g1�ɂ������X�^�[1�̕��̋���������

class Monsters
{
public:
	Monsters(){};
	Monsters(int n);
	~Monsters();
	void Draw(int pos_x, int pos_y, int size_x, int size_y, bool brightflag); //�����Ƃ�����̍��W

	typedef enum strain //�푰�ꗗ
	{
		MAJIC_LIFE = 1//���@����
	};
	strain Strain;
	status Status_;

	status_c Status_c;

	int graph_b; //�傫���摜�̃n���h��
	int graph_m; //�������摜�̃n���h��

	void MonsterSet(int n); //�t�@�C���������ǂݍ����n�Ԗڂ̃����X�^�[���ɏ������B
	FILE* individuals_fp; //�X�̏���ǂݍ��ނ��߂̎g���񂷃|�C���^
	char monster_file_name[101]; //�����X�^�[�̖��O(�t�@�C���ǂݍ��ݗp)
	char monster_file_name_temp[101]; //�����X�^�[�̖��O(�t�@�C���ǂݍ��ݗp)
	MonsterList* monsterlist; //�t�@�C���ꗗ

	int monster_information_flag;
	void nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...);
	int brighttime = 0;
	double timeflo = 0;
	int m_ailment_turns[Defines::AILMENT_MAX]; //�e��Ԉُ�̎c��^�[��
	int m_ailment_level[Defines::AILMENT_MAX]; //�e��Ԉُ�̃��x��
	int m_ailment_target[Defines::AILMENT_MAX]; //�e��Ԉُ��N�ɂ�����ꂽ���B�N�Ƃ����̂�0�`4�̃L�����̈ʒu�ɂ��
	int m_hate[Defines::PT_MAX]; //�e�L�����ɑ΂���w�C�g�B�f�t�H���g��100�ŁA�����Ȃǂő����B0�����ɂ͂Ȃ�Ȃ��悤�ɍH�v����
	int TargetSet(); //�w�C�g����G1�̂̍U���Ώۂ����߂ĕԂ��B�ԍ��̓p�[�e�B�[��̈ʒu

private:
	Ailment* m_ailment;
	Party* m_party;
	Randomer* m_randomer;
};

