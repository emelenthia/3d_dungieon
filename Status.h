#pragma once
class Status //モンスターとキャラクター共通のステータスクラス
{
public:
	Status();
	~Status();

	typedef struct tolerance //基本耐性の構造体
	{
		int cut; //斬耐性
		int beat; //殴耐性
		int stab; //突耐性
		int fire; //火
		int aqua; //水
		int wind; //風
		int earth; //土
		int light; //雷
	};

	typedef struct toleranceadd //加算耐性の構造体
	{
		int cut; //斬耐性
		int beat; //殴耐性
		int stab; //突耐性
		int fire; //火
		int aqua; //水
		int wind; //風
		int earth; //土
		int light; //雷
	};

	typedef struct abnomalous //各状態異常のフラグ
	{
		bool sleep;
		bool freez;
		bool silent;
		bool paralysis;
		bool poison;
	};

	typedef struct status //変化しない情報の構造体
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
	};

	typedef struct status_c //戦闘中に変化する情報の構造体
	{
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
	};
};

