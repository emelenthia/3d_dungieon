#pragma once
#include<stdio.h>
#include"MonsterList.h"
#include"Status.h"

//�����X�^�[�I�u�W�F�N�g
//�t�@�C���������ǂݍ��݁A�I�u�W�F�N�g1�ɂ������X�^�[1�̕��̋���������

class Monsters
{
public:
	Monsters(int n);
	~Monsters();
	void Draw();

	typedef enum strain //�푰�ꗗ
	{
		MAJIC_LIFE //���@����
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
};

