#pragma once
#include<stdio.h>
#include"Characters.h"
#include"Character_Show_F.h"

class Character_Show //キャラクターのステータスを見る画面
{
public:
	Character_Show_F *character_show_f;
	void Draw();
	int Reaction();

	Character_Show(){ character_show_f = new Character_Show_F; };
	~Character_Show(){ delete character_show_f; };
};
