#include "Character_Data.h"
#include<stdio.h>
#include"DxLib.h"

Character_Data::Character_Data()
{
	fp_n_s = NULL;
	strcpy(file_name_n_s, "null");
}


Character_Data::~Character_Data()
{
	if (fp_n_s != NULL)
	{
		fclose(fp_n_s);
	}
}


void Character_Data::Load_Char_n_s(char *file_pointer, char *file_pointer_save)
{
	if (!(strcmp(file_name_n_s, "null")))
	{
		strcpy(file_name_n_s, file_pointer); //���̃t�@�C�������o���Ă����B�Q�[�����̂ɂ͈Ӗ����Ȃ�
	}
	fp_n_s = fopen(file_pointer, "r"); //�w�肳�ꂽ�t�@�C�����J��

	if (fp_n_s == NULL) //�G���[����
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name_n_s);
		WaitKey();
		DxLib_End();				// �c�w���C�u�����g�p�̏I������
		exit(1);
	}

	fscanf(fp_n_s, "%d", &job_max);
	for (int i = 0; i < job_max;i++)
	{
		fscanf_s(fp_n_s, "%s", char_h_name[i], 99);
		//fscanf_s(fp_n_s, "%s", char_h_i_name[i], 49);
		char_h[i] = LoadGraph(char_h_name[i]);
		//char_h_i[i] = LoadGraph(char_h_i_name[i]);
		if (char_h[i] == -1) //�G���[����
		{
			DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", char_h_name[i]);
			WaitKey();
			DxLib_End();				// �c�w���C�u�����g�p�̏I������
			exit(1);
		}
		//fscanf_s(fp, "%s", char_h_i_name[i], 49);
	}


	//�p�����Ńt�@�C�����J��
	Load_Char(file_pointer_save);
}