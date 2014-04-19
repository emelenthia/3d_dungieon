#include "Character_Data.h"
#include<stdio.h>
#include"DxLib.h"
#include"Defines.h"

Character_Data::Character_Data()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		fp_n_s[i] = NULL;
		strcpy(file_name_n_s[i], "null");
	}
}


Character_Data::~Character_Data()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		if (fp_n_s[i] != NULL)
		{
			fclose(fp_n_s[i]);
		}
	}
}


void Character_Data::Load_Char_n_s(char *file_pointer, char *file_pointer_save,int n)
{
	if (!(strcmp(file_name_n_s[n], "null")))
	{
		strcpy(file_name_n_s[n], file_pointer); //���̃t�@�C�������o���Ă����B�Q�[�����̂ɂ͈Ӗ����Ȃ�
	}
	fp_n_s[n] = fopen(file_pointer, "r"); //�w�肳�ꂽ�t�@�C�����J��

	if (fp_n_s[n] == NULL) //�G���[����
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name_n_s[n]);
		WaitKey();
		DxLib_End();				// �c�w���C�u�����g�p�̏I������
		exit(1);
	}

	fscanf(fp_n_s[n], "%d", &job_system[n]);
	
	
	//�摜�̓ǂݍ���
	for (int i = 0; i < 1; i++) //�摜�����������̑Ώ����ł���悤�ɂ���
	{
		fscanf_s(fp_n_s[n], "%s", char_h_name[n][i], 99);
		char_h[n][i] = LoadGraph(char_h_name[n][i]);


		fscanf_s(fp_n_s[n], "%s", char_h_i_name[n][i], 99);
		char_h_i[n][i] = LoadGraph(char_h_i_name[n][i]);
	}
	//�Ƃ肠�����S�������摜���g��
	for (int i = 0; i < 10; i++)
	{
		char_h[n][i] = char_h[n][0];
		char_h_i[n][i] = char_h_i[n][0];
	}



	if (char_h[n][0] == -1) //�G���[����
		{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", char_h_name[n][0]);
			WaitKey();
			DxLib_End();				// �c�w���C�u�����g�p�̏I������
			exit(1);
		}
		//fscanf_s(fp, "%s", char_h_i_name[i], 49);
	
	//�p�����Ńt�@�C�����J��
	Load_Char(file_pointer_save, n);
}


