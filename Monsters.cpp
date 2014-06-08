#include "Monsters.h"
#include<string.h>
#include<DxLib.h>
#include"Colors.h"

Monsters::Monsters(int n)
{
	monster_information_flag = 0;
	monsterlist = MonsterList::GetInstance();
	MonsterSet(n);
}


Monsters::~Monsters()
{

}


void Monsters::Draw(int pos_x,int pos_y,int size_x,int size_y)
{
	DrawExtendGraph(pos_x, pos_y, pos_x + size_x, pos_y + size_y, graph_b, TRUE);

	if (monster_information_flag)
	{
		DrawFormatString(pos_x, pos_y - 20, Colors::black, Status_.name);
	}
}


void Monsters::MonsterSet(int n)
{
	int numitemmax = 0;
	//äÓñ{
	sprintf(monster_file_name_temp, "./scn/monsters/%s", monsterlist->monsterlist[n]);
	Status_c.alive = 1;

	//èÓïÒÇì«Ç›çûÇﬁ
	sprintf(monster_file_name, "%s/info.cns", monster_file_name_temp);
	individuals_fp = fopen(monster_file_name, "r");
	fscanf(individuals_fp, "%s", Status_.name);
	fscanf(individuals_fp, "%d", &Status_.hpmax);
	fscanf(individuals_fp, "%d", &Status_.tpmax);
	fscanf(individuals_fp, "%d", &Status_.atk);
	fscanf(individuals_fp, "%d", &Status_.def);
	fscanf(individuals_fp, "%d", &Status_.int_s);
	fscanf(individuals_fp, "%d", &Status_.res);
	fscanf(individuals_fp, "%d", &Status_.dex);
	fscanf(individuals_fp, "%d", &Status_.agi);
	fscanf(individuals_fp, "%d", &Status_.Tolerance.cut);
	fscanf(individuals_fp, "%d", &Status_.Tolerance.stab);
	fscanf(individuals_fp, "%d", &Status_.Tolerance.beat);
	fscanf(individuals_fp, "%d", &Status_.Tolerance.fire);
	fscanf(individuals_fp, "%d", &Status_.Tolerance.aqua);
	fscanf(individuals_fp, "%d", &Status_.Tolerance.earth);
	fscanf(individuals_fp, "%d", &Status_.Tolerance.wind);
	fscanf(individuals_fp, "%d", &Status_.Tolerance.light);
	fscanf(individuals_fp, "%d", &Status_.exp);
	fscanf(individuals_fp, "%d", &numitemmax);
	for (int i = 0; i < numitemmax; i++)
	{
		fscanf(individuals_fp, "%d", &Status_.item[i]);
	}
	for (int i = 0; i < numitemmax; i++)
	{
		fscanf(individuals_fp, "%d", &Status_.item_p[i]);
	}
	fscanf(individuals_fp, "%d", &Status_.item_pa);
	fscanf(individuals_fp, "%d", &Strain);
	fclose(individuals_fp);

	//âÊëúÇì«Ç›çûÇﬁ
	sprintf(monster_file_name, "%s/pic_b.png", monster_file_name_temp);
	graph_b = LoadGraph(monster_file_name);
	sprintf(monster_file_name, "%s/pic_m.png", monster_file_name_temp);
	graph_m = LoadGraph(monster_file_name);
}