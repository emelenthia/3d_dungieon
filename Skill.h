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
	enum skillType { PASSIVE = 0, ATTACK, HEAL, HELP };
	typedef struct //スキル型の構造体
	{
		char m_skillList_PT[32]; //味方が使用するスキルの名前のリスト
		char m_skillType; //各スキルの使用属性。0ならパッシブ、1なら攻撃系、2なら回復系、3なら補助系。enum skillType参照
		char m_skillText[128]; //スキルの説明文。TODO:変数名からm_skillを抜いても良いかも
	}t_skills;
	t_skills m_skill_PT[SKILL_MAX_PT];
	int LoadSkillList_PT(); //味方が使用するスキルの名前のリストをロードする
	bool GetSkillCanUse_PT(int number, int mode); //指定したスキルが指定したmodeで使用できるかどうかを返す。使用できるならTRUE。modeはdefines参照
	

private:
	// 生成やコピーを禁止する
	Skill();
	Skill(const Skill& rhs);
	Skill& operator=(const Skill& rhs);
	~Skill() {};
};

