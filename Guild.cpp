#include "Guild.h"
#include"DxLib.h"
#include"Flags.h"
#include"Key_Input.h"
#include"Dungeon.h"

Guild::Guild()
{
	guild_scene = &guild_entrance;
	reaction_number = 0;
}


Guild::~Guild()
{
}


void Guild::Draw()
{
	guild_scene->Draw();
	DrawFormatString(0, 200, GetColor(255, 0, 0), "%x", Flags::nowscene);
}


int Guild::Reaction()
{
	reaction_number = guild_scene->Reaction();

	if (guild_scene == &guild_entrance && reaction_number == 2)
	{
		guild_scene = &guild_main_scene;
		Flags::guild_now = 2;
	}
	if (guild_scene == &guild_entrance && reaction_number == 8)
	{
		guild_scene = &guild_dungeon;
		Flags::guild_now = -1;
	}

	else if (guild_scene == &guild_dungeon && reaction_number) //ƒGƒ‹ƒ[‚ç‚È‚¢‚Æ‚·‚®‚Éˆ—‚³‚ê‚Ä‚µ‚Ü‚¤
	{
		if (reaction_number == 1)
		{
			guild_scene = &guild_entrance;
			Flags::guild_now = 1;
		}
		else
		{
			Flags::nowscene = 0xf1e1d;
			Dungeon::floors = reaction_number - 1;
		}

	}
	if (guild_scene == &guild_main_scene && (reaction_number == 1 || reaction_number == 215))
	{
		guild_scene = &guild_entrance;
		Flags::guild_now = 1;
	}
	return 0;
}