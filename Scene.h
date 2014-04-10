#pragma once
#include"Battle.h"
#include"Guild.h"
#include"Dungeon.h"

class Scene //ŠeƒV[ƒ“‚ğ‘JˆÚ
{
public:
	Scene();
	~Scene();
	Battle battle;
	Guild guild;
	Dungeon dungeon;
	SceneBase* scene_now;
	void Draw();
	int Reaction();
};

