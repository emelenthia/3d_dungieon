#pragma once
#include<stdio.h>
#include"Characters.h"

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

	Character_Show_F();
	~Character_Show_F(){};
};
