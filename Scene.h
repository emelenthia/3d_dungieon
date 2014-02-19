#pragma once
#include"Battle.h"
#include"Guild.h"
#include"Field.h"//->Dungeonのよてい

class Scene //各シーンを遷移
{
public:
	Scene();
	~Scene();
	Battle battle;
	Guild guild;
	Field field;
	SceneBase* scene_now;
	void Draw();
	int Reaction();
};

