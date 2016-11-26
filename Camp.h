#pragma once
#include"DxLib.h"
#include"Characters.h" //�L�����̊G�Ȃǂ�\�����邽��
#include"Options.h"
#include"Guild_PT.h"
#include"Character_Show.h"
#include"Key_Input.h"

//��{�I��Guild_Main�𗬗p�c�Ƃ������A�����ƍ���Ă����Guild_Main�Ƃ��Ŏg���܂킷�ׂ������
class Camp
{
public:
	Camp();
	~Camp();

	void Draw();
	int Reaction();

private:
	int str_size_max; //������̍ő�̑傫��(�`���)
	bool m_char_flag;
	Characters *char_pt;
	int char_ran; //�����_���ɕ\�������Ă��鍡�̃L�����̔ԍ��B1����
	Options *m_options;
	Guild_PT *guild_pt;
	int list_max; //menu_list�̐�
	Party *m_party;
	int m_choose_now;
	char m_menu_explanation[20][100];
	char m_menu_list[20][20]; //�s��̈ꗗ
	Character_Show *m_character_show;
	int choosed_number; //�I�������s��
	int fscanf_r(char *file_name); //�܂Ƃ߂�fscan_s
	bool m_1f_flag; //1F�ڂ̍s���ł��邱�Ƃ���������(�L�����v��������Ă����u�ԂɃL�����v�{�^���Ŕ����Ȃ��悤��)
	typedef enum camp_list_ //���������ԍ��w����Č�Œ����ɂ�������悭�Ȃ��C������(���ڃ\�[�X�ɏ����Ă邩��RPG�G�f�B�^�݂����ɏo���Ȃ�)�c
	{
		BAG = 0,
		EQUIP,
		CSUTOM,
		STATES,
		QUEST,
		OTHER,
		SAVE,
		LOAD,
		OPTION,
		TITLE,
		CLOSE
	}camp_list;
	/*
	
#include"Party.h" //PT�̕\��

class Guild_Scene_Base //�M���h�N���X����s����e��ʂ̃N���X�̋��ʌ^
{
public:
	virtual void Draw();
	virtual int Reaction() = 0;
	int background_h1;
	FILE *fp;
	int str_size_max; //������̍ő�T�C�Y
	int char_flag = 1; //�L�����̕\���t���O
	*/
};

