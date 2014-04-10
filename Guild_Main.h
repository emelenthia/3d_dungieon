#pragma once
#include "Guild_Scene_Base.h"
#include<stdio.h>
#include"SaveData.h"
#include"Options.h"
#include"Character_Show.h"
#include"Guild_PT.h"

class Guild_Main :
	public Guild_Scene_Base
{
public:
	Guild_Main();
	~Guild_Main();
	int Reaction();
	SaveData *savedata;
	Options *options;
	Character_Show *character_show;
	void Draw();
	Guild_PT *guild_pt;
};

