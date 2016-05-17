#include "Ailment.h"
#include"DxLib.h"

Ailment* Ailment::instance;

Ailment::Ailment()
{
	LoadAilment();
}


Ailment::~Ailment()
{
}


void Ailment::LoadAilment()
{
	FILE* fp, *fp2;
	char dammy[256];
	int temp[Defines::AILMENT_MAX_LEVEL];
	fp = fopen("./scn/status_ailment/status_ailment.txt", "r"); //��Ԉُ햼���L�����t�@�C��
	fp2 = fopen("./scn/status_ailment/ailment_value.txt", "r"); //��Ԉُ�̏ڍׂ��L�����t�@�C��
	if (fp == NULL || fp2 == NULL)
	{
		//TODO:�G���[�\����������Ƃł���悤�ɂ���
		DrawFormatString(0, 0, Colors::white, "Error in LoadAilMent()");
		ScreenFlip();
		WaitKey();
		return;
	}

	//�܂��͏�Ԉُ햼��ǂݍ���
	for (int i = 0; i < Defines::AILMENT_MAX; i++)
	{
		fscanf(fp, "%s", m_ailment[i].name);
	}

	for (int i = 0; i < Defines::AILMENT_MAX; i++)
	{
		//�ǂݔ�΂�
		fscanf(fp2, "%s", dammy);
		//�o�t�f�o�t
		fscanf(fp2, "%d", &(m_ailment[i].de_buff));
		//���s������ǂݔ�΂��c�K�v�͂Ȃ��炵��
		//fscanf(fp2, "%s", dammy);
		//�^�[����
		LoadInts(fp2, temp, Defines::AILMENT_MAX_LEVEL);
		for (int level = 0; level < Defines::AILMENT_MAX_LEVEL; level++)
		{
			m_ailment[i].turns[level] = temp[level];
		}
		//����
		LoadInts(fp2, temp, Defines::AILMENT_MAX_LEVEL);
		for (int level = 0; level < Defines::AILMENT_MAX_LEVEL; level++)
		{
			m_ailment[i].walks[level] = temp[level];
		}
	}
	
	fclose(fp);
	fclose(fp2);
}


