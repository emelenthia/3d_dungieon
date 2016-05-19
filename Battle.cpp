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

Battle::Battle(int ne, int* monster_number, bool escape_flag)
{
	//������
	randomer = Randomer::GetInstance();
	numenemy = ne;
	can_escape_flag = escape_flag;
	gameover_h = LoadGraph("./pics/gameover.bmp"); 
	m_chooseSkill = 0;
	m_t_skillNumber = -1;

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
	battle_effect = BattleEffect::GetInstance();
	m_skill = Skill::GetInstance();
	m_ailment = Ailment::GetInstance();
	for (int i = 0; i < 10; i++)
	{
		turn_active[i] = 0;
		guardflag[i] = FALSE;
	}
	for (int i = 0; i < 10; i++)
	{
		temp_damage[i] = -1;
	}

	//�e�X�g�f�[�^
	active_point[0] = 7;
	active_point[1] = 2;
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

	//�����J�n�O��1��Ăяo��
	ActiveSort();
	nowchar = turn_active[0];
	TurnStart();
	
}


Battle::~Battle()
{
}


void Battle::Draw()
{
	DebugPrintf(1);
	

	if (!issueflag)
	{
		DrawMonster();
		DrawMiniChar();
		//party->Draw();
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����
		DrawBox(0, 0, 640, 20, Colors::blue, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�

		if (nowchar < 5)
		{
			switch (state)
			{
			case CHOOSE_ACT:
				DrawCanActive();
				break;
			case NORMAL_ATTACK:
				DrawAttack();
				break;
			case SKILL:
				DrawSkill();
				break;
			case GUARD:
				DrawFormatString(20, 0, Colors::white, "%s�͖h��̑Ԑ��B", characters->name[party->party_info[nowchar]]);
				break;
			case ESCAPE: //����������Ă��Ȃ����Ƃɂ��΂炭�C���t���Ȃ�����
				DrawCanActive();
				break;
			}
		}
		else if (nowchar < 10)
		{

			if (time < NORMAL_ATTACK_TIME&&time>1) //�\������肭�����Ȃ�
			{
				battle_effect->Draw_e(temp, time > 2 ? -1 : 0); //�ŏ���time��1�̂����ŕ�����ɂ���
			}
			DrawFormatString(20, 0, Colors::white, "%s�̍U���i�����j:%d�I", monsters[nowchar - 5]->Status_.name, temp);
		}
	}
	else if (issueflag == 1) //RESULT���
	{
		DrawResult();
	}
	else if (issueflag == -1) //�Q�[���I�[�o�[���
	{
		DrawGameOver();
	}
}


int Battle::Reaction()
{
	DebugPrintf(2);
	

	int r = 0;
	//�f�o�b�O�p�̐퓬���甲���鏈��
	if (Key_Input::buff_time[KEY_INPUT_X]&&Key_Input::buff_time[KEY_INPUT_Z])
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


	if (!issueflag)
	{
		if (nowchar < 5) //���ݍs�����̃L�����������L�����������ꍇ
		{
			switch (state) //��ȏ���
			{
			case CHOOSE_ACT: //��b�s���I��҂�
				if (!checkstate)
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
							finishflag = 0;
							while (!finishflag)
							{
								if (monsters[nowchoosea]->Status_c.alive&&numenemy - m_numdiedEnemy > 0) //�������[�v�΍� //TODO:�E���̏����͗v��̂��ǂ����B
								{
									finishflag = TRUE;
								}
								else
								{
									nowchoosea = nowchoosea == numenemy - 1 ? 0 : ++nowchoosea;
								}
							}
							break;
						case 2: //�X�L��
							if (characters->GetCanSkillNum(party->party_info[nowchar], Defines::BATTLE) > 0) //�g�p�\�X�L��������ꍇ�̂ݑI���\
							{
								checkstate = 3;
							}
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
						//�����ڕW������ł�����E�ɂ��炵�Ă���
						do
						{
							nowchoosea = nowchoosea ? --nowchoosea : numenemy - 1;
						} while (!monsters[nowchoosea]->Status_c.alive&&numenemy - m_numdiedEnemy > 0);
					}
					else if (Key_Input::buff_time[KEY_INPUT_RIGHT] == 1 && !Key_Input::buff_time[KEY_INPUT_LEFT])
					{
						do
						{
							nowchoosea = nowchoosea == numenemy - 1 ? 0 : ++nowchoosea;
						} while (!monsters[nowchoosea]->Status_c.alive&&numenemy - m_numdiedEnemy > 0);
					}
					if (Key_Input::buff_time[KEY_INPUT_X] == 1) //��b�s���I���ɖ߂�
					{
						checkstate = 0;
						nowchoosea = -1;
					}
					else if (Key_Input::buff_time[KEY_INPUT_Z] == 1) //�U���Ɉڍs
					{
						checkstate = 0;
						state = NORMAL_ATTACK;
						temp_nowchoosea = nowchoosea;
						nowchoosea = -1; //�_�ł�h������
						characters->lastchoosef[party->party_info[nowchar]] = 1; //�R�}���h���L��
					}
				}
				else if (checkstate == 3) //�X�L���I��
				{
					if (Key_Input::buff_time[KEY_INPUT_UP] % 10 == 1)
					{
						m_chooseSkill = (!m_chooseSkill ? characters->GetCanSkillNum(party->party_info[nowchar],Defines::BATTLE) - 1 : --m_chooseSkill); //���ݑI�𒆂̃X�L������ԏ�Ȃ��ԉ��ɁB����ȊO�Ȃ�ЂƂ��
					}
					else if (Key_Input::buff_time[KEY_INPUT_DOWN] % 10 == 1 && !Key_Input::buff_time[KEY_INPUT_UP])
					{
						m_chooseSkill = (m_chooseSkill == characters->GetCanSkillNum(party->party_info[nowchar], Defines::BATTLE) - 1 ? 0 : ++m_chooseSkill); //���ݑI�𒆂̃X�L������ԉ��Ȃ��ԏ�ɁA����ȊO�Ȃ�����
					}
					else if (Key_Input::buff_time[KEY_INPUT_X] == 1) //��b�s���I���ɖ߂�
					{
						checkstate = 0;
					}
					else if (Key_Input::buff_time[KEY_INPUT_Z] == 1) //�X�L�����s�A�������̓X�L���ΏۑI���Ɉڍs
					{
						int skillnumber = characters->GetSkillNumber(party->party_info[nowchar], m_chooseSkill, Defines::BATTLE); //�X�L���ԍ����擾����
						if (m_skill->m_skill_PT[skillnumber].type_kind == 0 ||
							m_skill->m_skill_PT[skillnumber].type_kind == 5 ||
							m_skill->m_skill_PT[skillnumber].type_kind == 10 ||
							m_skill->m_skill_PT[skillnumber].type_kind == 17) //���̃X�L�����G1�̂�I������X�L���Ȃ�
						{
							//�����I��Ώۂ̐ݒ�
							finishflag = 0;
							nowchoosea = 0;
							while (!finishflag)
							{
								if (monsters[nowchoosea]->Status_c.alive&&numenemy - m_numdiedEnemy > 0) //�������[�v�΍� //TODO:�E���̏����͗v��̂��ǂ����B
								{
									finishflag = TRUE;
								}
								else
								{
									nowchoosea = nowchoosea == numenemy - 1 ? 0 : ++nowchoosea;
								}
							}
							checkstate = 31; //�G1�̂�I�������Ԃ�
						}
						else //����ȊO�A�܂�I�񂾏u�Ԕ���������̂Ȃ�
						{
							checkstate = 0;
							state = SKILL; //�X�L�������ۂɎ��s�����Ԃ�
						}
					}
				}
				else if (checkstate == 31) //TODO:���switch�ɒ����B
				{
					if (Key_Input::buff_time[KEY_INPUT_LEFT] == 1)
					{
						//�����ڕW������ł�����E�ɂ��炵�Ă���
						do
						{
							nowchoosea = nowchoosea ? --nowchoosea : numenemy - 1;
						} while (!monsters[nowchoosea]->Status_c.alive&&numenemy - m_numdiedEnemy > 0);
					}
					else if (Key_Input::buff_time[KEY_INPUT_RIGHT] == 1 && !Key_Input::buff_time[KEY_INPUT_LEFT])
					{
						do
						{
							nowchoosea = nowchoosea == numenemy - 1 ? 0 : ++nowchoosea;
						} while (!monsters[nowchoosea]->Status_c.alive&&numenemy - m_numdiedEnemy > 0);
					}
					if (Key_Input::buff_time[KEY_INPUT_X] == 1) //��b�s���I���ɖ߂�
					{
						checkstate = 0;
						nowchoosea = -1;
					}
					else if (Key_Input::buff_time[KEY_INPUT_Z] == 1) //�U���Ɉڍs
					{
						checkstate = 0;
						state = SKILL;
						temp_nowchoosea = nowchoosea;
						nowchoosea = -1; //�_�ł�h������
						characters->lastchoosef[party->party_info[nowchar]] = 1; //�R�}���h���L��
					}
				}
				break;

			case NORMAL_ATTACK:

				break;
			case SKILL:
				//TODO:time++�𓝈ꂷ��B���̕ӂ�
				if (m_t_skillNumber != -1)
				{

				}
				else
				{
					m_t_skillNumber = characters->GetSkillNumber(party->party_info[nowchar], m_chooseSkill, Defines::BATTLE);
				}
				switch (m_t_skillNumber) //�e�X�L���̏���
				{
				case 1: //�E�H�[�N���C�B���̕ӂ�#define���悤
					if (time == 27) //#define�ŁA�X�L�������^�C���Ƃ��ݒ肵�悤
					{
						for (int i = 0; i < party->GetNumMember(); i++)
						{
							characters->ailment_turn[party->party_info[i]][11] = m_ailment->m_ailment[AIL_WARCRY].turns[characters->m_canSkillLevel[party->party_info[nowchar]][1]]; //�^�[������ݒ�
							characters->ailment_walks[party->party_info[i]][11] = m_ailment->m_ailment[AIL_WARCRY].walks[characters->m_canSkillLevel[party->party_info[nowchar]][1]]; //������ݒ�
						}
					}
					break;
				default:
					break;
				}

				break;
			case GUARD:
				ActGuard();
				break;

			case ESCAPE: //�����鏈��
				if (can_escape_flag)
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
					characters->lastchoosef[party->party_info[nowchar]] = ESCAPE; //�R�}���h���L��
				}
				else //�������Ȃ�!
				{
					time++;
					if (time > 30)
					{
						state = 0;
						time = 0;
					}
				}
			}
		}
		else if (nowchar < 10) //�G�̍s��
		{
			//�����ɓG�̍s�����L�q

			if (!time)
			{
				finishflag = 0;
				while (!finishflag)
				{
					temp = randomer->GetRand() % party->GetNumMember();
					//temp = temp; TODO:���̃R�[�h�ɈӖ��͂���̂�?
					if (characters->status_c[party->party_info[temp]].alive)
					{
						finishflag = TRUE;
					}
				}
			}

			if (time == NORMAL_ATTACK_TIME / 2) //TODO:�̗͂����炷�^�C�~���O�𓝈ꂷ��
			{
				characters->status_c[party->party_info[temp]].hp -= monsters[nowchar - 5]->Status_.atk * 3 * (guardflag[temp] ? 0.5 : 1);
			}

			if (time>NORMAL_ATTACK_TIME)
			{
				temp = 0;
				time = 0;
				active_point[nowchar] += 10;
				turn_finish_flag = TRUE;
			}
			else
			{
				time++;
			}
		}


		//�s�������̃L�����Ɉڍs����
		if (turn_finish_flag)
		{
			TurnFinish();
			if (turn_finish_finish_flag)
			{
				ActiveSort();
				TurnStart();
			}
		}
	}
	else if (issueflag == 1) //RESULT���
	{

		if (Key_Input::buff_time[KEY_INPUT_Z] == 1) //�퓬�I��
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

	}


	return r;
}


