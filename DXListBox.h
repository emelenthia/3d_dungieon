#pragma once
#include"DxLib.h"
#include<vector>
using namespace std;

//アイテムリストとか、出来る行動のリストとかを表示する際に使用するクラス
//1つのウィンドウ(リスト)につき1つクラスのインスタンスを作る


class DXListBox
{
public:
	DXListBox();
	~DXListBox();
	void Draw(); //このクラスの肝
	void AddNameList(string str);
	void AddExplanationList(string str);
	void SetExplanationFlag(bool flag);
	void SetPos(int x, int y, int sizex, int sizey);
	void SetChoose(int choose);
	void DownChoose(); //一番下が選ばれている場合に上に戻ってくることを考慮して現在選ばれている物を1つ下にする
	void UpChoose();
	int GetChoose(){ return m_choose_now; }


private:
	int m_choose_now; //このリストで今選ばれているもの
	int m_num_item; //このリストで表示すべき一覧の個数
	vector<string> m_nameList;
	vector<string> m_explanationList;
	bool m_bExplanation; //これがTRUEなら上に説明文を表示
	const int strHigh = 20; //1行の高さ
	int m_pos_x; //表示枠の左上の位置
	int m_pos_y;
	int m_size_x;
	int m_size_y;
};

