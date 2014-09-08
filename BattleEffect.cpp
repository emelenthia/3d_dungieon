#include "BattleEffect.h"

BattleEffect* BattleEffect::instance;

BattleEffect::BattleEffect()
{
	nownumber = -1;
	elem = 0;
	time = 0;
	LoadEffect();
	party = Party::GetInstance();

	//テストデータ
	player.effect_p[0].left = 200;
	player.effect_p[0].bottom = 340;
	player.effect_p[0].right=440;
	player.effect_p[0].top = 100;
	for (int i = 0; i < 9; i++)
	{
		player.effect_f[0][i] = 2;
	}
	player.effect_f[0][9] = -1;


	enemy.effect_p[0].left = 0;
	enemy.effect_p[0].top = 0;
	enemy.effect_p[0].bottom = party->size_y;
	enemy.effect_p[0].right = party->size_x;
	for (int i = 0; i < 9; i++)
	{
		enemy.effect_f[0][i] = 2;
	}
	enemy.effect_f[0][9] = -1;
}


BattleEffect::~BattleEffect()
{
}


void BattleEffect::LoadEffect()
{
	//effect_h[0][0]=LoadGraph("./pics/戦闘エフェクトアニメ13/640×480/pipo-btleffect084b.png");
	LoadDivGraph("./pics/戦闘エフェクトアニメ13/640×480/pipo-btleffect084b.png", 9, 9, 1, 240, 240, player.effect_h[0]);
	LoadDivGraph("./pics/戦闘エフェクトアニメ13/640×480/pipo-btleffect084b.png", 9, 9, 1, 240, 240, enemy.effect_h[0]);
}


