#pragma once
#include<stdio.h>
#include"DxLib.h"

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

	int effect_h[10][10]; //各エフェクトのハンドル(1枚毎に
	char effect_f[10][10]; //各エフェクトの表示フレーム数
	point effect_p[10]; //各エフェクトの表示位置(1セット毎に
	void LoadEffect(); //エフェクトのロード
	void LoadEffectFrame(){}; //エフェクトの表示フレームのロード
	void LoadEffectPos(){}; //エフェクトの表示位置のロード
	void DrawEffect(int monster_pos, int number); //選択されたエフェクトの描画
	int time; //DrawEffectで使用される時間計測用の変数
	int elem; //現在のエフェクトが何枚目か。0を1枚目とする
	void Draw(int monster_pos,int number); //DrawEffectとの仲介役
	int nownumber; //現在表示しているエフェクトの番号

private:
	BattleEffect();
	~BattleEffect();
	BattleEffect(const BattleEffect& rhs);
	BattleEffect& operator=(const BattleEffect& rhs);
};

