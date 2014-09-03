#pragma once
class Status //モンスターとキャラクター共通のステータスクラス
{
public:
	Status();
	~Status();
};

//グローバルにしないと関数の返り値に出来ない
typedef struct tolerance_ //基本耐性の構造体
{
	int cut; //斬耐性
	int beat; //殴耐性
	int stab; //突耐性
	int fire; //火
	int aqua; //水
	int wind; //風
	int earth; //土
	int light; //雷
}tolerance;

typedef struct toleranceadd_ //加算耐性の構造体
{
	int cut; //斬耐性
	int stab; //突耐性
	int beat; //殴耐性
	int fire; //火
	int aqua; //水
	int wind; //風
	int earth; //土
	int light; //雷
}toleranceadd;

typedef struct abnomalous_ //各状態異常のフラグ
{
	bool sleep;
	bool freez;
	bool silent;
	bool paralysis;
	bool poison;
}abnomalous;

typedef int test;

typedef struct status_ //変化しない情報の構造体
{
	char name[21];
	int lv;
	int hpmax;
	int tpmax;
	int atk; //基本atk
	int def;
	int int_s;
	int res;
	int dex;
	int agi;
	tolerance Tolerance;
	int exp; //得られる総経験値
	int item[5]; //落とすアイテム
	int item_p[5]; //それぞれの落とす確率
	int item_pa; //そもそも落とす確率
}status;

typedef struct status_c_ //戦闘中に変化する情報の構造体
{
	int alive;
	int hp;
	int tp;
	int atk_scale; //atkの倍率
	int def_scale;
	int int_s_scale;
	int res_scale;
	int dex_scale;
	int agi_scale;
	toleranceadd ToleranceAdd;
	abnomalous Abnomalous;
}status_c;