void BattleEffect::DrawEffect(int monsterpos, int number)
{
	switch (monsterpos / 10)
	{
	case 0: //全体攻撃
		DrawExtendGraph(player.effect_p[number].left, player.effect_p[number].top, player.effect_p[number].right, player.effect_p[number].bottom,
			player.effect_h[number][elem], TRUE);
		break;
	case 1: //敵が1体のみ
		DrawExtendGraph(player.effect_p[number].left, player.effect_p[number].top, player.effect_p[number].right, player.effect_p[number].bottom,
			player.effect_h[number][elem], TRUE);
		break;
	case 2: //敵が2体いる
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(player.effect_p[number].left - 640 / 4, player.effect_p[number].top, player.effect_p[number].right - 640 / 4, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(player.effect_p[number].left + 640 / 4, player.effect_p[number].top, player.effect_p[number].right + 640 / 4, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(player.effect_p[number].left - 640 / 4, player.effect_p[number].top, player.effect_p[number].right - 640 / 4, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(player.effect_p[number].left, player.effect_p[number].top, player.effect_p[number].right, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 2:
			DrawExtendGraph(player.effect_p[number].left + 640 / 4, player.effect_p[number].top, player.effect_p[number].right + 640 / 4, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(player.effect_p[number].left - (320 - 640 / 2 / 3), player.effect_p[number].top, player.effect_p[number].right - (320 - 640 / 2 / 3), player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(player.effect_p[number].left - (320 - 640 / 3), player.effect_p[number].top, player.effect_p[number].right - (320 - 640 / 3), player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 2:
			DrawExtendGraph(player.effect_p[number].left + 640 / 2 / 3, player.effect_p[number].top, player.effect_p[number].right + 640 / 2 / 3, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 3:
			DrawExtendGraph(player.effect_p[number].left + 640 / 3, player.effect_p[number].top, player.effect_p[number].right + 640 / 3, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		default:
			break;
		}
		break;
	case 5:
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(player.effect_p[number].left - (320 - 640 / 2 / 3), player.effect_p[number].top, player.effect_p[number].right - (320 - 640 / 2 / 3), player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(player.effect_p[number].left - (320 - 640 / 3), player.effect_p[number].top, player.effect_p[number].right - (320 - 640 / 3), player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 2:
			DrawExtendGraph(player.effect_p[number].left, player.effect_p[number].top, player.effect_p[number].right, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 3:
			DrawExtendGraph(player.effect_p[number].left + 640 / 2 / 3, player.effect_p[number].top, player.effect_p[number].right + 640 / 2 / 3, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		case 4:
			DrawExtendGraph(player.effect_p[number].left + 640 / 3, player.effect_p[number].top, player.effect_p[number].right + 640 / 3, player.effect_p[number].bottom,
				player.effect_h[number][elem], TRUE);
			break;
		default:
			break;
		}
	default:
		break;
	}
	time++;
	if (time == player.effect_f[number][elem])
	{
		elem++;
		time = 0;
	}
}


void BattleEffect::Draw(int monsterpos=-1,int number = -1)
{
	if (nownumber == -1 && number != -1)
	{
		nownumber = number;
		nowtargetpos = monsterpos;
		playerflag = TRUE;
	}
	if (nownumber >= 0)
	{
		if (player.effect_f[nownumber][elem] <= 0) //エフェクトの終了
		{
			elem = 0;
			nownumber = -1;
			nowtargetpos = -1;
		}
	}
}


void BattleEffect::DrawEffect_e(int targetpos, int number)
{
	//味方の位置は上下各5通りなので左上から数えて番号を付けていく。例えば、前列中心は3番
	switch (party->GetNumMember())
	{
	case 0: //全体攻撃
		DrawExtendGraph(player.effect_p[number].left, player.effect_p[number].top, player.effect_p[number].right, player.effect_p[number].bottom,
			player.effect_h[number][elem], TRUE);
		break;
	case 1: //味方が1体のみ
		target_number = 3;
		break;
	case 2: //味方が2体いる
		switch (party->party_type)
		{
		case 21: //Party.h参照
			switch (targetpos)
			{
			case 0:
				target_number = 2;
				break;
			case 1:
				target_number = 4;
				break;
			}
			break;
		case 22:
			switch (targetpos)
			{
			case 0:
				target_number = 3;
				break;
			case 1:
				target_number = 8;
				break;
			}
			break;
		}
		break;
	case 3:
		switch (party->party_type)
		{
		case 31:
			switch (targetpos)
			{
			case 0:
				target_number = 1;
				break;
			case 1:
				target_number = 3;
				break;
			case 2:
				target_number = 5;
				break;
			}
			break;
		case 32:
			switch (targetpos)
			{
			case 0:
				target_number = 2;
				break;
			case 1:
				target_number = 4;
				break;
			case 2:
				target_number = 8;
				break;
			}
			break;
		case 33:
			switch (targetpos)
			{
			case 0:
				target_number = 3;
				break;
			case 1:
				target_number = 7;
				break;
			case 2:
				target_number = 9;
				break;
			}
			break;
		}
		break;
	case 4:
		switch (party->party_type)
		{
		case 41:
			switch (targetpos)
			{
			case 0:
				target_number = 1;
				break;
			case 1:
				target_number = 3;
				break;
			case 2:
				target_number = 5;
				break;
			case 3:
				target_number = 8;
				break;
			}
			break;
		case 42:
			switch (targetpos)
			{
			case 0:
				target_number = 2;
				break;
			case 1:
				target_number = 4;
				break;
			case 2:
				target_number = 7;
				break;
			case 3:
				target_number = 9;
				break;
			}
			break;
		case 43:
			switch (targetpos)
			{
			case 0:
				target_number = 3;
				break;
			case 1:
				target_number = 6;
				break;
			case 2:
				target_number = 8;
				break;
			case 3:
				target_number = 10;
				break;
			}
			break;
		}
		break;
	case 5:
		switch (party->party_type)
		{
		case 51:
			switch (targetpos)
			{
			case 0:
				target_number = 1;
				break;
			case 1:
				target_number = 3;
				break;
			case 2:
				target_number = 5;
				break;
			case 3:
				target_number = 7;
				break;
			case 4:
				target_number = 9;
				break;
			}
			break;
		case 52:
			switch (targetpos)
			{
			case 0:
				target_number = 2;
				break;
			case 1:
				target_number = 4;
				break;
			case 2:
				target_number = 6;
				break;
			case 3:
				target_number = 8;
				break;
			case 4:
				target_number = 10;
				break;
			}
			break;
		}
	}

	//対象の左上を0,0としてエフェクト位置に依存して描画
	point point_t;
	point_t.left = enemy.effect_p[number].left + party->pos_x_lu_territory + party->size_x * ((target_number - 1) % 5) * 0.5 + 0.5 * party->crevice_x;
	point_t.top = enemy.effect_p[number].top + party->pos_y_lu_territory + party->size_y * (target_number > 5) + 0.5 * party->crevice_y;
	point_t.right = enemy.effect_p[number].right + party->pos_x_lu_territory + party->size_x * ((target_number - 1) % 5) * 0.5 + 0.5 * party->crevice_x;
	point_t.bottom = enemy.effect_p[number].bottom + party->pos_y_lu_territory + party->size_y * (target_number > 5) + 0.5 * party->crevice_y;
	DrawExtendGraph(point_t.left, point_t.top, point_t.right, point_t.bottom, enemy.effect_h[number][elem], TRUE);

	time++;
	if (time == enemy.effect_f[number][elem])
	{
		elem++;
		time = 0;
	}
}


void BattleEffect::Draw_e(int targetpos = -1, int number = -1)
{
	if (nownumber == -1 && number != -1)
	{
		nownumber = number;
		nowtargetpos = targetpos;
		playerflag = FALSE;
	}
	if (nownumber >= 0)
	{
		if (enemy.effect_f[nownumber][elem] <= 0) //エフェクトの終了
		{
			elem = 0;
			nownumber = -1;
			nowtargetpos = -1;
		}
	}
}


void BattleEffect::mainDraw()
{
	if (nownumber >= 0)
	{
		if (playerflag)
		{
			DrawEffect(nowtargetpos, nownumber);
		}
		else
		{
			DrawEffect_e(nowtargetpos, nownumber);
		}
	}
}