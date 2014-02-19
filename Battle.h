#pragma once
#include "SceneBase.h"
class Battle :
	public SceneBase
{
public:
	Battle();
	~Battle();
	void Draw();
	int Reaction();
	int testgraph;
};

