#pragma once
#include<stdio.h>
#include"Character_Haruka.h" //�L�����̊G�Ȃǂ�\�����邽��
#include"Character_02.h"
#include"Character_Data_Save.h"

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
	Character_Data *char_pt[2];
	//Character_Haruka char_p[0] = Character_Haruka::GetInstance();
	//Character_02 *Chihaya = Character_02::GetInstance(); //�o����΃|�C���^�̔z��ɂ�����
	static int char_ran; //�����_���ɕ\�������Ă��鍡�̃L�����̔ԍ��B1����
};