#include "Character_Data_Save.h"
#include"DxLib.h"


Character_Data_Save::Character_Data_Save()
{
	fp = NULL;
	strcpy(file_name, "null");
}


Character_Data_Save::~Character_Data_Save()
{
	if (fp != NULL)
	{
		fclose(fp);
	}
}


void Character_Data_Save::Load_Char(char *file_pointer)
{
	if (!(strcmp(file_name, "null")))
	{
		strcpy(file_name, file_pointer); //���̃t�@�C�������o���Ă����B�Q�[�����̂ɂ͈Ӗ����Ȃ�
	}
	fp = fopen(file_pointer, "r"); //�w�肳�ꂽ�t�@�C�����J��

	if (fp == NULL) //�G���[����
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name);
		WaitKey();
		DxLib_End();				// �c�w���C�u�����g�p�̏I������
		exit(1);
	}

	fscanf_s(fp, "%d", &in_team, 1);
	if (in_team)
	{
		fscanf(fp, "%d", &exp);
		fscanf(fp, "%d", &job);
		fscanf_s(fp, "%s", name, 20);
	}
}