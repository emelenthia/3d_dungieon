#pragma once
#include "Character_Data.h"
class Character_Haruka :
	public Character_Data
{
public:
	static Character_Haruka* instance;
	//// 唯一のアクセス経路
	static Character_Haruka* GetInstance()
	{
		if (instance == NULL)instance = new Character_Haruka();
		return instance;
	}


private:
	// 生成やコピーを禁止する
	Character_Haruka(){}
	Character_Haruka(const Character_Haruka& rhs);
	Character_Haruka& operator=(const Character_Haruka& rhs);
	~Character_Haruka(){};
	


};

