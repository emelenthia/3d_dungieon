#include "BattleEffect.h"

BattleEffect* BattleEffect::instance;

BattleEffect::BattleEffect()
{
	nownumber = -1;
	elem = 0;
	time = 0;
	LoadEffect();

	//テストデータ
	effect_p[0].left = 200;
	effect_p[0].bottom = 340;
	effect_p[0].right=440;
	effect_p[0].top = 100;
	for (int i = 0; i < 9; i++)
	{
		effect_f[0][i] = 2;
	}
	effect_f[0][9] = -1;
}


BattleEffect::~BattleEffect()
{
}


void BattleEffect::LoadEffect()
{
	//effect_h[0][0]=LoadGraph("./pics/戦闘エフェクトアニメ13/640×480/pipo-btleffect084b.png");
	LoadDivGraph("./pics/戦闘エフェクトアニメ13/640×480/pipo-btleffect084b.png", 9, 9, 1, 240, 240, effect_h[0]);
}


void BattleEffect::DrawEffect(int monsterpos, int number)
{
	switch (monsterpos / 10)
	{
	case 0: //全体攻撃
		DrawExtendGraph(effect_p[number].left, effect_p[number].top, effect_p[number].right, effect_p[number].bottom,
			effect_h[number][elem], TRUE);
		break;
	case 1: //敵が1体のみ
		DrawExtendGraph(effect_p[number].left, effect_p[number].top, effect_p[number].right, effect_p[number].bottom,
			effect_h[number][elem], TRUE);
		break;
	case 2: //敵が2体いる
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(effect_p[number].left - 640 / 4, effect_p[number].top, effect_p[number].right - 640 / 4, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(effect_p[number].left + 640 / 4, effect_p[number].top, effect_p[number].right + 640 / 4, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		default:
			break;
		}
		break;
	case 3:
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(effect_p[number].left - 640 / 4, effect_p[number].top, effect_p[number].right - 640 / 4, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(effect_p[number].left, effect_p[number].top, effect_p[number].right, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 2:
			DrawExtendGraph(effect_p[number].left + 640 / 4, effect_p[number].top, effect_p[number].right + 640 / 4, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		default:
			break;
		}
		break;
	case 4:
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(effect_p[number].left - (320 - 640 / 2 / 3), effect_p[number].top, effect_p[number].right - (320 - 640 / 2 / 3), effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(effect_p[number].left - (320 - 640 / 3), effect_p[number].top, effect_p[number].right - (320 - 640 / 3), effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 2:
			DrawExtendGraph(effect_p[number].left + 640 / 2 / 3, effect_p[number].top, effect_p[number].right + 640 / 2 / 3, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 3:
			DrawExtendGraph(effect_p[number].left + 640 / 3, effect_p[number].top, effect_p[number].right + 640 / 3, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		default:
			break;
		}
		break;
	case 5:
		switch (monsterpos - 10 * (monsterpos / 10))
		{
		case 0: //左から数えて1体目
			DrawExtendGraph(effect_p[number].left - (320 - 640 / 2 / 3), effect_p[number].top, effect_p[number].right - (320 - 640 / 2 / 3), effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 1: //左から数えて2体目
			DrawExtendGraph(effect_p[number].left - (320 - 640 / 3), effect_p[number].top, effect_p[number].right - (320 - 640 / 3), effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 2:
			DrawExtendGraph(effect_p[number].left, effect_p[number].top, effect_p[number].right, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 3:
			DrawExtendGraph(effect_p[number].left + 640 / 2 / 3, effect_p[number].top, effect_p[number].right + 640 / 2 / 3, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		case 4:
			DrawExtendGraph(effect_p[number].left + 640 / 3, effect_p[number].top, effect_p[number].right + 640 / 3, effect_p[number].bottom,
				effect_h[number][elem], TRUE);
			break;
		default:
			break;
		}
	default:
		break;
	}
	time++;
	if (time == effect_f[number][elem])
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
	}
	if (nownumber >= 0)
	{
		DrawEffect(monsterpos, nownumber);
		if (effect_f[nownumber][elem] <= 0) //エフェクトの終了
		{
			elem = 0;
			nownumber = -1;
		}
	}
}