#pragma once
#include "SceneBase.h"
#include"Monsters.h"
#include"Party.h"
#include"Characters.h"
#include<random>
#include"Randomer.h"

class Battle :
	public SceneBase
{
public:
	Battle();
	Battle(int e1, int e2, int e3, int e4, int e5);
	~Battle();
	void Draw();
	int Reaction();
	int testgraph;
	void DrawMiniChar(); //�E���̃A��
	const int enemy_max = 5; //�G�L�����̍ő吔
	int numenemy;
	Monsters* monsters[5];
	int active_point[10]; //0~4�cPT���ɂ��L�����̍s���|�C���g�B5~�G�L������1�Ԗڂ���̍s���|�C���g�B�Ⴂ���ɍs��
	int turn_active[10]; //avtive_point��Ⴂ���ɕ��ׂ����̃L�����N�^�[�i���o�[(active_point�̓Y�����ˑ�)
	bool isplayer[10]; //
	Party* party;
	Characters* characters;
	int minichar_size_x;
	int minichar_size_y;
	void ActiveSort(); //active_point�̒Ⴂ���ɕ��ёւ���
	bool winflag = 0;
	bool unionattackflag = 0;
	void DrawCanActive(); //�s���̑I������\������
	int thickfont_h;
	int nowchoosef = 1;
	void DrawStringsCenterToHandle(int cpos_x, int cpos_y, int color_h, int fonr_h, const char* str); //���������̕�����`��
	void DrawMonster(); //�܂��
	const int monstersizex = 200;
	const int monsterposy = 60;
	const int monstersizey = 300;
	Randomer* randomer;
};

