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
	

	if (Flags::nowscene == 0xba771e && scene_now != &battle) //�퓬�V�[���Ɉڍs����M�����󂯎������
	{
		scene_now = &battle; //�퓬�V�[���Ɉڍs����
	}
	if (Flags::nowscene == 0xf1e1d && scene_now != &dungeon) //�_���W�����Ɉڍs����M�����󂯎������
	{
		//�_���W�����ɓ������ۂ̏�����
		if (scene_now == &guild)
		{
			dungeon.LoadDungeon();
		}
		scene_now = &dungeon; //�_���W�����Ɉڍs����
	}
	if (Flags::nowscene == 0x8011d && scene_now != &guild) //�M���h�Ɉڍs����M�����󂯎������
	{
		scene_now = &guild; //�M���h�Ɉڍs����
	}

	return 0;
}