#pragma once
#include<stdio.h>
#include"Characters.h"

class Character_Show_F //キャラクターのステータスを見る画面
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
	char names[20][20]; //対応表。0=Lv,1=HP,2=TP,3=ATK,4=DEF,5=INT,6=RES,7=DEX,8=AGI,9=EXP,10=NEXT
	//つづき。11=斬耐性,12=突耐性,13=欧耐性,14=火耐性,15=水耐性,16=風耐性,17=土耐性,18=雷耐性
	int namemax;
	void DrawIntRight(int x, int y, int num, int color);

	Character_Show_F();
	~Character_Show_F(){};
};
