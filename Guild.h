#pragma once
#include "SceneBase.h"
#include<stdio.h>
#include"Guild_Main_Scene.h"
#include"Guild_Scene_Base.h"
#include"Guild_Entrance.h"

class Guild : //�M���h��ʂ̃N���X
	public SceneBase
{
public:
	Guild();
	~Guild();
	void Draw();
	int Reaction();
	Guild_Main_Scene guild_main_scene; //1�Ԗ�
	Guild_Entrance guild_entrance; //0�Ԗ�
	Guild_Scene_Base *guild_scene; //state
	int reaction_number;
	int x_r; //�E��x���W
	int y_d; //����y���W
};
