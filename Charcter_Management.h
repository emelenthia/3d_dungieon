#pragma once
#include<stdio.h>

class Charcter_Management //キャラの総合情報管理
{
public:
	// 唯一のアクセス経路
	static Charcter_Management* GetInstance()
	{
		static Charcter_Management instance;  // 唯一のインスタンス
		return &instance;
	}

	FILE *fp;
	int character_max; //キャラの最大数
	void Set_Variable(); //初期ロード

private:
	// 生成やコピーを禁止する
	Charcter_Management(){}
	Charcter_Management(const Charcter_Management& rhs);
	Charcter_Management& operator=(const Charcter_Management& rhs);
	~Charcter_Management(){}//;
};

