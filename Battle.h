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
	Battle(){};
	Battle(int ne, int* monster_number);
	~Battle();
	void Draw();
	int Reaction();
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
	bool winflag = 0;
	bool unionattackflag = 0; //協力攻撃ができるフラグ
	void DrawCanActive(); //行動の選択肢を表示する
	int thickfont_h;
	int nowchoosef = 1; //現在選ばれている基礎行動
	int nowchooses = 0; //現在選ばれているスキル
	int nowchoosea = -1; //現在選んでいる攻撃対象
	void DrawStringsCenterToHandle(int cpos_x, int cpos_y, int color_h, int fonr_h, const char* str); //中央揃えの文字列描画
	void DrawMonster(); //まんま
	const int monstersizex = 200;
	const int monsterposy = 80;
	const int monstersizey = 300;
	Randomer* randomer;
	void nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...);
	void CheckResult();
	int state = 0; //現在の状態。0…行動選択待ち、2…味方の攻撃中、3…防御している、5…逃げている
	int checkstate = 0; //何か選択することに対して現在の状態。0…特になし、もしくは基礎行動選択待ち、1…協力攻撃選択待ち
						//2…通常攻撃対象選択待ち、3…スキル選択待ち、4…アイテム選択待ち
						//11…協力攻撃対象選択待ち、31…スキル対象選択待ち、41…アイテム対象選択待ち
	void TurnStart(); //ターン開始処理
	int nowchar = -1; //現在行動しているキャラの番号
};

