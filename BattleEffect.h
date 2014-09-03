#pragma once
#include<stdio.h>
#include"DxLib.h"

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

	int effect_h[10][10]; //�e�G�t�F�N�g�̃n���h��(1������
	char effect_f[10][10]; //�e�G�t�F�N�g�̕\���t���[����
	point effect_p[10]; //�e�G�t�F�N�g�̕\���ʒu(1�Z�b�g����
	void LoadEffect(); //�G�t�F�N�g�̃��[�h
	void LoadEffectFrame(){}; //�G�t�F�N�g�̕\���t���[���̃��[�h
	void LoadEffectPos(){}; //�G�t�F�N�g�̕\���ʒu�̃��[�h
	void DrawEffect(int monster_pos, int number); //�I�����ꂽ�G�t�F�N�g�̕`��
	int time; //DrawEffect�Ŏg�p����鎞�Ԍv���p�̕ϐ�
	int elem; //���݂̃G�t�F�N�g�������ڂ��B0��1���ڂƂ���
	void Draw(int monster_pos,int number); //DrawEffect�Ƃ̒����
	int nownumber; //���ݕ\�����Ă���G�t�F�N�g�̔ԍ�

private:
	BattleEffect();
	~BattleEffect();
	BattleEffect(const BattleEffect& rhs);
	BattleEffect& operator=(const BattleEffect& rhs);
};

