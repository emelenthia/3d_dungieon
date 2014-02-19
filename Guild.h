#pragma once
#include "SceneBase.h"
#include<stdio.h>
#include"Guild_Main_Scene.h"
#include"Guild_Scene_Base.h"
#include"Guild_Entrance.h"

class Guild : //ギルド画面のクラス
	public SceneBase
{
public:
	Guild();
	~Guild();
	void Draw();
	int Reaction();
	Guild_Main_Scene guild_main_scene; //1番目
	Guild_Entrance guild_entrance; //0番目
	Guild_Scene_Base *guild_scene; //state
	int reaction_number;
	int x_r; //右のx座標
	int y_d; //下のy座標
};
