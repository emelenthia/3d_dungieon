#pragma once
#include"Battle.h"
#include"Guild.h"
#include"Field.h"//->Dungeon‚Ì‚æ‚Ä‚¢

class Scene //ŠeƒV[ƒ“‚ğ‘JˆÚ
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

