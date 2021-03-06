#pragma once
#include "SceneBase.h"
#include"DxLib.h"
//#include<stdio.h>
#include"SaveData.h"
#include"Options.h"
#include"Party.h"
#include"Battle.h"
#include"BattleEffect.h"
#include"Camp.h"

class Dungeon :
	public SceneBase
{
public:
	Dungeon();
	~Dungeon();
	void Draw();
	int Reaction();
	int DrawSquare(float pos_x_lu, float pos_y_lu, float pos_z_lu, float pos_x_rd, float pos_y_rd, float pos_z_rd); //3d空間に正四角形を書く関数
	//int kabe_handle;
	int DrawMap_c(unsigned char(*map_data)[10], int x_max, int z_max); //マップの描画。深度バッファしない
	void DrawMiniMap(); //ミニマップの描画
	FILE *fp;
	int kabe_handle;
	int pos_x;
	int pos_z;
	const int block_size = 100;
	int muki = 0; //0=U,1=R,2=D,3=L
	unsigned char map_data[10][10];
	int x_max = 0, z_max = 0;
	VECTOR target_camera;
	VECTOR player_camera;
	int y = 1;
	typedef enum _STATE {
		NEUTRAL = 0,
		GO_FORWARD,
		TURN_RIGHT,
		TURN_BACK,
		TURN_LEFT,
		GO_RIGHT,
		GO_LEFT,
		ENCOUNT,
		GO_BACK,
		GO_ONE_RETURN,
		CAMP
	}STATE;
	//この辺いい加減enumしよう
	STATE state; //状態を表す変数。1で前進中。2で右転回。3で逆を向く。4で左転回。
			   //5で右平行移動。6で左平行移動。7でエンカウント開始。8で後退。9で一歩戻る。10でキャンプ画面
	STATE lastact; //逃げた場合にやる事。state依存
	int revflag = 0; //回転しているフラグ。要するに回転時はエンカウントしないため
	int time; //状態にかかっている時間を保持。
	void Return_right(); //右転回
	void GoForward(); //前進
	void ReturnBack();
	void ReturnLeft();
	void GoRight();
	void GoLeft();
	void GoBack();
	int down_help = 0; //下ボタン時のヘルパー
	int flaging = 0; //便利フラッグ
	static int floors; //現在の階層
	int start_z = 0;
	int start_x = 0;
	void LoadDungeon();
	int black;
	int yellow;
	int white;
	int blue;
	int nowchoose = 0;
	int feel_flag;
	char kabe_name[100];
	unsigned char fog_r = 0;
	unsigned char fog_g = 0;
	unsigned char fog_b = 0;
	float fog_start = 0;
	float fog_goal = 0;
	int yajirushi_h;
	SaveData *savedata;
	Options *options;
	Party *party;
	int non_walk_flag = 0; //帰るかのメッセージの表示しないフラグ
	int minimap_flag = 0; //0で非表示、1で通常表示、2で全体表示?
	char dungeon_name[50];
	Battle* battle;
	void GetMonsterKind();
	int monster_number[5];
	int numenemy = 0;
	void nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...);
	bool CheckCanEscape(); //逃走可能か調べる
	BattleEffect* battleeffect; //パーティーより後に描画するため

private: //最初はm_なしpublicでやってたためこんなことになってる
	Camp* m_camp;
};
