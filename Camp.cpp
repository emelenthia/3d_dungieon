#include "Camp.h"
#include"Flags.h"
#include"Colors.h"
#include"Options.h"



Camp::Camp()
{
	str_size_max = 160;//とりあえず
	
	fscanf_r("./scn/guild/camp_list.cns");
	m_options = Options::GetInstance();
	char_pt = Characters::GetInstance();
	m_options = Options::GetInstance();
	m_itemList = ItemList::GetInstance();
	guild_pt = new Guild_PT;
	char_ran = 0;
	m_party = Party::GetInstance();
	m_1f_flag = TRUE;

	//キャンプ画面のメニューリストの設定
	m_dxLB_CampMenu = new DXListBox;
	if (m_dxLB_CampMenu != nullptr)
	{
		for (int i = 0; i < list_max; i++)
		{
			string temp = m_menu_list[i];
			m_dxLB_CampMenu->AddNameList(temp);
			temp = m_menu_explanation[i];
			m_dxLB_CampMenu->AddExplanationList(temp);
		}
		m_dxLB_CampMenu->SetExplanationFlag(true);
		int temp_size_x = str_size_max + 36;
		m_dxLB_CampMenu->SetPos(18, 39, temp_size_x, list_max * 20);
	}

	//choosed_number = -1;
	//savedata = SaveData::GetInstance();
	//character_show = NULL;
}


Camp::~Camp()
{
}


void Camp::Draw()
{
	int temp_size_x = str_size_max + 36;

	//DrawExtendGraph(0, 0, 640, 480, background_h1, TRUE); //背景

	if (!(m_options->optionflag || Flags::character_show_flag || guild_pt->guild_pt_flag)) //オプション等表示中でない
	{
		if (m_char_flag)
		{
			//TODO:キャラの画像表をここで弄る
			DrawRotaGraph(480, 300, 0.5, 0, char_pt->char_h[char_ran][char_pt->job[char_ran] - 1], TRUE);
		}
		
		//メニュー欄の描画
		m_dxLB_CampMenu->Draw();

		//パーティの描画
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


void Camp::DrawBag()
{
	int numitem = 0;
	for (int i = 0; i < numitem; i++)
	{

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
			choosed_number = m_dxLB_CampMenu->GetChoose();
		}
		else if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_UP] != 11)
		{
			m_dxLB_CampMenu->UpChoose();
		}
		else if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && Key_Input::buff_time[KEY_INPUT_DOWN] != 11)
		{
			m_dxLB_CampMenu->DownChoose();
		}
		

		//何かが選ばれた時
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
		str_size_max = (GetDrawFormatStringWidth(m_menu_list[i]) > str_size_max ? GetDrawFormatStringWidth(m_menu_list[i]) : str_size_max); //横の最大の長さを求める
	}
	return return_number;
}
