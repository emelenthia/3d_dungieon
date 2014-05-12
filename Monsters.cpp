#include "Monsters.h"
#include<string.h>
#include<DxLib.h>

Monsters::Monsters(int n)
{
	monsterlist = MonsterList::GetInstance();
	MonsterSet(n);
}


Monsters::~Monsters()
{

}


void Monsters::Draw()
{
	DrawGraph(0, 0, graph_b, TRUE);
}


void Monsters::MonsterSet(int n)
{
	//��{
	sprintf(monster_file_name_temp, "./scn/monsters/%s", monsterlist->monsterlist[n]);


	//����ǂݍ���
	sprintf(monster_file_name, "%s/info.cns", monster_file_name_temp);
	individuals_fp = fopen(monster_file_name, "r");
	fscanf(individuals_fp, "%s", Status.name);

	//strcpy(monster_file_name, "\0");

	//�摜��ǂݍ���
	sprintf(monster_file_name, "%s/pic_b.png", monster_file_name_temp);
	graph_b = LoadGraph(monster_file_name);
	sprintf(monster_file_name, "%s/pic_m.png", monster_file_name_temp);
	graph_m = LoadGraph(monster_file_name);
}