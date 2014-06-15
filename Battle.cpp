#include "Battle.h"
#include "DxLib.h"
#include "Key_Input.h"
#include"Flags.h"
#include"Colors.h"
#include"Dungeon.h"

#define swap(a,b) a^=b^=a^=b

#define nfscanf(scan_target, format_text, ...) nfscanf_(__LINE__,__FILE__,scan_target, format_text,__VA_ARGS__);
void Battle::nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...)
{
	FILE* scanf_fp;
	int ret = 0;
	va_list args;

	scanf_fp = fopen("scanf_log.txt", "w");
	fprintf(scanf_fp, "%s\n�s:%d\n", file, line);
	fclose(scanf_fp);

	va_start(args, format_text);
	ret = vfscanf(scan_target, format_text, args);
	va_end(args);

}

Battle::Battle(int ne,int* monster_number)
{
	randomer = Randomer::GetInstance();
	numenemy = ne;
	//nowchoosea = -1;

	for (int i = 0; i < 5; i++)
	{
		monsters[i] = NULL;
	}
	for (int i = 0; i < numenemy; i++)
	{
		monsters[i] = new Monsters(monster_number[i]);
	}

	party = Party::GetInstance();
	characters = Characters::GetInstance();
	for (int i = 0; i < 10; i++)
	{
		turn_active[i] = 0;
	}

	active_point[0] = 2;
	active_point[1] = 7;
	active_point[2] = -1;
	active_point[3] = -1;
	active_point[4] = -1;
	for (int i = 0; i < numenemy; i++)
	{
		active_point[i + 5] = i * 2 + 3;
	}
	minichar_size_x = 75;
	minichar_size_y = 24;

	thickfont_h = CreateFontToHandle(NULL, 21, 5);
}


Battle::~Battle()
{
}


void Battle::Draw()
{
	DrawString(220, 120, "����͉��̐퓬�V�[���ł�", GetColor(0, 0, 255));
	DrawString(220, 160, "����L�[�Ŗ߂�܂�", GetColor(0, 0, 255));

	DrawMonster();
	DrawMiniChar();
	//party->Draw();
	DrawCanActive();
}


int Battle::Reaction()
{
	int r = 0;
	if (Key_Input::buff_time[KEY_INPUT_X]&&Key_Input::buff_time[KEY_INPUT_Z]) //�f�o�b�O�p�̐퓬���甲���鏈��
	{
		Flags::battleflag = -1;
		for (int i = 0; i < numenemy; i++)
		{
			if (monsters[i] != NULL)
			{
				delete monsters[i];
			}
		}
	}

	if (!state&&!checkstate) //��b�s���I��҂�
	{
		if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1)
		{
			nowchoosef = (nowchoosef == 1 && !unionattackflag || !nowchoosef) ? 5 : --nowchoosef;
		}
		else if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && !Key_Input::buff_time[KEY_INPUT_UP])
		{
			nowchoosef = nowchoosef == 5 ? !unionattackflag : ++nowchoosef;
		}
		if (Key_Input::buff_time[KEY_INPUT_Z] == 1)
		{
			switch (nowchoosef)
			{
			case 0: //���͍U��
				checkstate = 1;
				break;
			case 1: //�ʏ�U��
				checkstate = 2;
				nowchoosea = 0;
				break;
			case 2: //�X�L��
				checkstate = 3;
				break;
			case 3: //�h��
				state = 3;
				break;
			case 4: //�A�C�e��
				checkstate = 4;
				break;
			case 5: //������
				state = 5;
				break;
			default:
				nowchoosef = 1; //�ی�
				break;
			}
		}
	}
	else if (checkstate == 1) //���͍U���I��
	{

	}
	else if (checkstate == 2) //�ʏ�U���ΏۑI��
	{
		if (Key_Input::buff_time[KEY_INPUT_LEFT] == 1)
		{
			nowchoosea = nowchoosea ? --nowchoosea : numenemy - 1;
		}
		else if (Key_Input::buff_time[KEY_INPUT_RIGHT] == 1 && !Key_Input::buff_time[KEY_INPUT_LEFT])
		{
			nowchoosea = nowchoosea == numenemy - 1 ? 0 : ++nowchoosea;
		}
		if (Key_Input::buff_time[KEY_INPUT_X] == 1) //��b�s���I���ɖ߂�
		{
			checkstate = 0;
			nowchoosea = -1;
		}
	}
	else if (state==5) //�����鏈��
	{
		Flags::battleflag = -1;
		for (int i = 0; i < numenemy; i++)
		{
			if (monsters[i] != NULL)
			{
				delete monsters[i];
			}
		}
		r = 5; //���������Ƃ�`����
		characters->lastchoosef[party->party_info[nowchar]] = 5; //�R�}���h���L��
	}

	//���s�𔻒肷��
	CheckResult();
	return r;
}


