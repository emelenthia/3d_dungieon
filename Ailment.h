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
//10�`11�cFT�X�L���ɂ���Ԉُ�
#define AIL_PROVOKE 10
#define AIL_WARCRY 11
//12�`�cPL�X�L����


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

