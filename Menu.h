#include<stdio.h>

#pragma once
class Menu //���j���[��ʃN���X
{
public:
	Menu();
	~Menu();
	void Draw();
	int Reaction();
	int boxcolor; //���j���[�{�b�N�X�̐F
	int boxcolor2; //���j���[�{�b�N�X�̐F(����)
	int boxcolor3; //�����{�b�N�X�̐F
	int textcolor; //�����̐F
	int textcolor2; //�����̐F(�I��)
	int choosecolor; //�I���������F
	int choose_now; //���I��ł��郁�j���[�B0�Ԃ���
	int menu_act_number; //���ݏ������Ă��郁�j���[�̔ԍ��B�������Ă��Ȃ����-1
	char menu_mean[10][20]; //���j���[�̕�����
	char menu_explanation[10][40]; //�e���j���[�̐���
	FILE *fp;
	int menumax; //���j���[�̍��ڂ̐�
	int test;
};

