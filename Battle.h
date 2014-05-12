#pragma once
#include "SceneBase.h"
#include"Monsters.h"

class Battle :
	public SceneBase
{
public:
	Battle();
	~Battle();
	void Draw();
	int Reaction();
	int testgraph;
	Monsters* monsters;
};

