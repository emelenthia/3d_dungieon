#pragma once
#include "Character_Data.h"
class Character_02 : //����͐瑁
	public Character_Data
{
public:
	// �B��̃A�N�Z�X�o�H
	/*static Character_02* GetInstance()
	{
		static Character_02 instance;  // �B��̃C���X�^���X
		return &instance;
	}*/

	static Character_02* instance;
	//// �B��̃A�N�Z�X�o�H
	static Character_02* GetInstance()
	{
		if (instance == NULL)instance = new Character_02();
		return instance;
	}


private:
	// ������R�s�[���֎~����
	Character_02(){}
	Character_02(const Character_02& rhs);
	Character_02& operator=(const Character_02& rhs);
	~Character_02(){};
};

