#pragma once
class Balloon //台詞欄
{
public:
	Balloon();
	~Balloon();
	void Draw();
	int boxcolor; //台詞欄の色のハンドル
	int talkcolor; //台詞の色のハンドル
	static int talkflag; //台詞欄を表示させるフラグ
	static char talktext[10][80]; //台詞(9回話を進められる)
	static int talkfinishflag;
};

