#pragma once

static const int SKILL_MAX_PT = 8; //味方のスキルの総数
static const int CHARA_MAX = 15; //キャラクターの最大数

class Defines
{
public:
	Defines();
	~Defines();
	static const int player_size_x = 32;
	static const int player_size_y = 48;
	static const int char_max = 15; //キャラクターの最大数
	//どのmodeかの判断
	static const int GUILD = 0;
	static const int FIELD = 1;
	static const int BATTLE = 2;
	static const int SKILL_MAX_LEVEL = 10; //味方スキルの最大レベル。
	static const int AILMENT_MAX = 12; //状態異常の総数
	static const int PT_MAX = 5; //味方PTメンバーの最大数
	static const int AILMENT_MAX_LEVEL = 10; //状態異常の最大レベル
};