void Battle::DrawMiniChar()
{
	DebugPrintf(3);

	for (int i = 0; i < party->GetNumMember() + numenemy; i++)
	{
		if (turn_active[i] >= 0)
		{
			if (turn_active[i] <= 4) //isplayer
			{
				if (characters->status_c[party->party_info[turn_active[i]]].alive) //�ꉞ
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
					DrawFormatString(640 - minichar_size_x - 15, 360 - (i + 1) * minichar_size_y - 4 * i, Colors::black, "%d", active_point[turn_active[i]]);
				}
			}
			else //!isplayer
			{
				if (monsters[turn_active[i] - 5]->Status_c.alive)
				{
					//�G�w���ƕ�����悤��
					DrawBox(
						640 - minichar_size_x - 15 - (nowchoosea == turn_active[i]-5?10:0), //���ݑI�΂�Ă���Ȃ班������
						360 - (i + 1) * minichar_size_y - 4 * i,
						640,
						360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
						Colors::red, TRUE);
					//�L�����摜�̕\��
					DrawExtendGraph(
						640 - minichar_size_x - (nowchoosea == turn_active[i] - 5 ? 10 : 0),
						360 - (i + 1) * minichar_size_y - 4 * i,
						640 - (nowchoosea == turn_active[i] - 5 ? 10 : 0),
						360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
						monsters[turn_active[i] - 5]->graph_m, TRUE);
					//�f�o�b�O�I��
					DrawFormatString(640 - minichar_size_x - 15, 360 - (i + 1) * minichar_size_y - 4 * i, Colors::black, "%d", active_point[turn_active[i]]);
				}
			}
		}
	}

	//���ݍs�����̃L����������
	DrawBox(640 - minichar_size_x - 15 - 100, 360 - minichar_size_y, 640 - minichar_size_x - 15 - 5, 360, Colors::blue, TRUE);
	DrawFormatString(640 - minichar_size_x - 15 - 90, 360 - minichar_size_y + 4, Colors::white, "ACTIVE ��", TRUE);
	
}


