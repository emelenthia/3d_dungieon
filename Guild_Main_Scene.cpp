#include "Guild_Main_Scene.h"
#include"Flags.h"

Guild_Main_Scene::Guild_Main_Scene()
{
	guild_scene = &guild_main;
	reaction_number = 0;
}


Guild_Main_Scene::~Guild_Main_Scene()
{
}


void Guild_Main_Scene::Draw()
{
	guild_scene->Draw();
}


int Guild_Main_Scene::Reaction()
{
	reaction_number = guild_scene->Reaction();
	if (guild_scene != &guild_main && reaction_number == 2)
	{
		guild_scene = &guild_main;
		reaction_number = 0;
	}
	if (guild_scene != &guild_warehouse && reaction_number == 201)
	{
		guild_scene = &guild_warehouse;
		reaction_number = 0;
	}

	return reaction_number;
}