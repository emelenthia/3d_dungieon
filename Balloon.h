#pragma once
class Balloon //�䎌��
{
public:
	Balloon();
	~Balloon();
	void Draw();
	int boxcolor; //�䎌���̐F�̃n���h��
	int talkcolor; //�䎌�̐F�̃n���h��
	static int talkflag; //�䎌����\��������t���O
	static char talktext[10][80]; //�䎌(9��b��i�߂���)
	static int talkfinishflag;
};