void Battle::ActiveSort()
{

	DebugPrintf(4);

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

	nowchar = turn_active[0]; //�s�������̃L�����ɓ���ւ���
}


void Battle::DrawCanActive()
{

	DebugPrintf(5);

	const int pos_x_lu = 5;
	const int pos_y_lu = 480 - 30 * 6;
	const int pos_x_rd = 160 - 10;
	int i = 0;


	if (nowchar < 5)
	{
		if (checkstate != 3 && checkstate != 4 && checkstate != 31) //�X�L����A�C�e���̑I�����łȂ�
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //����

			DrawBox(pos_x_lu + 15, pos_y_lu + nowchoosef * 30 + 5, pos_x_rd, pos_y_lu + nowchoosef * 30 + 5 + 21, Colors::yellow, TRUE); //���ݑI��ł��

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //���ɖ߂�
		}
		if (!state&&!checkstate)
		{

			if (unionattackflag)
			{
				DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 5, Colors::white, thickfont_h, "���͍U��");
			}
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 35, Colors::white, thickfont_h, "�U��");
			if (characters->GetCanSkillNum(party->party_info[nowchar], Defines::BATTLE) > 0)
			{
				DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 65, Colors::white, thickfont_h, "�X�L��");
			}
			else
			{
				DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 65, Colors::black, thickfont_h, "�X�L��");
			}
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 95, Colors::white, thickfont_h, "�h��");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 125, Colors::white, thickfont_h, "�A�C�e��");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 155, (can_escape_flag?Colors::white:Colors::black), thickfont_h, "������");

			//�s���̐���
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
			DrawFormatString(5, 1, Colors::white, "�U���Ώۂ�I�����Ă��������B");
		}

		//�X�L���I��
		if (checkstate == 3 || checkstate == 31)
		{
			characters->DrawSkill(party->party_info[nowchar], Defines::BATTLE, 0, 300, m_chooseSkill); 
		}

		//�������Ȃ�
		if (state == 5 && !can_escape_flag)
		{
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 155, Colors::black, thickfont_h, "������");
			DrawFormatString(15, 1, Colors::white, "�ޘH���ǂœ������Ȃ��I");
		}
	}
}


