#pragma once
#include"Battle.h"
#include"Guild.h"
#include"Field.h"//->Dungeon�̂�Ă�

class Scene //�e�V�[����J��
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

