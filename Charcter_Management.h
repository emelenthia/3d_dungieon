#pragma once
#include<stdio.h>

class Charcter_Management //�L�����̑������Ǘ�
{
public:
	// �B��̃A�N�Z�X�o�H
	static Charcter_Management* GetInstance()
	{
		static Charcter_Management instance;  // �B��̃C���X�^���X
		return &instance;
	}

	FILE *fp;
	int character_max; //�L�����̍ő吔
	void Set_Variable(); //�������[�h

private:
	// ������R�s�[���֎~����
	Charcter_Management(){}
	Charcter_Management(const Charcter_Management& rhs);
	Charcter_Management& operator=(const Charcter_Management& rhs);
	~Charcter_Management(){}//;
};