void Battle::DrawStringsCenterToHandle(int cpos_x, int cpos_y, int color_h,int font_h, const char* str)
{
	DrawFormatStringToHandle(cpos_x - GetDrawStringWidthToHandle(str,strlen(str),font_h) / 2, cpos_y, color_h, font_h, str);
}


void Battle::DrawMonster()
{
	DebugPrintf(6);

	switch (numenemy)
	{
	case 1:
		monsters[0]->Draw(640 / 2 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);

		break;
	case 2:
		monsters[0]->Draw(640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);

		monsters[1]->Draw(640 / 2 + 640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 1 ? TRUE : FALSE);

		break;
	case 3:
		monsters[0]->Draw(640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);

		monsters[1]->Draw(640 / 2 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 1 ? TRUE : FALSE);

		monsters[2]->Draw(640 / 2 + 640 / 4 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 2 ? TRUE : FALSE);

		break;
	case 4:
		monsters[0]->Draw(640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);

		monsters[1]->Draw(640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 1 ? TRUE : FALSE);

		monsters[2]->Draw(640 / 2 + 640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 2 ? TRUE : FALSE);

		monsters[3]->Draw(640 / 2 + 640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 3 ? TRUE : FALSE);

		break;
	case 5:
		monsters[0]->Draw(640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 0 ? TRUE : FALSE);

		monsters[1]->Draw(640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 1 ? TRUE : FALSE);

		monsters[2]->Draw(640 / 2 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 2 ? TRUE : FALSE);

		monsters[3]->Draw(640 / 2 + 640 / 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 3 ? TRUE : FALSE);

		monsters[4]->Draw(640 / 2 + 640 / 2 * 2 / 3 - monstersizex / 2, monsterposy, monstersizex, monstersizey, nowchoosea == 4 ? TRUE : FALSE);

		break;
	default:
		break;
	}
}


