#pragma once
#include "Field_Base_Data.h"
#include"G_F_O_Exit.h"

class Green_Field :
	public Field_Base_Data
{
public:
	Green_Field();
	~Green_Field();
	void Draw();
	int mapchip_h[5]; //�}�b�v�`�b�v�̃n���h��
	int mapchip_h2[40];
	char map_array[30][30]; //���̃}�b�v�̃}�b�v�`�b�v�̕���
	static const int numstumpobj = 27;
	Objects stoneobj[2];
	Objects stumpobj[numstumpobj];
	G_F_O_Exit exitobj;
	int Reaction();
};

