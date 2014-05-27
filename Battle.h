#pragma once
#include "SceneBase.h"
#include"Monsters.h"
#include"Party.h"
#include"Characters.h"

class Battle :
	public SceneBase
{
public:
	Battle();
	~Battle();
	void Draw();
	int Reaction();
	int testgraph;
	void DrawMiniChar(); //右側のアレ
	const int enemy_max = 5; //敵キャラの最大数
	int numenemy;
	Monsters* monsters[5];
	int active_point[10]; //0~4…PT順によるキャラの行動ポイント。5~敵キャラの1番目からの行動ポイント。低い順に行動
	int turn_active[10]; //avtive_pointを低い順に並べた時のキャラクターナンバー(active_pointの添え字依存)
	bool isplayer[10]; //
	Party* party;
	Characters* characters;
	int minichar_size_x;
	int minichar_size_y;
	void ActiveSort(); //active_pointの低い順に並び替える
};

