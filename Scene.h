#pragma once
#include"Battle.h"
#include"Guild.h"
#include"Dungeon.h"

class Scene //�e�V�[����J��
{
public:
	Scene();
	~Scene();
	Guild guild;
	Dungeon dungeon;
	SceneBase* scene_now;
	void Draw();
	int Reaction();
};

