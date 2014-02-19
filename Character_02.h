#pragma once
#include "Character_Data.h"
class Character_02 : //現状は千早
	public Character_Data
{
public:
	// 唯一のアクセス経路
	/*static Character_02* GetInstance()
	{
		static Character_02 instance;  // 唯一のインスタンス
		return &instance;
	}*/

	static Character_02* instance;
	//// 唯一のアクセス経路
	static Character_02* GetInstance()
	{
		if (instance == NULL)instance = new Character_02();
		return instance;
	}


private:
	// 生成やコピーを禁止する
	Character_02(){}
	Character_02(const Character_02& rhs);
	Character_02& operator=(const Character_02& rhs);
	~Character_02(){};
};