void Battle::CheckResult()
{
	DebugPrintf(7);

	for (int i = 0; i < party->GetNumMember(); i++)
	{
		if (characters->status_c[party->party_info[i]].alive)
		{
			break;
		}
		if (i == party->GetNumMember() - 1)
		{
			issueflag--;
		}
	}
	for (int i = 0; i < numenemy; i++)
	{
		if (monsters[i]->Status_c.alive)
		{
			break;
		}
		if (i == numenemy - 1)
		{
			issueflag++;
		}
	}

	//����ł���L�����̍��v
	numdiedchar = 0;
	m_numdiedEnemy = 0;
	for (int i = 0; i < party->GetNumMember(); i++)
	{
		if (active_point[i] == -1)
		{
			numdiedchar++;
		}
	}
	for (int i = 0; i < numenemy; i++)
	{
		if (active_point[i + 5] == -1) //����ł���L�����̍��v
		{
			numdiedchar++;
			m_numdiedEnemy++;
		}
	}
}


void Battle::TurnFinish()
{
	DebugPrintf(8);


	turn_finish_finish_flag = FALSE;
	for (int i = 0; i < numenemy; i++)
	{
		//�����̔���
		if (monsters[i]->Status_c.hp <= 0 && monsters[i]->Status_c.alive)
		{
			monsters[i]->Status_c.alive = 0;
			active_point[i + 5] = -1;
			//��Ԉُ�����Z�b�g

		}
		//��Ԉُ��1�^�[���i�߂�
	}
	for (int i = 0; i < party->GetNumMember(); i++)
	{
		//�����̔���
		if (characters->status_c[party->party_info[i]].hp <= 0 && characters->status_c[party->party_info[i]].alive)
		{
			characters->status_c[party->party_info[i]].alive = 0;
			active_point[i] = -1;
			//��Ԉُ�����Z�b�g
			for (int ail_count = 0; ail_count < Defines::AILMENT_MAX; ail_count++)
			{
				characters->ailment_turn[party->party_info[i]][ail_count] = 0;
				characters->ailment_walks[party->party_info[i]][ail_count] = 0;
			}
		}
	}

	//���������̂̓��[�v�O�ł��Ȃ��Ƃ�
	if (nowchar < Defines::PT_MAX) //�����̃L�����̃^�[���̏ꍇ�̏���
	{
		//��Ԉُ��1�^�[���i�߂�
		int temp_nowchar = party->party_info[nowchar];
		for (int ail_count = 0; ail_count < Defines::AILMENT_MAX; ail_count++)
		{
			if (characters->ailment_turn[temp_nowchar][ail_count] > 0)
			{
				characters->ailment_turn[temp_nowchar][ail_count]--;
				characters->ailment_walks[temp_nowchar][ail_count] -= 10;
				//10������������0�ɂ���
				if (characters->ailment_walks[temp_nowchar][ail_count] < 0)
				{
					characters->ailment_walks[temp_nowchar][ail_count] = 0;
				}
			}
		}
	}
	//������
	m_t_skillNumber = -1;

	//���s�𔻒肷��
	CheckResult();
	turn_finish_finish_flag = TRUE;
}

