#pragma once
#include "SceneBase.h"
#include"Monsters.h"
#include"Party.h"
#include"Characters.h"
#include<random>
#include"Randomer.h"
#include"BattleEffect.h"
#include"Skill.h"
#include"Ailment.h"

class Battle :
	public SceneBase
{
public:
	Battle(){};
	Battle(int ne, int* monster_number,bool escape_flag);
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
	char issueflag = 0; //1なら勝利、-1なら敗北、0なら試合中
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
	int state = 0; //現在の状態。0…行動選択待ち、2…味方の攻撃中、3…防御している、4…スキル演出中、5…逃げている
#define CHOOSE_ACT 0
#define NORMAL_ATTACK 2
#define GUARD 3
#define SKILL 4
#define ESCAPE 5
	int checkstate = 0; //何か選択することに対して現在の状態。0…特になし、もしくは基礎行動選択待ち、1…協力攻撃選択待ち
						//2…通常攻撃対象選択待ち、3…スキル選択待ち、4…アイテム選択待ち
						//11…協力攻撃対象選択待ち、31…スキル対象(敵1体)選択待ち、41…アイテム対象選択待ち
	void TurnStart(); //ターン開始処理
	void TurnFinish(); //ターン終了処理
	int nowchar = -1; //現在行動しているキャラの番号
	bool can_escape_flag = 0; //逃げられるか否かのフラグ
	int time = 0;
	int temp_nowchoosea = -1;
	void DrawAttack(); //まんま
	void DrawSkill(); //スキル演出
	int numdiedchar; //敵と味方の!aliveのキャラ合計
	int m_numdiedEnemy; //敵の!aliveキャラの合計
#define NORMAL_ATTACK_TIME 35 //現在通常攻撃演出にかかる時間。いずれオプション設定できるように
#define TURN_DURING_TIME 10 //ターンとターンの間にある時間。クッション的な。意味あるかは知らない
#define GUARD_TIME 35 //防御処理に使う時間
	BattleEffect* battle_effect;
	bool turn_finish_flag=FALSE;
	void DrawResult(); //経験値獲得などの表示
	int temp = 0; //色々
	bool finishflag = 0; 
	void ActGuard();
	bool guardflag[10]; //各キャラのガードフラグ
	bool turn_finish_finish_flag=0; //エンドフェイズが終わったフラグ
	int temp_damage[10]; //一時的に表示するためのダメージを記憶。配列の要素はキャラの位置と連動
	int gameover_h; //ゲームオーバー画像のハンドル
	void DrawGameOver(); //ゲームオーバー画面の表示
	const bool debugflag = 1;
	FILE* debug_fp;
	void DebugPrintf(int number);
	void DamageCalculat(int char_numb, int act_numb, int* damage, int target_numb); //ダメージ計算用の関数。act_numbは通常攻撃の場合は-1

private:
	int m_chooseSkill; //現在選択しているスキルが上から何個目か
	Skill* m_skill;
	int m_t_skillNumber; //現在選択しているスキルが何のスキルか。毎回計算するのもあれだし記憶する
	Ailment* m_ailment;
#define SKILL_TIME 27 //スキルの処理をするtime
};

