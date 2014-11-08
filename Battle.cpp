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
	fprintf(scanf_fp, "%s\n行:%d\n", file, line);
	fclose(scanf_fp);

	va_start(args, format_text);
	ret = vfscanf(scan_target, format_text, args);
	va_end(args);

}

Battle::Battle(int ne, int* monster_number, bool escape_flag)
{
	//初期化
	randomer = Randomer::GetInstance();
	numenemy = ne;
	can_escape_flag = escape_flag;
	gameover_h = LoadGraph("./pics/gameover.bmp");

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
	for (int i = 0; i < 10; i++)
	{
		turn_active[i] = 0;
		guardflag[i] = FALSE;
	}
	for (int i = 0; i < 5; i++)
	{
		temp_damage[i] = -1;
	}

	//テストデータ
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

	//試合開始前に1回呼び出す
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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透過
		DrawBox(0, 0, 640, 20, Colors::blue, TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す

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
			case GUARD:
				DrawFormatString(20, 0, Colors::white, "%sは防御の態勢。", characters->name[party->party_info[nowchar]]);
				break;
			}
		}
		else if (nowchar < 10)
		{

			if (time < NORMAL_ATTACK_TIME&&time>1) //表示が上手くいかない
			{
				battle_effect->Draw_e(temp, time > 2 ? -1 : 0); //最初のtimeが1のせいで分かりにくい
			}
			DrawFormatString(20, 0, Colors::white, "%sの攻撃（属性）:%d！", monsters[nowchar - 5]->Status_.name, temp);
		}
	}
	else if (issueflag == 1) //RESULT画面
	{
		DrawResult();
	}
	else if (issueflag == -1) //ゲームオーバー画面
	{
		DrawGameOver();
	}
}