void Battle::DrawMiniChar()
{
	ActiveSort();

	for (int i = 0; i < party->GetNumMember() + numenemy; i++)
	{
		if (turn_active[i] <= 4) //isplayer
		{
			//���w���ƕ�����悤��
			DrawBox(
				640 - minichar_size_x - 15,
				360 - (i + 1) * minichar_size_y - 4 * i,
				640,
				360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
				Colors::blue, TRUE);
			//�L�����摜�̕\��
			DrawExtendGraph(
				640 - minichar_size_x,
				360 - (i + 1) * minichar_size_y - 4 * i,
				640,
				360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
				characters->char_h_i[party->party_info[turn_active[i]]][characters->job[party->party_info[turn_active[i]]]], TRUE);
			//�f�o�b�O�I��
			DrawFormatString(640 - minichar_size_x - 15, 360 - (i + 1) * minichar_size_y - 4 * i, Colors::purple, "%d", active_point[turn_active[i]]);
		}
		else //!isplayer
		{
			//�G�w���ƕ�����悤��
			DrawBox(
				640 - minichar_size_x - 15,
				360 - (i + 1) * minichar_size_y - 4 * i,
				640,
				360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
				Colors::red, TRUE);
			//�L�����摜�̕\��
			DrawExtendGraph(
				640 - minichar_size_x,
				360 - (i + 1) * minichar_size_y - 4 * i,
				640,
				360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
				monsters[turn_active[i] - 5]->graph_m, TRUE);
			//�f�o�b�O�I��
			DrawFormatString(640 - minichar_size_x - 15, 360 - (i + 1) * minichar_size_y - 4 * i, Colors::purple, "%d", active_point[turn_active[i]]);
		}
	}

	//���ݍs�����̃L����������
	DrawBox(640 - minichar_size_x - 15 - 100, 360 - minichar_size_y, 640 - minichar_size_x - 15 - 5, 360, Colors::blue, TRUE);
	DrawFormatString(640 - minichar_size_x - 15 - 90, 360 - minichar_size_y + 4, Colors::white, "ACTIVE ��", TRUE);
	
}


void Battle::ActiveSort()
{
	int temp_number = 0, temp_min = 0;
	bool finishflag = FALSE;


	for (int n = 0; n < 10; n++)
	{
		temp_number = -1;
		temp_min = INT_MAX;
		for (int i = 0; i < 10; i++)
		{
			//���Ɏ擾�������̂͂���[
			for (int i2 = 0; i2<n; i2++)
			{
				if (turn_active[i2] == i)
				{
					finishflag = TRUE;
					break;
				}
			}
			if (!finishflag)
			{
				if (temp_min>active_point[i] && active_point[i] >= 0) //�K��0�ȏ�
				{
					temp_min = active_point[i];
					temp_number = i;
				}
			}
			else
			{
				finishflag = FALSE;
			}
		}
		turn_active[n] = temp_number;
	}

	//�s�������̃L�����Ɉڍs����
	if (nowchar != turn_active[0])
	{
		nowchar = turn_active[0];
		TurnStart();

	}
}


