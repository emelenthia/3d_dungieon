#pragma once
#include<stdio.h>
#include"Characters.h"

class Party
{
public:
	static Party* instance;
	static Party* GetInstance()
	{
		if (instance == NULL)instance = new Party;
		return instance;
	}

	void Draw();
	int party_type; //�Ґ��̌`�B0�ŃL�����Ȃ��B
					//			11�ŃL����1�́B
					//			21�ŃL����2�́B���O���l�B
					//			22�ŃL����2�́B���O���e��l�B
					//			31�ŃL����3�́B���O��O�l�B
					//			32�ŃL����3�́B���O���l�A����l�B
					//			33�ŃL����3�́B���O���l�A����l�B
					//			41�ŃL����4�́B���O��O�l�A����l�B
					//			42�ŃL����4�́B���O���e��l�B
					//			43�ŃL����4�́B���O���l�A���O�l�B
					//			51�ŃL����5�́B���O��O�l�A����l�B
					//			52�ŃL����5�́B���O���l�A���O�l�B
	int party_info[5]; //���ォ�珇��0�Ԗڂɂ���L�����̔ԍ�
	FILE* fp;
	int pos_x_lu_territory; //�p�[�e�B�̕`�ʂɎg����͈͂̍����x���W
	int pos_y_lu_territory; //�p�[�e�B�̕`�ʂɎg����͈͂̍����y���W
	int pos_x_rd_territory; //�p�[�e�B�̕`�ʂɎg����͈͂̉E����x���W
	int pos_y_rd_territory; //�p�[�e�B�̕`�ʂɎg����͈͂̉E����y���W
	int crevice_x; //�L�������̌��Ԃ̉��̑傫��
	int crevice_y; //�L�������̌��Ԃ̏c�̑傫��
	int size_x; //�L�����`��g�̉��̑傫��
	int size_y; //�L�����`��g�̏c�̑傫��
	int countdbt; // DrawBox_t�����s������
	void DrawBox_t(int front_or_back,float left_pos_number); //0�őO�A1�Ō�B0�ō���A1�Ő^�񒆁A0.5�P�ʂ�2�܂�
	int testgraph, testgraph2;
	Characters *characters;
	void Save();
	void DrawPartyType();
	int GetNumMember();
private:
	// ������R�s�[���֎~����
	Party();
	~Party();
	Party(const Party& rhs);
	Party& operator=(const Party& rhs);
};