int Battle::Reaction()
{
	DebugPrintf(2);
	

	int r = 0;
	//デバッグ用の戦闘から抜ける処理
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
		if (nowchar < 5)
		{
			switch (state) //主な処理
			{
			case CHOOSE_ACT: //基礎行動選択待ち
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
						case 0: //協力攻撃
							checkstate = 1;
							break;
						case 1: //通常攻撃
							checkstate = 2;
							nowchoosea = 0;
							finishflag = 0;
							while (!finishflag)
							{
								if (monsters[nowchoosea]->Status_c.alive&&numenemy - numdiedchar > 0) //無限ループ対策
								{
									finishflag = TRUE;
								}
								else
								{
									nowchoosea = nowchoosea == numenemy - 1 ? 0 : ++nowchoosea;
								}
							}
							break;
						case 2: //スキル
							checkstate = 3;
							break;
						case 3: //防御
							state = 3;
							break;
						case 4: //アイテム
							checkstate = 4;
							break;
						case 5: //逃げる
							state = 5;
							break;
						default:
							nowchoosef = 1; //保険
							break;
						}
					}
				}
				else if (checkstate == 1) //協力攻撃選択
				{

				}
				else if (checkstate == 2) //通常攻撃対象選択
				{
					if (Key_Input::buff_time[KEY_INPUT_LEFT] == 1)
					{
						//初期目標が死んでいたら右にずらしていく
						do
						{
							nowchoosea = nowchoosea ? --nowchoosea : numenemy - 1;
						} while (!monsters[nowchoosea]->Status_c.alive&&numenemy - numdiedchar > 0);
					}
					else if (Key_Input::buff_time[KEY_INPUT_RIGHT] == 1 && !Key_Input::buff_time[KEY_INPUT_LEFT])
					{
						do
						{
							nowchoosea = nowchoosea == numenemy - 1 ? 0 : ++nowchoosea;
						} while (!monsters[nowchoosea]->Status_c.alive&&numenemy - numdiedchar > 0);
					}
					if (Key_Input::buff_time[KEY_INPUT_X] == 1) //基礎行動選択に戻る
					{
						checkstate = 0;
						nowchoosea = -1;
					}
					else if (Key_Input::buff_time[KEY_INPUT_Z] == 1) //攻撃に移行
					{
						checkstate = 0;
						state = 2;
						temp_nowchoosea = nowchoosea;
						nowchoosea = -1; //点滅を防ぐため
						characters->lastchoosef[party->party_info[nowchar]] = 1; //コマンドを記憶
					}
				}
				break;

			case NORMAL_ATTACK:

				break;

			case GUARD:
				ActGuard();
				break;

			case ESCAPE: //逃げる処理
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
					r = 5; //逃げたことを伝える
					characters->lastchoosef[party->party_info[nowchar]] = ESCAPE; //コマンドを記憶
				}
				else //逃げられない!
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
		else if (nowchar < 10) //敵の行動
		{
			//ここに敵の行動を記述

			if (!time)
			{
				finishflag = 0;
				while (!finishflag)
				{
					temp = randomer->GetRand() % party->GetNumMember();
					temp = temp;
					if (characters->status_c[party->party_info[temp]].alive)
					{
						finishflag = TRUE;
					}
				}
			}

			if (time == NORMAL_ATTACK_TIME / 2)
			{
				characters->status_c[party->party_info[temp]].hp -= monsters[nowchar - 5]->Status_.atk * 3 * (guardflag[temp] ? 0.5 : 1);
			}

			if (time>NORMAL_ATTACK_TIME)
			{

				temp = 0;
				time = 0;
				active_point[nowchar] += 3;
				turn_finish_flag = TRUE;
			}
			else
			{
				time++;
			}
		}


		//行動が次のキャラに移行する
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
	else if (issueflag == 1) //RESULT画面
	{

		if (Key_Input::buff_time[KEY_INPUT_Z] == 1) //戦闘終了
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
				if (characters->status_c[party->party_info[turn_active[i]]].alive) //一応
				{
					//自陣だと分かるように
					DrawBox(
						640 - minichar_size_x - 15,
						360 - (i + 1) * minichar_size_y - 4 * i,
						640,
						360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
						Colors::blue, TRUE);
					//キャラ画像の表示
					DrawExtendGraph(
						640 - minichar_size_x,
						360 - (i + 1) * minichar_size_y - 4 * i,
						640,
						360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
						characters->char_h_i[party->party_info[turn_active[i]]][characters->job[party->party_info[turn_active[i]]]], TRUE);
					//デバッグ的な
					DrawFormatString(640 - minichar_size_x - 15, 360 - (i + 1) * minichar_size_y - 4 * i, Colors::purple, "%d", active_point[turn_active[i]]);
				}
			}
			else //!isplayer
			{
				if (monsters[turn_active[i] - 5]->Status_c.alive)
				{
					//敵陣だと分かるように
					DrawBox(
						640 - minichar_size_x - 15 - (nowchoosea == turn_active[i]-5?10:0), //現在選ばれているなら少し左へ
						360 - (i + 1) * minichar_size_y - 4 * i,
						640,
						360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
						Colors::red, TRUE);
					//キャラ画像の表示
					DrawExtendGraph(
						640 - minichar_size_x - (nowchoosea == turn_active[i] - 5 ? 10 : 0),
						360 - (i + 1) * minichar_size_y - 4 * i,
						640 - (nowchoosea == turn_active[i] - 5 ? 10 : 0),
						360 - (i + 1) * minichar_size_y - 4 * i + minichar_size_y,
						monsters[turn_active[i] - 5]->graph_m, TRUE);
					//デバッグ的な
					DrawFormatString(640 - minichar_size_x - 15, 360 - (i + 1) * minichar_size_y - 4 * i, Colors::purple, "%d", active_point[turn_active[i]]);
				}
			}
		}
	}

	//現在行動中のキャラを示す
	DrawBox(640 - minichar_size_x - 15 - 100, 360 - minichar_size_y, 640 - minichar_size_x - 15 - 5, 360, Colors::blue, TRUE);
	DrawFormatString(640 - minichar_size_x - 15 - 90, 360 - minichar_size_y + 4, Colors::white, "ACTIVE ⇒", TRUE);
	
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
			//既に取得したものはするー
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
				if (temp_min>active_point[i] && active_point[i] >= 0) //必ず0以上
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

	nowchar = turn_active[0]; //行動を次のキャラに入れ替える
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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 144); //透化

		DrawBox(pos_x_lu + 15, pos_y_lu + nowchoosef * 30 + 5, pos_x_rd, pos_y_lu + nowchoosef * 30 + 5 + 21, Colors::yellow, TRUE); //現在選んでるの

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0); //元に戻す
		if (!state&&!checkstate)
		{

			if (unionattackflag)
			{
				DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 5, Colors::white, thickfont_h, "協力攻撃");
			}
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 35, Colors::white, thickfont_h, "攻撃");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 65, Colors::white, thickfont_h, "スキル");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 95, Colors::white, thickfont_h, "防御");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 125, Colors::white, thickfont_h, "アイテム");
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 155, (can_escape_flag?Colors::white:Colors::black), thickfont_h, "逃げる");

			//行動の説明
			DrawFormatString(5, 1, Colors::white, nowchoosef == 0 ? "協力攻撃をします。" :
												  nowchoosef == 1 ? "装備している武器で攻撃します。" :
												  nowchoosef == 2 ? "技や魔法を使用します。" :
												  nowchoosef == 3 ? "敵の攻撃に備えて防御の態勢をとります。" :
												  nowchoosef == 4 ? "所持しているアイテムを使用します。" :
												  nowchoosef == 5 ? "戦闘からの脱出を試みます。" :
																	"エラーです。");
		}

		//通常攻撃選択
		if (checkstate == 2)
		{
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 35, Colors::white, thickfont_h, "攻撃");
			DrawFormatString(5, 1, Colors::white, "攻撃対象を選択してください。");
		}

		//逃げられない
		if (state == 5 && !can_escape_flag)
		{
			DrawStringsCenterToHandle(pos_x_lu + 75, pos_y_lu + 155, Colors::black, thickfont_h, "逃げる");
			DrawFormatString(15, 1, Colors::white, "退路が壁で逃げられない！");
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

	//死んでいるキャラの合計
	numdiedchar = 0;
	for (int i = 0; i < party->GetNumMember(); i++)
	{
		if (active_point[i] == -1)
		{
			numdiedchar++;
		}
	}
	for (int i = 0; i < numenemy; i++)
	{
		if (active_point[i + 5] == -1) //死んでいるキャラの合計
		{
			numdiedchar++;
		}
	}
}


