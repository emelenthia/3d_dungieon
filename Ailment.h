#pragma once
#include"Defines.h"

class Ailment //状態異常についてのクラス
{
public:
	Ailment();
	~Ailment();

	typedef struct ailment_
	{
		char name[64]; //状態異常名
		int turns; //状態異常が解除されるまでのターン数
	}ailment_t;

	ailment_t m_ailment[Defines::AILMENT_MAX];
	void LoadAilment();
};

