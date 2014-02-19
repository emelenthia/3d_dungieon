#pragma once
class Field_Base_Data
{
public:
	Field_Base_Data();
	~Field_Base_Data();
	virtual void Draw() = 0;
	virtual int Reaction() = 0;
	char map_array[10][10];
};