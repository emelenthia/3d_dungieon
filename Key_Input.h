#pragma once
#include"Options.h"
class Key_Input //�L�[�{�[�h����̓��͂��󂯎��N���X
{
public:
	Key_Input();
	~Key_Input();

	static char buff[256];
	static int buff_time[256]; //���ꂼ��̃L�[�̉���������
	int i;
	void KeyUpdate();
	int talkingflag; //�b�����t���O
	int JoyPadInput;
	int AnalogInputx;
	int AnalogInputy;
	Options *options;
	//D_XINPUT_STATE xboxInput;
};

