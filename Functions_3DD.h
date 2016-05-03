#pragma once
#include"DxLib.h"
#define GUILD 0
#define FIELD 1
#define BATTLE 2

class Functions_3DD
{
public:
	Functions_3DD();
	~Functions_3DD();
	void DrawSkill(int chara, int mode); //指定されたキャラのスキル一覧を表示します。charaはキャラ番号を指定。modeは使用場面によって選択。上のdefineを参照
};

