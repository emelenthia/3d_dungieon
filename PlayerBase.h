#pragma once
class PlayerBase
{
public:
	PlayerBase();
	~PlayerBase();
	virtual void Draw() = 0;
	virtual void Reaction() = 0;
};

