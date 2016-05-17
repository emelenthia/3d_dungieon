#pragma once
#include"Defines.h"
#include"Functions_3DD.h"
#include"Colors.h"

class Ailment //��Ԉُ�ɂ��ẴN���X
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
		char name[64]; //��Ԉُ햼
		int turns[Defines::AILMENT_MAX_LEVEL]; //��Ԉُ킪���������܂ł̃^�[����
		int walks[Defines::AILMENT_MAX_LEVEL]; //��Ԉُ킪���������܂ł̕���
		int de_buff; //�o�t���f�o�t���B�f�o�t�Ȃ�1�A�o�t�Ȃ�2
	}ailment_t;

	ailment_t m_ailment[Defines::AILMENT_MAX];
	void LoadAilment();

private:
	// ������R�s�[���֎~����
	Ailment();
	~Ailment();
	Ailment(const Ailment& rhs);
	Ailment& operator=(const Ailment& rhs);
};