void Battle::TurnStart()
{
	DebugPrintf(9);


	if (nowchar < 5) //�v���C���[�L�����N�^�[�̏ꍇ
	{
		nowchoosef = characters->lastchoosef[party->party_info[nowchar]];
		nowchooses = characters->lastchoosef_skill[party->party_info[nowchar]];
	}
	else if (nowchar < 10) //�G�L�����N�^�[�̏ꍇ
	{
	}
	turn_finish_flag = FALSE;
	guardflag[nowchar] = FALSE;
}


void Battle::DrawAttack()
{
	DebugPrintf(10);


	if (state == NORMAL_ATTACK)
	{
		DrawFormatString(20, 1, Colors::white, "%s�̍U���i�����j�I", characters->name[party->party_info[nowchar]]);

		//1�񂾂��_���[�W�v�Z�B�Ƃ肠��������1�݂̂̂ɑΉ�
		if (temp_damage[0] == -1)
		{
			DamageCalculat(nowchar, -1, temp_damage, temp_nowchoosea + Defines::PT_MAX);
		}
		if (time < NORMAL_ATTACK_TIME)
		{
			//�����ɃG�t�F�N�g����
			battle_effect->Draw(numenemy * 10 + temp_nowchoosea, time ? -1 : 0, temp_damage);
			
		}
		if (time == NORMAL_ATTACK_TIME)
		{
			//�����̓_���[�W�����B����̂���1F���炷�K�v������
			monsters[temp_nowchoosea]->Status_c.hp -= temp_damage[temp_nowchoosea + Defines::PT_MAX];
		}
		if (time > NORMAL_ATTACK_TIME)
		{
			//�s���I������
			for (int i = 0; i < 10; i++)
			{
				temp_damage[i] = -1;
			}
			temp_nowchoosea = -1;
			time = 0;
			state = 0;
			active_point[nowchar] += 9;
			turn_finish_flag = TRUE;
		}
		else
		{
			time++;
		}
	}
}


void Battle::DrawResult()
{
	DebugPrintf(11);


	DrawExtendFormatString(20, 20, 2, 2, Colors::white, "RESULT");
}


void Battle::ActGuard()
{
	DebugPrintf(12);


	if (state == GUARD)
	{
		if (time < GUARD_TIME)
		{
		}
		else if (time == GUARD_TIME)
		{
			guardflag[nowchar] = TRUE;
		}
		if (time > GUARD_TIME)
		{
			//�s���I������
			time = 0;
			state = 0;
			active_point[nowchar] += 7;
			turn_finish_flag = TRUE;
			characters->lastchoosef[party->party_info[nowchar]] = GUARD; //�R�}���h���L��
		}
		else
		{
			time++;
		}
	}
	else
	{

	}
}


void Battle::DrawGameOver()
{
	DebugPrintf(13);


	DrawRotaGraph(60, 80,2.0,0.0, gameover_h, TRUE);
}

