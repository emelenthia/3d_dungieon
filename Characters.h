#pragma once
#include "Character_Data.h"
class Characters :
	public Character_Data
{
public:
	static Characters* instance;
	//// �B��̃A�N�Z�X�o�H
	static Characters* GetInstance()
	{
		if (instance == NULL)instance = new Characters();
		return instance;
	}

private:
	// ������R�s�[���֎~����
	Characters();
	Characters(const Characters& rhs);
	Characters& operator=(const Characters& rhs);
	~Characters(){};
};
