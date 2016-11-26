#include "Camp.h"
#include"Flags.h"
#include"Colors.h"
#include"Options.h"



Camp::Camp()
{
	str_size_max = 160;//�Ƃ肠����
	
	fscanf_r("./scn/guild/camp_list.cns");
	m_options = Options::GetInstance();
	char_pt = Characters::GetInstance();
	m_options = Options::GetInstance();
	guild_pt = new Guild_PT;
	char_ran = 0;
	m_choose_now = 0;
	m_party = Party::GetInstance();
	m_1f_flag = TRUE;
	//choosed_number = -1;
	//savedata = SaveData::GetInstance();
//	character_show = NULL;
}


Camp::~Camp()
{
}

void Camp::Draw()
{
	int temp_size_x = str_size_max + 36;

	//DrawExtendGraph(0, 0, 640, 480, background_h1, TRUE); //�w�i

	if (!(m_options->optionflag || Flags::character_show_flag || guild_pt->guild_pt_flag)) //�I�v�V�������\�����łȂ�
	{
		if (m_char_flag)
		{
			//TODO:�L�����̉摜�\�������ŘM��
			DrawRotaGraph(480, 300, 0.5, 0, char_pt->char_h[char_ran][char_pt->job[char_ran] - 1], TRUE);
		}

		DrawBox(2 + temp_size_x, 39, 4 + temp_size_x, list_max * 20 + 42, Colors::yellow, TRUE); //�䎌���̎���E
		DrawBox(18, 39, 20, list_max * 20 + 42, Colors::yellow, TRUE); //�䎌���̎��荶
		DrawBox(19, 38, 4 + temp_size_x, 40, Colors::yellow, TRUE); //�䎌���̎����
		DrawBox(19, list_max * 20 + 41, 4 + temp_size_x, list_max * 20 + 43, Colors::yellow, TRUE); //�䎌���̎��艺

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����
		DrawBox(20, 40, 2 + temp_size_x, list_max * 20 + 40, Colors::black, TRUE); //�䎌��
		DrawBox(0, 0, 640, 20, Colors::blue, TRUE); //������
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

		DrawBox(21, 41 + m_choose_now * 20, 1 + temp_size_x, 60 + m_choose_now * 20, Colors::yellow, TRUE); //�I�𒆂̂�����
		DrawFormatString(22, 2, Colors::white, "%s", m_menu_explanation[m_choose_now], TRUE); //�������悤

		for (int i = 0; i < list_max; i++)
		{
			DrawFormatString(22, 42 + i * 20, (m_choose_now == i ? Colors::black : Colors::white), " %s", m_menu_list[i]); //�I�΂ꂽ�̂́A���ł���
		}

		//�p�[�e�B�̕`��
		m_party->Draw();
	}
	else if (m_options->optionflag)
	{
		m_options->Draw();
	}
	else if (Flags::character_show_flag)
	{
		m_character_show->Draw();
	}
	else if (guild_pt->guild_pt_flag)
	{
		guild_pt->Draw();
	}
}


int Camp::Reaction()
{
	choosed_number = -2;
	if (!(m_options->optionflag || Flags::character_show_flag || guild_pt->guild_pt_flag))
	{
		if (Key_Input::buff_time[KEY_INPUT_C] == 1)
		{
			if (m_1f_flag != FALSE)
			{
				m_1f_flag = FALSE;
			}
			else
			{
				choosed_number = -1;
			}
		}
		else if (Key_Input::buff_time[KEY_INPUT_X] == 1)
		{
			choosed_number = -1;
		}
		else if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
		{
			choosed_number = m_choose_now;
		}
		else if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_UP] != 11)
		{
			m_choose_now = (m_choose_now > 0 ? m_choose_now - 1 : list_max - 1); //���[�v�ł���悤��
		}
		else if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_DOWN] != 11)
		{
			m_choose_now = (m_choose_now < list_max - 1 ? m_choose_now + 1 : 0);
		}
		

		//�������I�΂ꂽ��
		if (choosed_number != -2)
		{
			switch (choosed_number)
			{
			case BAG:
			{

			}
			break;
			case EQUIP:
			{

			}
			break;
			case CSUTOM:
			{

			}
			break;
			case STATES:
			{
				Flags::character_show_flag++;
				m_character_show = new Character_Show;
			}
			break;
			case QUEST:
			{

			}
			break;
			case OTHER:
			{

			}
			break;
			case SAVE:
			{
				//savedata->Save();
				//party->Save();
			}
			break;
			case LOAD:
			{

			}
			break;
			case OPTION:
			{
				m_options->optionflag++;
			}
			break;
			case TITLE:
			{

			}
			break;
			case CLOSE:
			{
				choosed_number = -1;
			}
			break;
			}
		}

	}
	else if (m_options->optionflag)
	{
		m_options->Reaction();
	}
	else if (Flags::character_show_flag)
	{
		m_character_show->Reaction();
		if (Key_Input::buff_time[KEY_INPUT_X] == 1)
		{
			Flags::character_show_flag = 0;
			delete m_character_show;
			m_character_show = NULL;
		}
	}
	else if (guild_pt->guild_pt_flag)
	{
		guild_pt->Reaction();
	}

	return choosed_number;
}


int Camp::fscanf_r(char *file_name)
{
	int return_number = 0;
	FILE* fp;

	fp = fopen(file_name, "r");
	if (fp == NULL)
	{
		DrawExtendFormatString(0, 0, 1.0, 1.0, GetColor(255, 0, 0), "Error!:I miss opening to %s", file_name);
		WaitKey();
	}

	fscanf(fp, "%d", &list_max);
	for (int i = 0; i < list_max; i++)
	{
		fscanf_s(fp, "%s", m_menu_list[i], 19);
		fscanf_s(fp, "%s", m_menu_explanation[i], 99);
		str_size_max = (GetDrawFormatStringWidth(m_menu_list[i]) > str_size_max ? GetDrawFormatStringWidth(m_menu_list[i]) : str_size_max); //���̍ő�̒��������߂�
	}
	return return_number;
}
