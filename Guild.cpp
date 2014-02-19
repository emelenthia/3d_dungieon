#include "Guild.h"
#include"DxLib.h"
#include"Flags.h"
#include"Key_Input.h"

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
}


int Guild::Reaction()
{
	reaction_number = guild_scene->Reaction();
	if (guild_scene != &guild_main_scene && reaction_number == 2)
	{
		guild_scene = &guild_main_scene;
		Flags::guild_now = 2;
	}
	if (guild_scene != &guild_entrance && (reaction_number == 1 || reaction_number == 215))
	{
		guild_scene = &guild_entrance;
		Flags::guild_now = 1;
	}
	return 0;
}