#pragma once
#include "SceneBase.h"
#include"Monsters.h"
#include"Party.h"
#include"Characters.h"
#include<random>
#include"Randomer.h"
#include"BattleEffect.h"
#include"Skill.h"
#include"Ailment.h"

class Battle :
	public SceneBase
{
public:
	Battle(){};
	Battle(int ne, int* monster_number,bool escape_flag);
	~Battle();
	void Draw();
	int Reaction();
	void DrawMiniChar(); //�E���̃A��
	const int enemy_max = 5; //�G�L�����̍ő吔
	int numenemy;
	Monsters* monsters[5];
	int active_point[10]; //0~4�cPT���ɂ��L�����̍s���|�C���g�B5~�G�L������1�Ԗڂ���̍s���|�C���g�B�Ⴂ���ɍs��
	int turn_active[10]; //avtive_point��Ⴂ���ɕ��ׂ����̃L�����N�^�[�i���o�[(active_point�̓Y�����ˑ�)
	bool isplayer[10]; //
	Party* party;
	Characters* characters;
	int minichar_size_x;
	int minichar_size_y;
	void ActiveSort(); //active_point�̒Ⴂ���ɕ��ёւ���
	char issueflag = 0; //1�Ȃ珟���A-1�Ȃ�s�k�A0�Ȃ玎����
	bool unionattackflag = 0; //���͍U�����ł���t���O
	void DrawCanActive(); //�s���̑I������\������
	int thickfont_h;
	int nowchoosef = 1; //���ݑI�΂�Ă����b�s��
	int nowchooses = 0; //���ݑI�΂�Ă���X�L��
	int nowchoosea = -1; //���ݑI��ł���U���Ώ�
	void DrawStringsCenterToHandle(int cpos_x, int cpos_y, int color_h, int fonr_h, const char* str); //���������̕�����`��
	void DrawMonster(); //�܂��
	const int monstersizex = 200;
	const int monsterposy = 80;
	const int monstersizey = 300;
	Randomer* randomer;
	void nfscanf_(const int line, const char* file, FILE* scan_target, const char* format_text, ...);
	void CheckResult();
	int state = 0; //���݂̏�ԁB0�c�s���I��҂��A2�c�����̍U�����A3�c�h�䂵�Ă���A4�c�X�L�����o���A5�c�����Ă���
#define CHOOSE_ACT 0
#define NORMAL_ATTACK 2
#define GUARD 3
#define SKILL 4
#define ESCAPE 5
	int checkstate = 0; //�����I�����邱�Ƃɑ΂��Č��݂̏�ԁB0�c���ɂȂ��A�������͊�b�s���I��҂��A1�c���͍U���I��҂�
						//2�c�ʏ�U���ΏۑI��҂��A3�c�X�L���I��҂��A4�c�A�C�e���I��҂�
						//11�c���͍U���ΏۑI��҂��A31�c�X�L���Ώ�(�G1��)�I��҂��A41�c�A�C�e���ΏۑI��҂�
	void TurnStart(); //�^�[���J�n����
	void TurnFinish(); //�^�[���I������
	int nowchar = -1; //���ݍs�����Ă���L�����̔ԍ�
	bool can_escape_flag = 0; //�������邩�ۂ��̃t���O
	int time = 0;
	int temp_nowchoosea = -1;
	void DrawAttack(); //�܂��
	void DrawSkill(); //�X�L�����o
	int numdiedchar; //�G�Ɩ�����!alive�̃L�������v
	int m_numdiedEnemy; //�G��!alive�L�����̍��v
#define NORMAL_ATTACK_TIME 35 //���ݒʏ�U�����o�ɂ����鎞�ԁB������I�v�V�����ݒ�ł���悤��
#define TURN_DURING_TIME 10 //�^�[���ƃ^�[���̊Ԃɂ��鎞�ԁB�N�b�V�����I�ȁB�Ӗ����邩�͒m��Ȃ�
#define GUARD_TIME 35 //�h�䏈���Ɏg������
	BattleEffect* battle_effect;
	bool turn_finish_flag=FALSE;
	void DrawResult(); //�o���l�l���Ȃǂ̕\��
	int temp = 0; //�F�X
	bool finishflag = 0; 
	void ActGuard();
	bool guardflag[10]; //�e�L�����̃K�[�h�t���O
	bool turn_finish_finish_flag=0; //�G���h�t�F�C�Y���I������t���O
	int temp_damage[10]; //�ꎞ�I�ɕ\�����邽�߂̃_���[�W���L���B�z��̗v�f�̓L�����̈ʒu�ƘA��
	int gameover_h; //�Q�[���I�[�o�[�摜�̃n���h��
	void DrawGameOver(); //�Q�[���I�[�o�[��ʂ̕\��
	const bool debugflag = 1;
	FILE* debug_fp;
	void DebugPrintf(int number);
	void DamageCalculat(int char_numb, int act_numb, int* damage, int target_numb); //�_���[�W�v�Z�p�̊֐��Bact_numb�͒ʏ�U���̏ꍇ��-1

private:
	int m_chooseSkill; //���ݑI�����Ă���X�L�����ォ�牽�ڂ�
	Skill* m_skill;
	int m_t_skillNumber; //���ݑI�����Ă���X�L�������̃X�L�����B����v�Z����̂����ꂾ���L������
	Ailment* m_ailment;
#define SKILL_TIME 27 //�X�L���̏���������time
};

