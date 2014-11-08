#pragma once
#include<stdio.h>
#include"DxLib.h"
#include"Party.h"

//戦闘用エフェクトを描画するためのクラス
class BattleEffect
{
public:
	typedef struct point_
	{
		int left; //左上のx座標
		int top; //左上のy座標
		int right; //右下のx座標
		int bottom; //右下のy座標

	}point; //RECT構造体的な

	static BattleEffect* instance;
	static BattleEffect* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new BattleEffect;
		}
		return instance;
	}

	typedef struct effect_
	{
		int effect_h[10][10]; //各エフェクトのハンドル(1枚毎に
		char effect_f[10][10]; //各エフェクトの表示フレーム数
		point effect_p[10]; //各エフェクトの表示位置(1セット毎に
	}effect;

	effect player; //敵用のとプレイヤー用の2つを用意
	effect enemy;
	void LoadEffect(); //エフェクトのロード
	void LoadEffectFrame(){}; //エフェクトの表示フレームのロード
	void LoadEffectPos(){}; //エフェクトの表示位置のロード
	void DrawEffect(int monster_pos, int number,int* damage); //選択されたエフェクトの描画。ダメージも表示。int*なのは全体攻撃のため
	void DrawEffect_e(int target_pos, int number); //選択されたエフェクトの描画。敵用
	void Draw(int monster_pos, int number,int* damage); //DrawEffectとの仲介役
	void Draw_e(int target_pos, int number); //DrawEffectとの仲介役。敵用。targetposは左上から数えて1ずつ0から増えていく
	void mainDraw(); //大元のDraw()
	void DrawIntCenter(int x,int y,int value); //(x,y)を中心としてvalueを表示

	//敵のみ使用
	Party* party;
	int target_number;
	//共通の変数
	int time; //DrawEffectで使用される時間計測用の変数
	int elem; //現在のエフェクトが何枚目か。0を1枚目とする
	int nownumber; //現在表示しているエフェクトの番号
	int nowtargetpos; //仕方ないので記憶させるように
	bool playerflag = 0; //現在表示したいエフェクトがプレイヤーのものか敵のものかのフラグ
	//味方だけが使用
	int* nowdamage=nullptr;
	int alltime = 0; //1つのanimの累計time

private:
	BattleEffect();
	~BattleEffect();
	BattleEffect(const BattleEffect& rhs);
	BattleEffect& operator=(const BattleEffect& rhs);
};

