#pragma once
class Flags //フラグをまとめるクラス?
{
public:
	Flags();
	~Flags();
	static int talkflag; //現在会話中であるフラグ
	static int menuflag; //メニュー画面ですよ～。でも現在はキャンプ
	static int nowscene; //0xf1e1dならダンジョン、0xba771eなら戦闘、0x8011dならギルド
	static int guild_now; //今実行しているエントランスのメニュー
	static int menu_window_size_x; //ギルドのメニュー欄の右のx座標
	static int menu_window_size_y; //ギルドのメニュー欄の右のy座標
	static int character_show_flag; //キャラクターの情報を見ているフラグ
	static int battleflag; //現在戦闘中であるフラグ
};

