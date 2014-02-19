#include<stdio.h>

#pragma once
class Menu //メニュー画面クラス
{
public:
	Menu();
	~Menu();
	void Draw();
	int Reaction();
	int boxcolor; //メニューボックスの色
	int boxcolor2; //メニューボックスの色(周り)
	int boxcolor3; //説明ボックスの色
	int textcolor; //文字の色
	int textcolor2; //文字の色(選択中)
	int choosecolor; //選択を示す色
	int choose_now; //今選んでいるメニュー。0番から
	int menu_act_number; //現在処理しているメニューの番号。処理していなければ-1
	char menu_mean[10][20]; //メニューの文字列
	char menu_explanation[10][40]; //各メニューの説明
	FILE *fp;
	int menumax; //メニューの項目の数
	int test;
};

