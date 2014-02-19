#pragma once
#include "Objects.h"
#include<stdio.h>
#include"Events.h"

class Talker :
	public Objects
{
public:
	Talker();
	~Talker();
	void talk_set(); //�ԓ����e���Z�b�g����
	FILE *fp;
	void Draw(); //�I�[�o�[���C�h
	int talkmax; //��b�̃y�[�W��
	char talk_mean[10][80]; //�ԓ����e�B�Ƃ肠����80�����܂�
	int choosemax; //�I������
	char choose_mean[10][80]; //�I�����̓��e�B�Ƃ肠����80�����܂�
	virtual int Reaction(); //�I�[�o�[���C�h&���z�֐�
	void LoadTalk(char file_pointer[40]); //�䎌�̃��[�h
	int boxcolor; //�䎌���̐F�̃n���h��
	int talkcolor; //�䎌�̐F
	int talkpage; //�䎌�̃y�[�W��
	char file_name[40];
	int chooseflag; //�I�������̃t���O
	int choosenumber; //�I�����ɑ΂�����̈ʒu
	char choose_file_name[5][40]; //�e�I�����ɑ΂���ԓ��̃t�@�C��
	int change_pattern; //��b��ς���ۂɋx�e���͂��ނȂ�2�A�����łȂ��Ȃ�1
	Events *events_t = Events::GetInstance();
	int event_number; //�Ăяo���C�x���g
};

