#pragma once
#include"Defines.h"
#include"Functions_3DD.h"
#include"Colors.h"


#define AIL_POISON 0
#define AIL_PARALYSIS 1
#define AIL_SLOW 2
#define AIL_FREEZE 3
#define AIL_AILENCE 4
#define AIL_PETRIFY 5
#define AIL_SLEEP 6
//10～11…FTスキルによる状態異常
#define AIL_PROVOKE 10
#define AIL_WARCRY 11
//12～…PLスキルに


class Ailment //状態異常についてのクラス
{
public:
	static Ailment* instance;
	static Ailment* GetInstance()
	{
		if (instance == NULL)instance = new Ailment;
		return instance;
	}

	typedef struct ailment_
	{
		char name[64]; //状態異常名
		int turns[Defines::AILMENT_MAX_LEVEL]; //状態異常が解除されるまでのターン数
		int walks[Defines::AILMENT_MAX_LEVEL]; //状態異常が解除されるまでの歩数
		int de_buff; //バフかデバフか。デバフなら1、バフなら2
	}ailment_t;

	ailment_t m_ailment[Defines::AILMENT_MAX];
	void LoadAilment();

private:
	// 生成やコピーを禁止する
	Ailment();
	~Ailment();
	Ailment(const Ailment& rhs);
	Ailment& operator=(const Ailment& rhs);
};

