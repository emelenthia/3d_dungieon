#include "Character_Data_Save.h"
#include"DxLib.h"
#include"Defines.h"

Character_Data_Save::Character_Data_Save()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		fp[i] = NULL;
		strcpy(file_name[i], "null");
	}
	m_skill = Skill::GetInstance();
	m_ailment = Ailment::GetInstance();
}


Character_Data_Save::~Character_Data_Save()
{
	for (int i = 0; i < Defines::char_max; i++)
	{
		if (fp[i] != NULL)
		{
			fclose(fp[i]);
		}
	}
}


void Character_Data_Save::Load_Char(char *file_pointer,int n)
{
	if (!(strcmp(file_name[n], "null")))
	{
		strcpy(file_name[n], file_pointer); //���̃t�@�C�������o���Ă����B�Q�[�����̂ɂ͈Ӗ����Ȃ�
	}
	fp[n] = fopen(file_pointer, "r"); //�w�肳�ꂽ�t�@�C�����J��

	if (fp[n] == NULL) //�G���[����
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name[n]);
		WaitKey();
		DxLib_End();				// �c�w���C�u�����g�p�̏I������
		exit(1);
	}

	//�F�X�ǂݍ���
	fscanf(fp[n], "%d", &in_team[n]);
	if (in_team)
	{
		fscanf(fp[n], "%d", &exp[n]);
		fscanf(fp[n], "%d", &job[n]);
		fscanf(fp[n], "%d", &Lv[n]);
		fscanf_s(fp[n], "%s", name[n], 20);
		fscanf(fp[n], "%d", &in_party[n]);
		fscanf(fp[n], "%d", &status_c[n].hp);
		fscanf(fp[n], "%d", &status_c[n].tp);
		fscanf(fp[n], "%d", &lastchoosef[n]);
		fscanf(fp[n], "%d", &lastchoosef_skill[n]);
		fgetc(fp[n]); //���s�������̂Ă�
		for (int i = 0; i < SKILL_MAX_PT; i++)
		{
			m_canSkillLevel[n][i] = fgetc(fp[n]) - '0'; //�����𐔎��ɕϊ�����
		}
		//��Ԉُ�̎c��^�[�������擾
		int ail_temp[Defines::AILMENT_MAX];
		LoadInts(fp[n], ail_temp);
		for (int i = 0; i < Defines::AILMENT_MAX; i++)
		{
			ailment_turn[n][i] = ail_temp[i];
		}
		//��Ԉُ�̎c��������擾
		LoadInts(fp[n], ail_temp);
		for (int i = 0; i < Defines::AILMENT_MAX; i++)
		{
			ailment_walks[n][i] = ail_temp[i];
		}
		//��Ԉُ�̃��x�����擾
		LoadInts(fp[n], ail_temp);
		for (int i = 0; i < Defines::AILMENT_MAX; i++)
		{
			ailment_level[n][i] = ail_temp[i];
		}
	}
}

