#pragma once
class Status //�����X�^�[�ƃL�����N�^�[���ʂ̃X�e�[�^�X�N���X
{
public:
	Status();
	~Status();
};

//�O���[�o���ɂ��Ȃ��Ɗ֐��̕Ԃ�l�ɏo���Ȃ�
typedef struct tolerance_ //��{�ϐ��̍\����
{
	int cut; //�a�ϐ�
	int beat; //���ϐ�
	int stab; //�ˑϐ�
	int fire; //��
	int aqua; //��
	int wind; //��
	int earth; //�y
	int light; //��
}tolerance;

typedef struct toleranceadd_ //���Z�ϐ��̍\����
{
	int cut; //�a�ϐ�
	int stab; //�ˑϐ�
	int beat; //���ϐ�
	int fire; //��
	int aqua; //��
	int wind; //��
	int earth; //�y
	int light; //��
}toleranceadd;

typedef struct abnomalous_ //�e��Ԉُ�̃t���O
{
	bool sleep;
	bool freez;
	bool silent;
	bool paralysis;
	bool poison;
}abnomalous;

typedef int test;

typedef struct status_ //�ω����Ȃ����̍\����
{
	char name[21];
	int lv;
	int hpmax;
	int tpmax;
	int atk; //��{atk
	int def;
	int int_s;
	int res;
	int dex;
	int agi;
	tolerance Tolerance;
	int exp; //�����鑍�o���l
	int item[5]; //���Ƃ��A�C�e��
	int item_p[5]; //���ꂼ��̗��Ƃ��m��
	int item_pa; //�����������Ƃ��m��
}status;

typedef struct status_c_ //�퓬���ɕω�������̍\����
{
	int alive;
	int hp;
	int tp;
	int atk_scale; //atk�̔{��
	int def_scale;
	int int_s_scale;
	int res_scale;
	int dex_scale;
	int agi_scale;
	toleranceadd ToleranceAdd;
	abnomalous Abnomalous;
}status_c;

