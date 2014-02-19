#pragma once
class Events //�C�x���g����������N���X�B����singleton
{
public:   // �B��̃A�N�Z�X�o�H
	static Events* GetInstance()
	{
		static Events instance;  // �B��̃C���X�^���X
		return &instance;
	}
	// ���Ƃ́A���̃N���X���g���K�v�ȃ����o���`����
	int ev_act(int number); //�^����ꂽ�ԍ��ɑ΂���C�x���g�̌Ăяo��
	void in_battle(); //�퓬�V�[���Ɉړ�

private:
	// ������R�s�[���֎~����
	Events(){}
	Events(const Events& rhs);
	Events& operator=(const Events& rhs);
	~Events();
};

