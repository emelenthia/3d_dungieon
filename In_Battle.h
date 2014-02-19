#pragma once
#include "Talker.h"
class In_Battle : //戦闘に入る可能性を秘めたオブジェクト
	public Talker
{
public:
	In_Battle();
	~In_Battle();
	int Reaction(); //オーバーライド
};

