#pragma once
#include<stdio.h>

class Character_Data_Save //�Z�[�u�����e�L�����̉σf�[�^
{
public:
	Character_Data_Save();
	~Character_Data_Save();
	int exp[15]; //
	int Lv[15];
	char name[15][21];
	int job[15];
	int in_team[15]; //�����t���O�B1�Ȃ����
	FILE *fp[15];
	void Load_Char(char *file_pointer,int n);
	int nowhp[15]; //���݂̎c��HP
	int nowtp[15]; //���݂̎c��TP
	char file_name[15][50]; //�t�@�C�������o���Ă���
	int in_party[15]; //�Ґ��ɓ����Ă�t���O�B1�Ȃ�����Ă܂�
};