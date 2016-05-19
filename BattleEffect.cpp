#include "BattleEffect.h"
#include"Colors.h"

BattleEffect* BattleEffect::instance;

BattleEffect::BattleEffect()
{
	nownumber = -1;
	elem = 0;
	time = 0;
	LoadEffect();
	party = Party::GetInstance();

	//テストデータ
	player[0].effect_p.left = 200;
	player[0].effect_p.bottom = 340;
	player[0].effect_p.right = 440;
	player[0].effect_p.top = 100;
	player[1].effect_p.left = 200;
	player[1].effect_p.bottom = 340;
	player[1].effect_p.right = 440;
	player[1].effect_p.top = 100;
	for (int i = 0; i < 9; i++)
	{
		player[0].effect_f[i] = 2;
	}
	player[0].effect_f[9] = -1;
	for (int i = 0; i < 9; i++)
	{
		player[1].effect_f[i] = 2;
	}
	player[1].effect_f[9] = -1;


	enemy[0].effect_p.left = 0;
	enemy[0].effect_p.top = 0;
	enemy[0].effect_p.bottom = party->size_y;
	enemy[0].effect_p.right = party->size_x;
	for (int i = 0; i < 9; i++)
	{
		enemy[0].effect_f[i] = 2;
	}
	enemy[0].effect_f[9] = -1;
}


BattleEffect::~BattleEffect()
{
}


void BattleEffect::LoadEffect()
{
	//effect_h[0][0]=LoadGraph("./pics/戦闘エフェクトアニメ13/640×480/pipo-btleffect084b.png");
	LoadDivGraph("./pics/戦闘エフェクトアニメ13/640×480/pipo-btleffect084b.png", 9, 9, 1, 240, 240, player[0].effect_h);
	LoadDivGraph("./pics/戦闘エフェクトアニメ13/640×480/pipo-btleffect087b.png", 9, 9, 1, 240, 240, player[1].effect_h);
	LoadDivGraph("./pics/戦闘エフェクトアニメ13/640×480/pipo-btleffect084b.png", 9, 9, 1, 240, 240, enemy[0].effect_h);
}


void BattleEffect::DrawEffect(int monsterpos, int number,int* damage)
{
	switch (monsterpos / 10)
	{
	case 0: //全体攻撃
		DrawExtendGraph(player[number].effect_p.left, player[number].effect_p.top, player[number].effect_p.right, player[number].effect_p.bottom,
			player[number].effect_h[elem], TRUE);
		break;
	case 1: //敵が1体のみ
		DrawExtendGraph(player[number].effect_p.left, player[number].effect_p.top, player[number].effect_p.right, player[number].effect_p.bottom,
			player[number].effect_h[elem], TRUE);
		DrawIntCenter(640 / 2, 480 / 2, damage[5]);
		break;
	case 2: //敵が2体いる
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(player[number].effect_p.left - 640 / 4, player[number].effect_p.top, player[number].effect_p.right - 640 / 4, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 4, 480 / 2, damage[5]);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(player[number].effect_p.left + 640 / 4, player[number].effect_p.top, player[number].effect_p.right + 640 / 4, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2 + 640 / 4, 480 / 2, damage[6]);
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(player[number].effect_p.left - 640 / 4, player[number].effect_p.top, player[number].effect_p.right - 640 / 4, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 4, 480 / 2, damage[5]);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(player[number].effect_p.left, player[number].effect_p.top, player[number].effect_p.right, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2, 480 / 2, damage[6]);
			break;
		case 2:
			DrawExtendGraph(player[number].effect_p.left + 640 / 4, player[number].effect_p.top, player[number].effect_p.right + 640 / 4, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2 + 640 / 4, 480 / 2, damage[7]);
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(player[number].effect_p.left - (320 - 640 / 2 / 3), player[number].effect_p.top, player[number].effect_p.right - (320 - 640 / 2 / 3), player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2 - 640 / 3, 480 / 2, damage[5]);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(player[number].effect_p.left - (320 - 640 / 3), player[number].effect_p.top, player[number].effect_p.right - (320 - 640 / 3), player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2 - 640 / 2 / 3, 480 / 2, damage[6]);
			break;
		case 2:
			DrawExtendGraph(player[number].effect_p.left + 640 / 2 / 3, player[number].effect_p.top, player[number].effect_p.right + 640 / 2 / 3, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2 + 640 / 2 / 3, 480 / 2, damage[7]);
			break;
		case 3:
			DrawExtendGraph(player[number].effect_p.left + 640 / 3, player[number].effect_p.top, player[number].effect_p.right + 640 / 3, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2 + 640 / 3, 480 / 2, damage[8]);
			break;
		default:
			break;
		}
		break;
	case 5:
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(player[number].effect_p.left - (320 - 640 / 2 / 3), player[number].effect_p.top, player[number].effect_p.right - (320 - 640 / 2 / 3), player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2 - 640 / 3, 480 / 2, damage[5]);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(player[number].effect_p.left - (320 - 640 / 3), player[number].effect_p.top, player[number].effect_p.right - (320 - 640 / 3), player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2 - 640 / 2 / 3, 480 / 2, damage[6]);
			break;
		case 2:
			DrawExtendGraph(player[number].effect_p.left, player[number].effect_p.top, player[number].effect_p.right, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2, 480 / 2, damage[7]);
			break;
		case 3:
			DrawExtendGraph(player[number].effect_p.left + 640 / 2 / 3, player[number].effect_p.top, player[number].effect_p.right + 640 / 2 / 3, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2+640 / 2 / 3, 480 / 2, damage[8]);
			break;
		case 4:
			DrawExtendGraph(player[number].effect_p.left + 640 / 3, player[number].effect_p.top, player[number].effect_p.right + 640 / 3, player[number].effect_p.bottom,
				player[number].effect_h[elem], TRUE);
			DrawIntCenter(640 / 2+640 / 3, 480 / 2, damage[9]);
			break;
		default:
			break;
		}
	default:
		break;
	}
	time++;
	alltime+=2;
	if (time == player[number].effect_f[elem])
	{
		elem++;
		time = 0;
	}
}


