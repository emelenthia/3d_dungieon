#pragma once
#include<stdio.h>
#include"DxLib.h"
#include"Party.h"

//�퓬�p�G�t�F�N�g��`�悷�邽�߂̃N���X
class BattleEffect
{
public:
	typedef struct point_
	{
		int left; //�����x���W
		int top; //�����y���W
		int right; //�E����x���W
		int bottom; //�E����y���W

	}point; //RECT�\���̓I��

	static BattleEffect* instance;
	static BattleEffect* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new BattleEffect;
		}
		return instance;
	}

	typedef struct effect_
	{
		int effect_h[10][10]; //�e�G�t�F�N�g�̃n���h��(1������
		char effect_f[10][10]; //�e�G�t�F�N�g�̕\���t���[����
		point effect_p[10]; //�e�G�t�F�N�g�̕\���ʒu(1�Z�b�g����
	}effect;

	effect player; //�G�p�̂ƃv���C���[�p��2��p��
	effect enemy;
	void LoadEffect(); //�G�t�F�N�g�̃��[�h
	void LoadEffectFrame(){}; //�G�t�F�N�g�̕\���t���[���̃��[�h
	void LoadEffectPos(){}; //�G�t�F�N�g�̕\���ʒu�̃��[�h
	void DrawEffect(int monster_pos, int number,int* damage); //�I�����ꂽ�G�t�F�N�g�̕`��B�_���[�W���\���Bint*�Ȃ̂͑S�̍U���̂���
	void DrawEffect_e(int target_pos, int number); //�I�����ꂽ�G�t�F�N�g�̕`��B�G�p
	void Draw(int monster_pos, int number,int* damage); //DrawEffect�Ƃ̒����
	void Draw_e(int target_pos, int number); //DrawEffect�Ƃ̒�����B�G�p�Btargetpos�͍��ォ�琔����1����0���瑝���Ă���
	void mainDraw(); //�匳��Draw()
	void DrawIntCenter(int x,int y,int value); //(x,y)�𒆐S�Ƃ���value��\��

	//�G�̂ݎg�p
	Party* party;
	int target_number;
	//���ʂ̕ϐ�
	int time; //DrawEffect�Ŏg�p����鎞�Ԍv���p�̕ϐ�
	int elem; //���݂̃G�t�F�N�g�������ڂ��B0��1���ڂƂ���
	int nownumber; //���ݕ\�����Ă���G�t�F�N�g�̔ԍ�
	int nowtargetpos; //�d���Ȃ��̂ŋL��������悤��
	bool playerflag = 0; //���ݕ\���������G�t�F�N�g���v���C���[�̂��̂��G�̂��̂��̃t���O
	//�����������g�p
	int* nowdamage=nullptr;
	int alltime = 0; //1��anim�̗݌vtime

private:
	BattleEffect();
	~BattleEffect();
	BattleEffect(const BattleEffect& rhs);
	BattleEffect& operator=(const BattleEffect& rhs);
};

