#pragma once
#include "Character_Data_Save.h"
#include<stdio.h>

class Character_Data : //�Z�[�u����Ȃ��L�����N�^�[�̌ŗL�f�[�^
	public Character_Data_Save
{
public:
	Character_Data();
	~Character_Data();
	int hp;
	int atk;
	int def;
	int int_s;
	int res;
	int agi;
	FILE *fp_n_s;
	void Load_Char_n_s(char *file_pointer, char *file_pointer_save);
	char file_name_n_s[50]; //�t�@�C�������o���Ă���
	int job_max; //���̃L�����̐E�Ɛ�
	int char_h[10]; //0���珇�ɁA(0+1)�̐E�Ƃ̉摜
	int char_h_i[10]; //0���珇�ɁA(0+1)�̐E�Ƃ̉摜�A�C�R��
	char char_h_name[10][100]; //0���珇�ɁA(0+1)�̐E�Ƃ̉摜�̃t�@�C����
	char char_h_i_name[10][50]; //0���珇�ɁA(0+1)�̐E�Ƃ̉摜�A�C�R���̃t�@�C����
};

