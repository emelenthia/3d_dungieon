#pragma once
#include<stdio.h>
#include"MonsterList.h"
#include"Status.h"

//モンスターオブジェクト
//ファイルから情報を読み込み、オブジェクト1つにつきモンスター1体分の挙動をする

class Monsters
{
public:
	Monsters(int n);
	~Monsters();
	void Draw();

	typedef enum strain //種族一覧
	{
		MAJIC_LIFE //魔法生物
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
};

