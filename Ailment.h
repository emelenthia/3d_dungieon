#pragma once
#include"Defines.h"
#include"Functions_3DD.h"
#include"Colors.h"

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

