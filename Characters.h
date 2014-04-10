#pragma once
#include "Character_Data.h"
class Characters :
	public Character_Data
{
public:
	static Characters* instance;
	//// 唯一のアクセス経路
	static Characters* GetInstance()
	{
		if (instance == NULL)instance = new Characters();
		return instance;
	}

private:
	// 生成やコピーを禁止する
	Characters();
	Characters(const Characters& rhs);
	Characters& operator=(const Characters& rhs);
	~Characters(){};
};