void BattleEffect::Draw(int monsterpos = -1, int number = -1, int* damage=nullptr)
{
	if (nownumber == -1 && number != -1)
	{
		nownumber = number;
		nowtargetpos = monsterpos;
		nowdamage = damage;
		playerflag = TRUE;
	}
	if (nownumber >= 0)
	{
		if (player[nownumber].effect_f[elem] <= 0) //エフェクトの終了
		{
			elem = 0;
			nownumber = -1;
			nowtargetpos = -1;
			nowdamage = nullptr;
		}
	}
}


void BattleEffect::DrawEffect_e(int targetpos, int number)
{
	//味方の位置は上下各5通りなので左上から数えて番号を付けていく。例えば、前列中心は3番
	switch (party->GetNumMember())
	{
	case 0: //全体攻撃
		DrawExtendGraph(player[number].effect_p.left, player[number].effect_p.top, player[number].effect_p.right, player[number].effect_p.bottom,
			player[number].effect_h[elem], TRUE);
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
	point_t.left = enemy[number].effect_p.left + party->pos_x_lu_territory + party->size_x * ((target_number - 1) % 5) / 2 + party->crevice_x / 2;
	point_t.top = enemy[number].effect_p.top + party->pos_y_lu_territory + party->size_y * (target_number > 5) + party->crevice_y / 2;
	point_t.right = enemy[number].effect_p.right + party->pos_x_lu_territory + party->size_x * ((target_number - 1) % 5) / 2 + party->crevice_x / 2;
	point_t.bottom = enemy[number].effect_p.bottom + party->pos_y_lu_territory + party->size_y * (target_number > 5) + party->crevice_y / 2;
	DrawExtendGraph(point_t.left, point_t.top, point_t.right, point_t.bottom, enemy[number].effect_h[elem], TRUE);

	time++;
	if (time == enemy[number].effect_f[elem])
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
		if (enemy[nownumber].effect_f[elem] <= 0) //エフェクトの終了
		{
			elem = 0;
			nownumber = -1;
			nowtargetpos = -1;
			alltime = 0;
		}
	}
}


void BattleEffect::mainDraw()
{
	if (nownumber >= 0)
	{
		if (playerflag)
		{
			DrawEffect(nowtargetpos, nownumber,nowdamage);
		}
		else
		{
			DrawEffect_e(nowtargetpos, nownumber);
		}
	}
}


void BattleEffect::DrawIntCenter(int x, int y, int value)
{
	char tempp[16];
	sprintf(tempp, "%d", value);
	DrawExtendFormatString(x - GetDrawStringWidth(tempp, strlen(tempp)), y - GetFontSize()-alltime, 2.0,2.0,Colors::white, "%d", value);
}