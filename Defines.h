#pragma once

static const int SKILL_MAX_PT = 8; //�����̃X�L���̑���
static const int CHARA_MAX = 15; //�L�����N�^�[�̍ő吔

class Defines
{
public:
	Defines();
	~Defines();
	static const int player_size_x = 32;
	static const int player_size_y = 48;
	static const int char_max = 15; //�L�����N�^�[�̍ő吔
	//�ǂ�mode���̔��f
	static const int GUILD = 0;
	static const int FIELD = 1;
	static const int BATTLE = 2;
	static const int SKILL_MAX_LEVEL = 10; //�����X�L���̍ő僌�x���B
	static const int AILMENT_MAX = 12; //��Ԉُ�̑���
	static const int PT_MAX = 5; //����PT�����o�[�̍ő吔
	static const int AILMENT_MAX_LEVEL = 10; //��Ԉُ�̍ő僌�x��
};

