#pragma once
#include "Character_Data_Save.h"
#include<stdio.h>

class Character_Data : //�Z�[�u����Ȃ��L�����N�^�[�̌ŗL�f�[�^
	public Character_Data_Save
{
public:
	Character_Data();
	~Character_Data();
	int GetStatus(int n, int want); //n�Ԗڂ̃L������want(1=atk,2=def,3=int,4=res,5=dex,6=agi,7=hp,8=tp,9=�a,10=��,11=��,12=��,13=��,14=��,15=�y,16=��)���擾����
	char* GetJobName(int n); //n�Ԗڂ̃L�����̌��݂̃N���X�̖��O��Ԃ�
	char* GetJobNameabb(int n); //n�Ԗڂ̃L�����̌��݂̃N���X�̖��O�̏ȗ��`��Ԃ�
	
	FILE *fp_n_s[15];
	void Load_Char_n_s(char *file_pointer, char *file_pointer_save,int n);
	char file_name_n_s[15][50]; //�t�@�C�������o���Ă���
	int job_system[15]; //���̃L�����̐E�Ƃ̌n��
	int char_h[15][10]; //0���珇�ɁA(0+1)�̐E�Ƃ̉摜
	int char_h_i[15][10]; //0���珇�ɁA(0+1)�̐E�Ƃ̉摜�A�C�R��(���i�\������鏬�����摜)
	char char_h_name[15][10][100]; //0���珇�ɁA(0+1)�̐E�Ƃ̉摜�̃t�@�C����
	char char_h_i_name[15][10][50]; //0���珇�ɁA(0+1)�̐E�Ƃ̉摜�A�C�R���̃t�@�C����
};

