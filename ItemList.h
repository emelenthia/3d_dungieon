#pragma once
#include<stdio.h>
#include<fstream>
#include<sstream>
#include<iostream>
#include<string>
using namespace std;

const int ITEM_ALL = 3;

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

	//アイテムと装備は分けることにした…?
	//アイテム構造体(可変情報)…これは他のクラスで使います
	typedef struct s_item_
	{
		int number; //アイテムナンバー。表は後で用意
		int num; //そのアイテムを持っている個数
		//int plus; //ユニークでない装備の場合は+○○が付くのでそれ //とりあえずこの辺は一旦無しで
		//int special[2]; //ユニークでない装備には付与効果が付けられます
	}s_item;

	//アイテム構造体(基本情報)…これはこのクラスで使います。他のクラスから参照されます
	typedef struct s_itemcommon_
	{
		string name;
		string descript; //説明
		bool equip; //TRUEなら装備
		bool unique; //TRUEならユニークアイテム、FALSEならそれ以外。装備はどうする?
	//	bool num; //TRUEなら数えられてFALSEなら数えられなくて…これ、上のとかとまとめてビット管理の方がいい?

	}s_itemcommon;

	

private:
	ItemList();
	~ItemList();
	ItemList(const ItemList& rhs);
	ItemList& operator=(const ItemList& rhs);

	void LoadItemList();
	s_itemcommon m_itemcommon[ITEM_ALL];
};

