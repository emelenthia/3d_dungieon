#pragma once
#include<stdio.h>

class Character_Data_Save //�Z�[�u�����e�L�����̉σf�[�^
{
public:
	Character_Data_Save();
	~Character_Data_Save();
	int exp; //
	char name[21];
	int job;
	bool in_team; //�����t���O�B1�Ȃ����
	FILE *fp;
	void Load_Char(char *file_pointer);
	char file_name[50]; //�t�@�C�������o���Ă���
};

