#pragma once
#include "Guild_Scene_Base.h"
#include<stdio.h>

class Guild_Entrance : //ギルドやお店との橋渡し的クラス
	public Guild_Scene_Base
{
public:
	Guild_Entrance();
	~Guild_Entrance();
	int Reaction();
};