void Battle::DrawCanActive()
{
	const int pos_x_lu = 5;
	const int pos_y_lu = 480 - 30 * 6;
	const int pos_x_rd = 160 - 10;
	int i = 0;

	if (nowchar < 5)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����

		DrawBox(pos_x_lu + 15, pos_y_lu + nowchoosef * 30 + 5, pos_x_rd, pos_y_lu + nowchoosef * 30 + 5 + 21, Colors::yellow, TRUE); //���ݑI��ł��

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�
		if (!state&&!checkstate)
		{

			if (unionattackflag)
			{
				DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 5, Colors::white, thickfont_h, "���͍U��");
			}
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 35, Colors::white, thickfont_h, "�U��");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 65, Colors::white, thickfont_h, "�X�L��");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 95, Colors::white, thickfont_h, "�h��");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 125, Colors::white, thickfont_h, "�A�C�e��");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 155, Colors::white, thickfont_h, "������");

			//�s���̐���
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����
			DrawBox(0, 0, 640, 20, Colors::blue, TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�
			DrawFormatString(5, 1, Colors::white, nowchoosef == 0 ? "���͍U�������܂��B" :
												  nowchoosef == 1 ? "�������Ă��镐��ōU�����܂��B" :
												  nowchoosef == 2 ? "�Z�▂�@���g�p���܂��B" :
												  nowchoosef == 3 ? "�G�̍U���ɔ����Ėh��̑Ԑ����Ƃ�܂��B" :
												  nowchoosef == 4 ? "�������Ă���A�C�e�����g�p���܂��B" :
												  nowchoosef == 5 ? "�퓬����̒E�o�����݂܂��B" :
																	"�G���[�ł��B");
		}

		//�ʏ�U���I��
		if (checkstate == 2)
		{
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 35, Colors::white, thickfont_h, "�U��");
			DrawFormatString(5, 1, Colors::white, "�U���Ώۂ�I�����Ă�������");
		}
	}
}


void Battle::DrawStringsCenterToHandle(int cpos_x, int cpos_y, int color_h,int font_h, const char* str)
{
	DrawFormatStringToHandle(cpos_x - GetDrawStringWidthToHandle(str,strlen(str),font_h) / 2, cpos_y, Colors::white, font_h, str);
}


void Battle::DrawMonster()
{

	switch (numenemy)
	{
	case 1:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 2 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);
		}
		break;
	case 2:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);
		}
		if (monsters[1]->Status_c.alive)
		{
			monsters[1]->Draw(640 / 2 + 640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 1 ? TRUE : FALSE);
		}
		break;
	case 3:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);
		}
		if (monsters[1]->Status_c.alive)
		{
			monsters[1]->Draw(640 / 2 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 1 ? TRUE : FALSE);
		}
		if (monsters[2]->Status_c.alive)
		{
			monsters[2]->Draw(640 / 2 + 640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 2 ? TRUE : FALSE);
		}
		break;
	case 4:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);
		}
		if (monsters[1]->Status_c.alive)
		{
			monsters[1]->Draw(640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 1 ? TRUE : FALSE);
		}
		if (monsters[2]->Status_c.alive)
		{
			monsters[2]->Draw(640 / 2 + 640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 2 ? TRUE : FALSE);
		}
		if (monsters[3]->Status_c.alive)
		{
			monsters[3]->Draw(640 / 2 + 640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 3 ? TRUE : FALSE);
		}
		break;
	case 5:
		if (monsters[0]->Status_c.alive)
		{
			monsters[0]->Draw(640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);
		}
		if (monsters[1]->Status_c.alive)
		{
			monsters[1]->Draw(640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 1 ? TRUE : FALSE);
		}
		if (monsters[2]->Status_c.alive)
		{
			monsters[2]->Draw(640 / 2 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 2 ? TRUE : FALSE);
		}
		if (monsters[3]->Status_c.alive)
		{
			monsters[3]->Draw(640 / 2 + 640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 3 ? TRUE : FALSE);
		}
		if (monsters[4]->Status_c.alive)
		{
			monsters[4]->Draw(640 / 2 + 640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 4 ? TRUE : FALSE);
		}
		break;
	default:
		break;
	}
}


void Battle::CheckResult()
{
	for (int i = 0; i < numenemy; i++)
	{
		if (!monsters[i]->Status_c.alive)
		{
			break;
		}
		if (i == numenemy - 1)
		{
			winflag++;
		}
	}
}


void Battle::TurnStart()
{
	if (nowchar < 5) //�v���C���[�L�����N�^�[�̏ꍇ
	{
		nowchoosef = characters->lastchoosef[party->party_info[nowchar]];
		nowchooses = characters->lastchoosef_skill[party->party_info[nowchar]];
	}
	else if (nowchar < 10) //�G�L�����N�^�[�̏ꍇ
	{
	}
}