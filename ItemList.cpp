#include "ItemList.h"

ItemList* ItemList::instance;

ItemList::ItemList()
{
	LoadItemList();
}


ItemList::~ItemList()
{
}


void ItemList::LoadItemList()
{
	int num = 0;
	ifstream ifs;
	ifs.open("./scn/item/itemlist.txt");
	string str;

	if (ifs.fail())
	{
		//失敗した時の処理
	}
	else
	{
		//成功した時の処理
		while (getline(ifs, str))
		{
			int i = 0;
			std::string tmp;
			std::istringstream stream(str);
			getline(stream, tmp, ',');
			m_itemcommon[i].name = tmp;
			getline(stream, tmp, ',');
			m_itemcommon[i].descript = tmp;
			getline(stream, tmp, ',');
			m_itemcommon[i].equip = (bool)stoi(tmp);
			getline(stream, tmp, ',');
			m_itemcommon[i].unique = (bool)stoi(tmp);
			i++;
		}

	}

}
