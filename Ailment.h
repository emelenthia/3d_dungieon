#pragma once
#include"Defines.h"

class Ailment //��Ԉُ�ɂ��ẴN���X
{
public:
	Ailment();
	~Ailment();

	typedef struct ailment_
	{
		char name[64]; //��Ԉُ햼
		int turns; //��Ԉُ킪���������܂ł̃^�[����
	}ailment_t;

	ailment_t m_ailment[Defines::AILMENT_MAX];
	void LoadAilment();
};

