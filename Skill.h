#pragma once
#include"DxLib.h"
#include"Defines.h"

class Skill //スキル関連を纏めるクラス
{
public:
	static Skill* instance;
	//// 唯一のアクセス経路
	static Skill* GetInstance()
	{
		if (instance == NULL)instance = new Skill();
		return instance;
	}
	char m_skillList_PT[SKILL_MAX_PT][32]; //味方が使用するスキルの名前のリスト
	int LoadSkillList_PT(); //味方が使用するスキルの名前のリストをロードする

private:
	// 生成やコピーを禁止する
	Skill();
	Skill(const Skill& rhs);
	Skill& operator=(const Skill& rhs);
	~Skill() {};
};

