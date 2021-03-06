#include "Monsters.h"
#include<string.h>
#include<DxLib.h>
#include"Colors.h"
#include<math.h>

#define nfscanf(scan_target, format_text, ...) nfscanf_(__LINE__,__FILE__,scan_target, format_text,__VA_ARGS__);
void Monsters::nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...)
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

Monsters::Monsters(int n)
{
	//初期化
	monster_information_flag = 2;
	monsterlist = MonsterList::GetInstance();
	MonsterSet(n);
	m_ailment = Ailment::GetInstance();
	m_party = Party::GetInstance();
	m_randomer = Randomer::GetInstance();
	for (int i = 0; i < Defines::AILMENT_MAX; i++)
	{
		m_ailment_turns[i] = 0;
		m_ailment_level[i] = 0; 
		m_ailment_target[i] = 0;
	}
	//ヘイト初期化
	int hate_count = 0;
	while (hate_count < m_party->GetNumMember())
	{
		m_hate[hate_count] = 100;
		//ここに装備の影響とかを書く

		hate_count++;
	}
	//居ないところは-1で埋める
	while (hate_count < Defines::PT_MAX)
	{
		m_hate[hate_count] = -1;
		hate_count++;
	}

}


Monsters::~Monsters()
{

}


void Monsters::Draw(int pos_x,int pos_y,int size_x,int size_y,bool brightflag)
{

	if (Status_c.alive) //死んでいると表示しない
	{
		if (brightflag)
		{
			brighttime = 191 + 64 * (sin(timeflo += 0.1) < 0 ? -sin(timeflo) : sin(timeflo));
			SetDrawBright(brighttime, brighttime, brighttime);
			DrawExtendGraph(pos_x, pos_y, pos_x + size_x, pos_y + size_y, graph_b, TRUE);
			SetDrawBright(255, 255, 255);
		}
		else
		{
			DrawExtendGraph(pos_x, pos_y, pos_x + size_x, pos_y + size_y, graph_b, TRUE);
			brightflag = 0;
		}

		if (monster_information_flag)
		{
			int posx_t = pos_x + GetDrawFormatStringWidth(Status_.name) / 2;
			DrawFormatString(posx_t, pos_y - 20, Colors::white, Status_.name);
			if (monster_information_flag == 2)
			{
				DrawFormatString(posx_t, pos_y - 40, Colors::white, "HP :%d", Status_c.hp);
				DrawFormatString(posx_t, pos_y - 60, Colors::white, "Lv :%d", Status_.lv);
			}
			//名前の下に状態異常を表示する
			for (int i = 0, count = 0; i < Defines::AILMENT_MAX; i++)
			{
				if (m_ailment_turns[i] > 0) //状態異常にかかっていれば
				{
					DrawFormatString(posx_t - GetDrawFormatStringWidth("%s", m_ailment->m_ailment[i].name) / 2 + 50, pos_y + count * 20,
						(m_ailment->m_ailment[i].de_buff == 1 ? Colors::red : Colors::aqua) //バフとデバフで色を分ける
						, "%s", m_ailment->m_ailment[i].name);
					count++;
				}
			}
		}
	}
}


void Monsters::MonsterSet(int n)
{
	int numitemmax = 0;
	//基本
	sprintf(monster_file_name_temp, "./scn/monsters/%s", monsterlist->monsterlist[n]);
	Status_c.alive = 1;

	//情報を読み込む
	sprintf(monster_file_name, "%s/info.cns", monster_file_name_temp);
	individuals_fp = fopen(monster_file_name, "r");
	nfscanf(individuals_fp, "%s", Status_.name);
	nfscanf(individuals_fp, "%d", &Status_.lv);
	nfscanf(individuals_fp, "%d", &Status_.hpmax);
	nfscanf(individuals_fp, "%d", &Status_.tpmax);
	nfscanf(individuals_fp, "%d", &Status_.atk);
	nfscanf(individuals_fp, "%d", &Status_.def);
	nfscanf(individuals_fp, "%d", &Status_.int_s);
	nfscanf(individuals_fp, "%d", &Status_.res);
	nfscanf(individuals_fp, "%d", &Status_.dex);
	nfscanf(individuals_fp, "%d", &Status_.agi);
	nfscanf(individuals_fp, "%d", &Status_.Tolerance.cut);
	nfscanf(individuals_fp, "%d", &Status_.Tolerance.stab);
	nfscanf(individuals_fp, "%d", &Status_.Tolerance.beat);
	nfscanf(individuals_fp, "%d", &Status_.Tolerance.fire);
	nfscanf(individuals_fp, "%d", &Status_.Tolerance.aqua);
	nfscanf(individuals_fp, "%d", &Status_.Tolerance.earth);
	nfscanf(individuals_fp, "%d", &Status_.Tolerance.wind);
	nfscanf(individuals_fp, "%d", &Status_.Tolerance.light);
	nfscanf(individuals_fp, "%d", &Status_.exp);
	nfscanf(individuals_fp, "%d", &numitemmax);
	for (int i = 0; i < numitemmax; i++)
	{
		nfscanf(individuals_fp, "%d", &Status_.item[i]);
	}
	for (int i = 0; i < numitemmax; i++)
	{
		nfscanf(individuals_fp, "%d", &Status_.item_p[i]);
	}
	nfscanf(individuals_fp, "%d", &Status_.item_pa);
	nfscanf(individuals_fp, "%d", &Strain);
	fclose(individuals_fp);

	//画像を読み込む
	sprintf(monster_file_name, "%s/pic_b.png", monster_file_name_temp);
	graph_b = LoadGraph(monster_file_name);
	sprintf(monster_file_name, "%s/pic_m.png", monster_file_name_temp);
	graph_m = LoadGraph(monster_file_name);

	//代入
	Status_c.hp = Status_.hpmax;
	Status_c.tp = Status_.tpmax;
}


int Monsters::TargetSet()
{
	int target = 0, hate_sum = 0, hate_ran = 0;
	//前提として、死んだりして居ない所のヘイトは-1になっている
	for (int i = 0; i < Defines::PT_MAX; i++) //ここはパーティーメンバーの数だけ回すのが速いか?でも場所によって居ない可能性を考えると…
	{
		if (m_hate[i] > 0)
		{
			hate_sum += m_hate[i]; //まず合計を求めて
		}
	}
	hate_ran = (m_randomer->GetRand()) % hate_sum; //合計未満の数値を求め
	hate_sum = 0;
	for (int i = 0; i < Defines::PT_MAX; i++)
	{
		if (m_hate[i] > 0) //ほんとは等号も付いているべきだけど、まあ意味ないし等号は付けない
		{
			//キャラ毎のヘイトを足していき、乱数が合計より小さくなった時点のキャラを攻撃する
			hate_sum += m_hate[i];
			if (hate_ran < hate_sum) //ここに等号がついてると、原理的には1体目のヘイトが0でも攻撃してしまう可能性があるから
			{
				//攻撃対象を設定
				target = i;
				break; //攻撃対象を設定したら抜けなきゃいけなかった
			}
		}
	}

	return target;
}
