#pragma once
#include<stdio.h>
#include"Characters.h"
#include"Status.h"

class Character_Show_F //�L�����N�^�[�̃X�e�[�^�X��������
{
public:

	void Draw();
	int Reaction();
	int black;
	int yellow;
	int white;
	int blue;
	int darkblue;
	int darkyellow;
	int lightblue;
	int green;
	int red;
	int brown;
	FILE* fp;
	int numchar = 0;
	Characters* characters;
	int choosenow = 0;
	char names[20][20]; //�Ή��\�B0=Lv,1=HP,2=TP,3=ATK,4=DEF,5=INT,6=RES,7=DEX,8=AGI,9=EXP,10=NEXT
	//�Â��B11=�a�ϐ�,12=�ˑϐ�,13=���ϐ�,14=�Αϐ�,15=���ϐ�,16=���ϐ�,17=�y�ϐ�,18=���ϐ�
	int namemax;
	void DrawIntRight(int x, int y, int num, int color);
	int number_list[13]; //�e�L�������ォ�牽�Ԗڂɏ�����Ă��邩�̃����B�������Ă��Ȃ��L�����̎����l�����邽�߁B��������-1

	int pos_x_lu = 20;
	int pos_y_lu = 24;
	int pos_x_rd = 120;
	int pos_y_rd = 0;
	Character_Show_F();
	~Character_Show_F(){};
	status Status_; //status�\���̂��󂯎��
	int GetCharNow(); //���ݑI�����Ă���L�����̔ԍ���Ԃ��B�ԍ��Ƃ͌ŗL�ԍ��ł���
};