void Character_Data_Save::DrawSkill(int chara, int mode, int pos_x, int pos_y,int choose)
{
	int count = 0;
	const int SIZE_X = 280; //�g�̔w�i�̑傫������ɂ���
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����

	//DrawBox(pos_x, pos_y - 5, pos_x + 303, pos_y + GetCanSkillNum(chara, mode) * 20 , Colors::dark_yellow, TRUE); //����̘g��\��
	DrawBox(pos_x , pos_y, pos_x + SIZE_X, pos_y + GetCanSkillNum(chara, mode) * 20, Colors::gray, TRUE); //�g�̔w�i��\��

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

	//��ɕ����\��
	DrawStringToHandle(pos_x + 20, pos_y - 14, "SKILL", Colors::yellow, Colors::fh_half);
	DrawStringToHandle(pos_x + SIZE_X - 20, pos_y - 14, "TP", Colors::yellow, Colors::fh_half);
	for (int i = 0; i < SKILL_MAX_PT; i++)
	{
		if (m_canSkillLevel[chara][i] >= 1 && m_skill->m_skill_PT[i].m_skillType >= 1) //���̃X�L���̃��x����1�ȏ�ŁA���̃X�L�����p�b�V�u����Ȃ��ꍇ
		{
			if (count == choose) //������i���g��Ȃ��̂́A�E���̐����̍ő�͎g�p�ł���X�L�����Ȃ���
			{
				DrawBox(pos_x + 2, pos_y + count * 20, pos_x + SIZE_X, pos_y + count * 20 + 20, Colors::yellow, TRUE); //��15�������̕�
				DrawFormatString(5, 1, Colors::white, "%s", m_skill->m_skill_PT[i].m_skillText); //�X�L���̐����̕\��
				DrawFormatString(pos_x + 20, pos_y + count * 20 + 2, Colors::black, "%s", m_skill->m_skill_PT[i].m_skillList_PT);
				DrawFormatString(pos_x + SIZE_X - 20, pos_y + count * 20 + 2, Colors::black, "%d", m_skill->m_skill_PT[i].need_TP[m_canSkillLevel[chara][i]]); //�K�vTP�̕\��
			}
			else //���ݑI������Ă���X�L���ȊO�͔��F�ŕ\������
			{
				DrawFormatString(pos_x + 20, pos_y + count * 20, Colors::white, "%s", m_skill->m_skill_PT[i].m_skillList_PT);
				DrawFormatString(pos_x + SIZE_X - 20, pos_y + count * 20, Colors::white, "%d", m_skill->m_skill_PT[i].need_TP[m_canSkillLevel[chara][i]]); //�K�vTP�̕\��
			}
			count++;
		}
	}

	DrawBox(pos_x + SIZE_X, pos_y, pos_x + SIZE_X + 2, pos_y + count * 20 + 2, Colors::dark_yellow, TRUE); //�䎌���̎���E
	DrawBox(pos_x, pos_y, pos_x + 2, pos_y + count * 20 + 2, Colors::dark_yellow, TRUE); //�䎌���̎��荶
	DrawBox(pos_x, pos_y - 2, pos_x + SIZE_X + 2, pos_y, Colors::dark_yellow, TRUE); //�䎌���̎����
	DrawBox(pos_x, pos_y + count * 20, pos_x + SIZE_X + 2, pos_y + count * 20 + 2, Colors::dark_yellow, TRUE); //�䎌���̎��艺

	if (!count) //�\�����ׂ��X�L�����Ȃ��ꍇ�c�܂��������낤����
	{
	}
	else
	{

	}
}

char Character_Data_Save::GetCanSkillNum(int chara, int mode)
{
	int count = 0;
	for (int i = 0; i < SKILL_MAX_PT; i++)
	{
		if (m_canSkillLevel[chara][i] >= 1) //���̃X�L���̃��x����1�ȏ�
		{
			if (mode != -1)
			{
				if (m_skill->GetSkillCanUse_PT(i, mode)) //�w�肵��mode�Ŏg����Ȃ��
				{
					count++;
				}
			}
			else //����mode���w�肵�Ȃ��ꍇ
			{
				count++;
			}
		}
	}
	return count;
}

int Character_Data_Save::GetSkillNumber(int chara, int number, int mode)
{
	int count = -1; //number��0�̉\��������̂ŁA-1����X�^�[�g����
	for (int i = 0; i < SKILL_MAX_PT; i++)
	{
		if (m_canSkillLevel[chara][i] >= 1) //i�Ԗڂ̃X�L�����o���Ă���
		{
			if (m_skill->GetSkillCanUse_PT(i, mode)) //���ꂪ�w�肳�ꂽmode�Ŏg�p�\�Ȃ��
			{
				count++; //����͏ォ��count�ڂɂ���X�L��
				if (count == number) //�ォ��number�ڂɗ�����
				{
					return i; //���̃X�L���̔ԍ���Ԃ�
				}
			}
		}
	}
	return -1; //�Ȃ�ɂ���������Ȃ������ꍇ�͈ꉞ�G���[�Ƃ���s
}


int Character_Data_Save::GetAilNumber(int chara, int number)
{
	int count = 0, i = 0;

	if (number <= 0)
	{
		return -1; //�ی�
	}
	for (; i < Defines::AILMENT_MAX; i++)
	{
		if (ailment_turn[chara][i])
		{
			count++;
			if (count == number)
			{
				return i;
			}
		}
	}
	return -1; //������Ȃ������炱���ɗ���
}


int Character_Data_Save::GetAilNum(int chara)
{
	int count = 0;
	for (int i = 0; i < Defines::AILMENT_MAX; i++)
	{
		if (ailment_turn[chara][i]) //�悭�l������-1������c?
		{
			count++;
		}
	}
	return count;
}