void Battle::TurnFinish()
{
	DebugPrintf(8);


	turn_finish_finish_flag = FALSE;
	//生死の判定
	for (int i = 0; i < numenemy; i++)
	{
		if (monsters[i]->Status_c.hp <= 0 && monsters[i]->Status_c.alive)
		{
			monsters[i]->Status_c.alive = 0;
			active_point[i + 5] = -1;
		}
	}
	for (int i = 0; i < party->GetNumMember(); i++)
	{
		if (characters->status_c[party->party_info[i]].hp <= 0 && characters->status_c[party->party_info[i]].alive)
		{
			characters->status_c[party->party_info[i]].alive = 0;
			active_point[i] = -1;
		}
	}

	//勝敗を判定する
	CheckResult();
	turn_finish_finish_flag = TRUE;
}

void Battle::TurnStart()
{
	DebugPrintf(9);


	if (nowchar < 5) //プレイヤーキャラクターの場合
	{
		nowchoosef = characters->lastchoosef[party->party_info[nowchar]];
		nowchooses = characters->lastchoosef_skill[party->party_info[nowchar]];
	}
	else if (nowchar < 10) //敵キャラクターの場合
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
		DrawFormatString(20, 1, Colors::white, "%sの攻撃（属性）！", characters->name[party->party_info[nowchar]]);

		//1回だけダメージ計算。とりあえず今は1体のみに対応
		if (temp_damage[0] == -1)
		{
			temp_damage[0] = characters->GetStatus(party->party_info[nowchar]).atk * 7 * (guardflag[temp_nowchoosea + 5] ? 0.5 : 1);
		}
		if (time < NORMAL_ATTACK_TIME)
		{
			//ここにエフェクト処理
			battle_effect->Draw(numenemy * 10 + temp_nowchoosea,time ? -1 : 0,temp_damage);
			
		}
		if (time == NORMAL_ATTACK_TIME)
		{
			//ここはダメージ処理。現状のだと1Fずらす必要がある
			monsters[temp_nowchoosea]->Status_c.hp -= temp_damage[0];
		}
		if (time > NORMAL_ATTACK_TIME)
		{
			//行動終了処理
			temp_damage[0] = -1;
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
	else
	{

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
			//行動終了処理
			time = 0;
			state = 0;
			active_point[nowchar] += 2;
			turn_finish_flag = TRUE;
			characters->lastchoosef[party->party_info[nowchar]] = GUARD; //コマンドを記憶
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
		debug_fp = fopen("./log/debug_log_battle.cns", "w");
		fprintf(debug_fp, "%d", number);
		fclose(debug_fp);
		debug_fp = nullptr;
	}
}