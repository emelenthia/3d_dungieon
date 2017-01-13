#pragma once
#include"DxLib.h"
#include<vector>
using namespace std;

//�A�C�e�����X�g�Ƃ��A�o����s���̃��X�g�Ƃ���\������ۂɎg�p����N���X
//1�̃E�B���h�E(���X�g)�ɂ�1�N���X�̃C���X�^���X�����


class DXListBox
{
public:
	DXListBox();
	~DXListBox();
	void Draw(); //���̃N���X�̊�
	void AddNameList(string str);
	void AddExplanationList(string str);
	void SetExplanationFlag(bool flag);
	void SetPos(int x, int y, int sizex, int sizey);
	void SetChoose(int choose);
	void DownChoose(); //��ԉ����I�΂�Ă���ꍇ�ɏ�ɖ߂��Ă��邱�Ƃ��l�����Č��ݑI�΂�Ă��镨��1���ɂ���
	void UpChoose();
	int GetChoose(){ return m_choose_now; }


private:
	int m_choose_now; //���̃��X�g�ō��I�΂�Ă������
	int m_num_item; //���̃��X�g�ŕ\�����ׂ��ꗗ�̌�
	vector<string> m_nameList;
	vector<string> m_explanationList;
	bool m_bExplanation; //���ꂪTRUE�Ȃ��ɐ�������\��
	const int strHigh = 20; //1�s�̍���
	int m_pos_x; //�\���g�̍���̈ʒu
	int m_pos_y;
	int m_size_x;
	int m_size_y;
};

