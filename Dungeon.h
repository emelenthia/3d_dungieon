#pragma once
#include "SceneBase.h"
#include"DxLib.h"
#include<stdio.h>
#include"SaveData.h"
#include"Options.h"
#include"Party.h"

class Dungeon :
	public SceneBase
{
public:
	Dungeon();
	~Dungeon();
	void Draw();
	int Reaction();
	int DrawSquare(float pos_x_lu, float pos_y_lu, float pos_z_lu, float pos_x_rd, float pos_y_rd, float pos_z_rd); //3d��Ԃɐ��l�p�`�������֐�
	//int kabe_handle;
	int DrawMap(unsigned char(*map_data)[10], int x_max, int z_max); //�}�b�v�̕`��B�[�x�o�b�t�@����
	int DrawMap_c(unsigned char(*map_data)[10], int x_max, int z_max); //�}�b�v�̕`��B�[�x�o�b�t�@���Ȃ�
	void DrawMiniMap(); //�~�j�}�b�v�̕`��
	FILE *fp;
	int kabe_handle;
	int pos_x;
	int pos_z;
	const int block_size = 100;
	int muki = 0; //0=U,1=R,2=D,3=L
	unsigned char map_data[10][10];
	int x_max = 0, z_max = 0;
	VECTOR target_camera;
	VECTOR player_camera;
	int y = 1;
	int state; //��Ԃ�\���ϐ��B1�őO�i���B2�ŉE�]��B3�ŋt�������B4�ō��]��B5�ŉE���s�ړ��B6�ō����s�ړ��B7�ŊX�ɖ߂낤�Ƃ��Ă���
	int time; //��Ԃɂ������Ă��鎞�Ԃ�ێ��B
	void Return_right(); //�E�]��
	int down_help = 0; //���{�^�����̃w���p�[
	int flaging = 0; //�֗��t���b�O
	static int floors; //���݂̊K�w
	int start_z = 0;
	int start_x = 0;
	void LoadDungeon();
	int black;
	int yellow;
	int white;
	int blue;
	int nowchoose = 0;
	int feel_flag;
	char kabe_name[100];
	unsigned char fog_r = 0;
	unsigned char fog_g = 0;
	unsigned char fog_b = 0;
	float fog_start = 0;
	float fog_goal = 0;
	int yajirushi_h;
	SaveData *savedata;
	Options *options;
	Party *party;
};