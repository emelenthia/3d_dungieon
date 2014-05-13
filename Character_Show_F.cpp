#include "Character_Show_F.h"
#include<DxLib.h>
#include"Flags.h"
#include"Defines.h"
#include"Key_Input.h"
#include"Guild_Scene_Base.h"


Character_Show_F::Character_Show_F()
{
	characters = Characters::GetInstance();

	black = GetColor(0, 0, 0);
	yellow = GetColor(255, 255, 0);
	darkyellow = GetColor(255, 205, 0);
	white = GetColor(255, 255, 255);
	blue = GetColor(0, 0, 255);
	darkblue = GetColor(0, 0, 80);
	lightblue = GetColor(24, 127, 196);
	green = GetColor(153, 204, 0);
	brown = GetColor(153, 51, 0);
	red = GetColor(255, 0, 0);
	fp = fopen("./scn/char/char_show.cns", "r");

	if (fp == NULL)
	{
		DrawString(0, 0, "Error. I can not open file.", yellow);
		WaitKey();
	}

	//�X�e�[�^�X�̕\�����@��ǂݍ���
	fscanf(fp, "%d", &namemax);
	for (int i = 0; i < namemax; i++)
	{
		fscanf(fp, "%s", names[i]);
	}

}


void Character_Show_F::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����
	DrawBox(0, 0, 640, 20, blue, TRUE); //������
	numchar = 0;
	if (Flags::nowscene == 0x8011d) //�M���h���
	{
		for (int i = 0; i < Defines::char_max; i++)
		{
			if (characters->in_team[i])
			{
				number_list[i] = numchar;
				numchar++;
			}
			else
			{
				number_list[i] = -1;
			}
		}
	}
	else //�_���W�������
	{
		for (int i = 0; i < Defines::char_max; i++)
		{
			if (characters->in_party[i])
			{
				number_list[i] = numchar;
				numchar++;
			}
			else
			{
				number_list[i] = -1;
			}
		}
	}

	pos_y_rd = pos_y_lu + numchar * 20;

	DrawBox(pos_x_lu, pos_y_lu, pos_x_rd, pos_y_rd, black, TRUE);

	int db_x_lu = pos_x_rd + 10;
	int db_y_lu = pos_y_lu + 22;
	int db_x_rd = pos_x_rd + 300;
	int db_y_rd = pos_y_lu + 22 + 140;
	DrawBox(db_x_rd, db_y_lu, db_x_lu, db_y_rd, darkblue, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

	DrawBox(db_x_lu - 2, db_y_lu - 22, db_x_rd + 2, db_y_lu - 2, lightblue, TRUE); //HP�Ƃ����O�Ƃ�
	DrawBox(db_x_rd, db_y_lu, db_x_rd + 2, db_y_rd, lightblue, TRUE); //�X�e�[�^�X�̎���E
	DrawBox(db_x_lu - 2, db_y_lu, db_x_lu, db_y_rd, lightblue, TRUE); //�X�e�[�^�X�̎��荶
	DrawBox(db_x_lu - 2, db_y_lu - 2, db_x_rd + 2, db_y_lu, lightblue, TRUE); //�X�e�[�^�X�̎����
	DrawBox(db_x_lu - 2, db_y_rd, db_x_rd + 2, db_y_rd + 2, lightblue, TRUE); //�X�e�[�^�X�̎��艺

	DrawFormatString(db_x_lu + 5, db_y_lu + 2 - 20, yellow, "%s", names[0]); //Lv
	DrawFormatString(db_x_lu + 5, db_y_lu + 2, darkyellow, "%s", names[1]); //HP
	DrawFormatString((db_x_rd - db_x_lu)*0.5 + db_x_lu + 5, db_y_lu + 2, green, "%s", names[2]); //TP
	DrawFormatString(db_x_lu + 5, db_y_lu + 22, yellow, "%s", names[3]); //ATK
	DrawFormatString(db_x_lu + 5, db_y_lu + 42, yellow, "%s", names[4]); //DEF
	DrawFormatString(db_x_lu + 5, db_y_lu + 62, yellow, "%s", names[5]); //INT
	DrawFormatString(db_x_lu + 5, db_y_lu + 82, yellow, "%s", names[6]); //RES
	DrawFormatString(db_x_lu + 5, db_y_lu + 102, yellow, "%s", names[7]); //DEX
	DrawFormatString(db_x_lu + 5, db_y_lu + 122, yellow, "%s", names[8]); //AGI

	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 42, yellow, "%s", names[9]); //EXP
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 62, yellow, "%s", names[10]); //NEXT
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 82, yellow, "%s", names[11]); //�a�ϐ�
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 102, yellow, "%s", names[12]); //�ˑϐ�
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/"), db_y_lu + 122, yellow, "%s", names[13]); //���ϐ�

	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 42, red, "%s", names[14]); //�Αϐ�
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 62, blue, "%s", names[14]); //���ϐ�
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 82, green, "%s", names[14]); //���ϐ�
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 102, brown, "%s", names[14]); //�y�ϐ�
	DrawFormatString(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999 "), db_y_lu + 122, yellow, "%s", names[14]); //���ϐ�

	DrawBox(pos_x_rd, pos_y_lu, pos_x_rd + 2, pos_y_rd, yellow, TRUE); //�L�����N�^�[�Q�̎���E
	DrawBox(pos_x_lu - 2, pos_y_lu, pos_x_lu, pos_y_rd, yellow, TRUE); //�L�����N�^�[�Q�̎��荶
	DrawBox(pos_x_lu - 2, pos_y_lu - 2, pos_x_rd + 2, pos_y_lu, yellow, TRUE); //�L�����N�^�[�Q�̎����
	DrawBox(pos_x_lu - 2, pos_y_rd, pos_x_rd + 2, pos_y_rd + 2, yellow, TRUE); //�L�����N�^�[�Q�̎��艺
	
	DrawBox(pos_x_lu + 1, choosenow * 20 + pos_y_lu + 1, pos_x_rd - 1, (choosenow + 1) * 20 + pos_y_lu - 1, yellow, TRUE); //���I�΂�Ă�̂�����
	int already = 0; //���O�������I������L�����̑���
	for (int i = 0; i < Defines::char_max; i++)
	{
		if (Flags::nowscene == 0x8011d)
		{
			if (characters->in_team[i])
			{
				DrawFormatString(pos_x_lu + 2, pos_y_lu + 2 + already * 20, (choosenow == number_list[i] ? black : white), "%s", characters->name[i]);
				if (choosenow == number_list[i])
				{
					Guild_Scene_Base::char_ran = i; //���ݑI�΂�Ă���L������\������
					Status_ = characters->GetStatus(i);

					//���ݑI������Ă���q���C���̏���\��
					DrawFormatString(db_x_lu + 5 + GetDrawStringWidth(names[0], strlen(names[0])) + 5, db_y_lu + 2 - 20, white, "%d", characters->Lv[i]);
					DrawFormatString(db_x_lu + 5 + GetDrawStringWidth(names[0], strlen(names[0])) + 20, db_y_lu + 2 - 20, white, "%s", characters->name[i]);
					char jobname_temp[20]; //�߂�l�ł͒������擾�ł��Ȃ������Ȃ̂ňꎞ�I�ɕۑ�
					strcpy(jobname_temp, characters->GetJobName(i));
					DrawFormatString(db_x_lu + 200 - 0.5 * GetDrawStringWidth(jobname_temp, strlen(jobname_temp)), db_y_lu + 2 - 20, white, "%s", jobname_temp);

					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, characters->nowhp[i], white);
					DrawString(db_x_lu + 15 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, "/", white);
					DrawIntRight(db_x_lu + 20 + GetDrawFormatStringWidth("ATK9999") + GetDrawFormatStringWidth("/%d", 9999), db_y_lu + 2, Status_.hpmax, white);

					DrawIntRight((db_x_rd - db_x_lu)*0.5 + db_x_lu + 5 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, characters->nowtp[i], white);
					DrawString((db_x_rd - db_x_lu)*0.5 + db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, "/", white);
					DrawIntRight((db_x_rd - db_x_lu)*0.5 + db_x_lu + 15 + GetDrawFormatStringWidth("/%d", 9999) + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 2, Status_.tpmax, white);


					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 22, Status_.atk, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 42, Status_.def, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 62, Status_.int_s, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 82, Status_.res, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 102, Status_.dex, white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999"), db_y_lu + 122, Status_.agi, white);

					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999"), db_y_lu + 42, characters->exp[i], white);
					DrawIntRight(db_x_lu + 10 + GetDrawFormatStringWidth("ATK9999/EXP  9999999"), db_y_lu + 62, characters->Lv[i] * 10 - characters->exp[i], white);
				}
				already++;
			}
		}
	}

}


int Character_Show_F::Reaction()
{
	if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_UP] != 11)
	{
		choosenow = (choosenow > 0 ? choosenow - 1 : numchar - 1); //���[�v�ł���悤��
	}
	if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_DOWN] != 11)
	{
		choosenow = (choosenow < numchar - 1 ? choosenow + 1 : 0);
	}

	if (Key_Input::buff_time[KEY_INPUT_X] == 1 || (Key_Input::buff_time[KEY_INPUT_Z] == 1 && choosenow == numchar))
	{
		Flags::character_show_flag = 0;
	}
	return 0;
}


void Character_Show_F::DrawIntRight(int x, int y, int num, int color)
{
	DrawFormatString(x - GetDrawFormatStringWidth("%d", num), y, color, "%d", num);
}


int Character_Show_F::GetCharNow()
{
	int number = -1;

	for (int i = 0; i < 13; i++)
	{
		//���ݑI�����Ă���L���������������ꍇ
		if (choosenow == number_list[i])
		{
			number = i;
			break;
		}
	}

	return number;
}