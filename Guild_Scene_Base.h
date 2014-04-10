#pragma once
#include<stdio.h>
#include"Characters.h" //�L�����̊G�Ȃǂ�\�����邽��
#include"Party.h" //PT�̕\��
#include"Colors.h"
#include"Key_Input.h"

class Guild_Scene_Base //�M���h�N���X����s����e��ʂ̃N���X�̋��ʌ^
{
public:
	Guild_Scene_Base();
	~Guild_Scene_Base();
	virtual void Draw();
	virtual int Reaction() = 0;
	int black_h;
	int blue_h;
	int yellow_h;
	int white_h;
	int background_h1;
	char menu_list[20][20]; //�s��̈ꗗ
	int list_max; //menu_list�̐�
	int choose_now;
	char menu_explanation[20][100];
	FILE *fp;
	int choosed_number; //�I�������s��
	int str_size_max; //������̍ő�T�C�Y
	int fscanf_r(char *file_name); //�܂Ƃ߂�fscan_s
	Characters *char_pt;
	static int char_ran; //�����_���ɕ\�������Ă��鍡�̃L�����̔ԍ��B1����
	int char_flag = 1; //�L�����̕\���t���O
	Party *party;
};