void Battle::DebugPrintf(int number)
{
	if (debugflag)
	{
		if ((debug_fp = fopen("./log/debug_log_battle.cns", "w")) != NULL)
		{
			fprintf(debug_fp, "%d", number);
			fclose(debug_fp);
			debug_fp = nullptr;
		}
		else
		{
			DrawFormatString(0, 50, Colors::white, "Error in Battle::DebugPrintf");
		}
	}
}


void Battle::DrawSkill()
{
	DebugPrintf(14);


	if (state == SKILL)
	{
		//��₱�����̂ŋL��
		int skillNumber = characters->GetSkillNumber(party->party_info[nowchar], m_chooseSkill, Defines::BATTLE);
		DrawFormatString(20, 1, Colors::white, "%s��%s�I", characters->name[party->party_info[nowchar]], m_skill->m_skill_PT[skillNumber].m_skillList_PT);

		if (m_skill->m_skill_PT[skillNumber].m_skillType == 1) //�U���n�̃X�L���Ȃ�
		{
			//1�񂾂��_���[�W�v�Z�B�Ƃ肠��������1�݂̂̂ɑΉ�
			if (temp_damage[temp_nowchoosea + Defines::PT_MAX] == -1)
			{
				DamageCalculat(nowchar, skillNumber, temp_damage, temp_nowchoosea + Defines::PT_MAX);
			}
			if (time < NORMAL_ATTACK_TIME)
			{
				//�����ɃG�t�F�N�g����
				battle_effect->Draw(numenemy * 10 + temp_nowchoosea, time ? -1 : m_skill->m_skill_PT[skillNumber].effect_number, temp_damage);

			}
			if (time == NORMAL_ATTACK_TIME)
			{
				//�����̓_���[�W�����B����̂���1F���炷�K�v������
				monsters[temp_nowchoosea]->Status_c.hp -= temp_damage[temp_nowchoosea + Defines::PT_MAX];
			}
		}
		else //����ȊO
		{
			//�����ɃG�t�F�N�g�����������Bbattle_effect�ɓn��temp_damage��-1�Ȃ�c�݂�����
		}
		if (time > NORMAL_ATTACK_TIME)
		{
			//�s���I������
			for (int i = 0; i < 10; i++)
			{
				temp_damage[i] = -1;
			}
			temp_nowchoosea = -1;
			time = 0;
			state = 0;
			active_point[nowchar] += 2;
			turn_finish_flag = TRUE;
		}
		else
		{
			time++;
		}
	}
}


void Battle::DamageCalculat(int char_numb, int act_numb, int * damage, int target_numb)
{
	DebugPrintf(15);

	if (act_numb >= 0) //�ʏ�U������Ȃ��Ȃ�
	{
		if (char_numb < Defines::PT_MAX) //�����L�����Ȃ�BMEMO:���������͂Ȃ����X�L�����G�����ʂȂ̂Łc��������Ƃ��͋��L�ɂ��悤�B
		{
			damage[target_numb] = characters->GetStatus(party->party_info[char_numb]).atk *
				m_skill->m_skill_PT[act_numb].value[characters->m_canSkillLevel[party->party_info[char_numb]][act_numb]] *
				(guardflag[target_numb] ? 0.5 : 1) / 14;
		}
		else //�G�L�����Ȃ�
		{

		}
	}
	else if (act_numb == -1)//�ʏ�U���Ȃ�
	{
		if (char_numb < Defines::PT_MAX) //�ꉞ�����Ƃ�
		{
			temp_damage[target_numb] = characters->GetStatus(party->party_info[char_numb]).atk *
				100 * (guardflag[target_numb] ? 0.5 : 1) / 14 +
				(characters->ailment_turn[party->party_info[char_numb]][10] ? 20 : 0); //���̍s�̓E�H�[�N���C�̃e�X�g�p�B//TODO;�S��Ԉُ��#define���ăR�[�h�������₷������
		}
		else //�G�L�����Ȃ�
		{

		}
	}
	else //TODO:�f�o�b�N�p
	{
		DrawString(100, 100, "Error in DamageCalculat()", Colors::purple);
	}
}
