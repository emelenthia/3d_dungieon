#pragma once
#include<stdio.h>

class ItemList
{
public:
	static ItemList* instance;
	static ItemList* GetInstance() 
	{
		if (instance == NULL)
		{
			instance = new ItemList;
		}
		return instance;
	}

	//�A�C�e���\����(�Ϗ��)�c����͑��̃N���X�Ŏg���܂�
	typedef struct s_item_
	{
		int number; //�A�C�e���i���o�[�B�\�͌�ŗp��
		int num; //���̃A�C�e���������Ă����
		int plus; //���j�[�N�łȂ������̏ꍇ��+�������t���̂ł���
		int special[2]; //���j�[�N�łȂ������ɂ͕t�^���ʂ��t�����܂�
	}s_item;

	//�A�C�e���\����(��{���)�c����͂��̃N���X�Ŏg���܂��B���̃N���X����Q�Ƃ���܂�
	typedef struct s_itemcommon_
	{
		char name[64];
		bool unique; //TRUE�Ȃ烆�j�[�N�����AFALSE�Ȃ炻��ȊO
		bool num; //TRUE�Ȃ琔������FALSE�Ȃ琔�����Ȃ��āc����A��̂Ƃ��Ƃ܂Ƃ߂ăr�b�g�Ǘ��̕�������?

	}s_itemcommon;

private:
	ItemList();
	~ItemList();
	ItemList(const ItemList& rhs);
	ItemList& operator=(const ItemList& rhs);
	
};

