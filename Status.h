#pragma once
class Status //�����X�^�[�ƃL�����N�^�[���ʂ̃X�e�[�^�X�N���X
{
public:
	Status();
	~Status();

	typedef struct tolerance //��{�ϐ��̍\����
	{
		int cut; //�a�ϐ�
		int beat; //���ϐ�
		int stab; //�ˑϐ�
		int fire; //��
		int aqua; //��
		int wind; //��
		int earth; //�y
		int light; //��
	};

	typedef struct toleranceadd //���Z�ϐ��̍\����
	{
		int cut; //�a�ϐ�
		int beat; //���ϐ�
		int stab; //�ˑϐ�
		int fire; //��
		int aqua; //��
		int wind; //��
		int earth; //�y
		int light; //��
	};

	typedef struct abnomalous //�e��Ԉُ�̃t���O
	{
		bool sleep;
		bool freez;
		bool silent;
		bool paralysis;
		bool poison;
	};

	typedef struct status //�ω����Ȃ����̍\����
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
	};

	typedef struct status_c //�퓬���ɕω�������̍\����
	{
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
	};
};