int Character_Data::GetStatus(int n,int want)
{
	int temp = 0; //�Ԃ�l

	switch (job_system[n])
	{
	case 1: //�t�@�C�^�[�n
		switch (job[n])
		{
		case 1: //�t�@�C�^�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //�p���f�B��
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //�o�[�T�[�J�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //���@���L���[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //��
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //�_�[�N���[�h
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 2: //�}�W�b�N���[�U�[�n
		switch (job[n])
		{
		case 1: //�}�W�b�N���[�U�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //�\�[�T���X
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //�G���`�����g���X
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //�v���[�X�e�X
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //�E�B�b�`
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //�}�W�J���v�����Z�X
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 7: //�Z�[�W
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 8: //�r�V���b�v
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 3: //�X�J�E�g�n
		switch (job[n])
		{
		case 1: //�X�J�E�g
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //�A�[�`���[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //�A�T�V��
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //�X�i�C�p�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //�g���W���[�n���^�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //���m��
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 4: //���C�h�n
		switch (job[n])
		{
		case 1: //���C�h
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //�o�[�h
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //�_���T�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //�f�B�[���@
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //�~�X�g���X
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //�G�g���[��
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	case 5: //�X�s�G���[�n
		switch (job[n])
		{
		case 1: //�X�s�G���[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 2: //�h�[���}�X�^�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 3: //�g���b�N�X�^�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 4: //�\�E���T���i�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 5: //�p�s����
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		case 6: //�W���[�J�[
			switch (want)
			{
			case 1:
				temp = Lv[n];
				break;
			case 2:
				temp = Lv[n];
				break;
			case 3:
				temp = Lv[n];
				break;
			case 4:
				temp = Lv[n];
				break;
			case 5:
				temp = Lv[n];
				break;
			case 6:
				temp = Lv[n];
				break;
			case 7:
				temp = Lv[n] * 6;
				break;
			case 8:
				temp = Lv[n];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
	return temp;
}


char* Character_Data::GetJobName(int n)
{
	char job_name[20];
	switch (job_system[n])
	{
	case 1: //�t�@�C�^�[�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "�t�@�C�^�[");
			break;
		case 2:
			strcpy(job_name, "�p���f�B��");
			break;
		case 3:
			strcpy(job_name, "�o�[�T�[�J�[");
			break;
		case 4:
			strcpy(job_name, "���@���L���[");
			break;
		case 5:
			strcpy(job_name, "��");
			break;
		case 6:
			strcpy(job_name, "�_�[�N���[�h");
			break;
		default:
			break;
		}
		break;
	case 2: //�}�W�b�N���[�U�[�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "�}�W�b�N���[�U�[");
			break;
		case 2:
			strcpy(job_name, "�\�[�T���X");
			break;
		case 3:
			strcpy(job_name, "�G���`�����g���X");
			break;
		case 4:
			strcpy(job_name, "�v���[�X�e�X");
			break;
		case 5:
			strcpy(job_name, "�E�B�b�`");
			break;
		case 6:
			strcpy(job_name, "�}�W�J���v�����Z�X");
			break;
		case 7:
			strcpy(job_name, "�Z�[�W");
			break;
		case 8:
			strcpy(job_name, "�r�V���b�v");
			break;
		default:
			break;
		}
		break;
	case 3: //�X�J�E�g�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "�X�J�E�g");
			break;
		case 2:
			strcpy(job_name, "�A�[�`���[");
			break;
		case 3:
			strcpy(job_name, "�A�T�V��");
			break;
		case 4:
			strcpy(job_name, "�X�i�C�p�[");
			break;
		case 5:
			strcpy(job_name, "�g���W���[�n���^�[");
			break;
		case 6:
			strcpy(job_name, "���m��");
			break;
		default:
			break;
		}
		break;
	case 4: //���C�h�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "���C�h");
			break;
		case 2:
			strcpy(job_name, "�o�[�h");
			break;
		case 3:
			strcpy(job_name, "�_���T�[");
			break;
		case 4:
			strcpy(job_name, "�f�B�[���@");
			break;
		case 5:
			strcpy(job_name, "�~�X�g���X");
			break;
		case 6:
			strcpy(job_name, "�G�g���[��");
			break;
		default:
			break;
		}
		break;
	case 5: //�X�s�G���[�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "�X�s�G���[");
			break;
		case 2:
			strcpy(job_name, "�h�[���}�X�^�[");
			break;
		case 3:
			strcpy(job_name, "�g���b�N�X�^�[");
			break;
		case 4:
			strcpy(job_name, "�\�E���T���i�[");
			break;
		case 5:
			strcpy(job_name, "�p�s����");
			break;
		case 6:
			strcpy(job_name, "�W���[�J�[");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}


	return job_name;
}


char* Character_Data::GetJobNameabb(int n)
{
	char job_name[5];
	switch (job_system[n])
	{
	case 1: //�t�@�C�^�[�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "FT");
			break;
		case 2:
			strcpy(job_name, "PL");
			break;
		case 3:
			strcpy(job_name, "BE");
			break;
		case 4:
			strcpy(job_name, "VL");
			break;
		case 5:
			strcpy(job_name, "SA");
			break;
		case 6:
			strcpy(job_name, "DL");
			break;
		default:
			break;
		}
		break;
	case 2: //�}�W�b�N���[�U�[�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "MU");
			break;
		case 2:
			strcpy(job_name, "SO");
			break;
		case 3:
			strcpy(job_name, "EN");
			break;
		case 4:
			strcpy(job_name, "PR");
			break;
		case 5:
			strcpy(job_name, "WT");
			break;
		case 6:
			strcpy(job_name, "MP");
			break;
		case 7:
			strcpy(job_name, "SG");
			break;
		case 8:
			strcpy(job_name, "BS");
			break;
		default:
			break;
		}
		break;
	case 3: //�X�J�E�g�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "SC");
			break;
		case 2:
			strcpy(job_name, "AR");
			break;
		case 3:
			strcpy(job_name, "AS");
			break;
		case 4:
			strcpy(job_name, "SN");
			break;
		case 5:
			strcpy(job_name, "TH");
			break;
		case 6:
			strcpy(job_name, "KN");
			break;
		default:
			break;
		}
		break;
	case 4: //���C�h�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "MD");
			break;
		case 2:
			strcpy(job_name, "BD");
			break;
		case 3:
			strcpy(job_name, "DN");
			break;
		case 4:
			strcpy(job_name, "DI");
			break;
		case 5:
			strcpy(job_name, "MI");
			break;
		case 6:
			strcpy(job_name, "ET");
			break;
		default:
			break;
		}
		break;
	case 5: //�X�s�G���[�n
		switch (job[n])
		{
		case 1:
			strcpy(job_name, "SP");
			break;
		case 2:
			strcpy(job_name, "DM");
			break;
		case 3:
			strcpy(job_name, "TS");
			break;
		case 4:
			strcpy(job_name, "SS");
			break;
		case 5:
			strcpy(job_name, "PA");
			break;
		case 6:
			strcpy(job_name, "JO");
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}


	return job_name;
}