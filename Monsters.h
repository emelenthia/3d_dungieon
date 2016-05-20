#pragma once
//#include"studio.h"
#include"MonsterList.h"
#include"Status.h"
#include"Ailment.h"
#include"Defines.h"

//モンスターオブジェクト
//ファイルから情報を読み込み、オブジェクト1つにつきモンスター1体分の挙動をする

class Monsters
{
public:
	Monsters(){};
	Monsters(int n);
	~Monsters();
	void Draw(int pos_x, int pos_y, int size_x, int size_y, bool brightflag); //両方とも左上の座標

	typedef enum strain //種族一覧
	{
		MAJIC_LIFE = 1//魔法生物
	};
	strain Strain;
	status Status_;

	status_c Status_c;

	int graph_b; //大きい画像のハンドル
	int graph_m; //小さい画像のハンドル

	void MonsterSet(int n); //ファイルから情報を読み込んでn番目のモンスター情報に初期化。
	FILE* individuals_fp; //個々の情報を読み込むための使い回すポインタ
	char monster_file_name[101]; //モンスターの名前(ファイル読み込み用)
	char monster_file_name_temp[101]; //モンスターの名前(ファイル読み込み用)
	MonsterList* monsterlist; //ファイル一覧

	int monster_information_flag;
	void nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...);
	int brighttime = 0;
	double timeflo = 0;
	int m_ailment_turns[Defines::AILMENT_MAX]; //各状態異常の残りターン
	int m_ailment_level[Defines::AILMENT_MAX]; //各状態異常のレベル

private:
	Ailment* m_ailment;
};

