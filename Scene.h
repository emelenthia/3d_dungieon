#pragma once
#include"Battle.h"
#include"Guild.h"
#include"Dungeon.h"

class Scene //各シーンを遷移
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

