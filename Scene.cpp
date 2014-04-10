#include "Scene.h"
#include"Flags.h"

Scene::Scene()
{
	scene_now = &guild;
	Flags::nowscene = 0x8011d;
}


Scene::~Scene()
{
}


void Scene::Draw()
{
	scene_now->Draw();
}


int Scene::Reaction()
{
	scene_now->Reaction();
	

	if (Flags::nowscene == 0xba771e && scene_now != &battle) //戦闘シーンに移行する信号を受け取ったら
	{
		scene_now = &battle; //戦闘シーンに移行する
	}
	if (Flags::nowscene == 0xf1e1d && scene_now != &dungeon) //ダンジョンに移行する信号を受け取ったら
	{
		scene_now = &dungeon; //ダンジョンに移行する
		dungeon.LoadDungeon();
	}
	if (Flags::nowscene == 0x8011d && scene_now != &guild) //ギルドに移行する信号を受け取ったら
	{
		scene_now = &guild; //ダンジョンに移行する
	}

	return 0;
}