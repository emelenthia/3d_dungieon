#pragma once
#include "Field_Base_Data.h"
#include"Objects.h"

class Ice_Field :
	public Field_Base_Data
{
public:
	Ice_Field();
	~Ice_Field();
	void Draw();
	int mapchip_h[5]; //�}�b�v�`�b�v�̃n���h��
	int mapchip_h2[40];
	char map_array[30][30]; //���̃}�b�v�̃}�b�v�`�b�v�̕���
	Objects stoneobj[2];
	int Reaction();
};

