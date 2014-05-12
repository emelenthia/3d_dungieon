#include "MonsterList.h"
#include<string.h>

MonsterList* MonsterList::instance = NULL;

MonsterList::MonsterList()
{
	//1‰ñ‚¾‚¯“Ç‚İ‚İ
	if (listfp == NULL)
	{
		//ˆê‰‰Šú‰»
		for (int i = 0; i < 1; i++)
		{
			strcpy(monsterlist[i], "\0");
		}

		listfp = fopen("./scn/monsters/monsterlist.cns", "r");

		fscanf(listfp, "%d", &monstermax);
		for (int i = 0; i < monstermax; i++)
		{
			fscanf(listfp, "%s", monsterlist[i]);
		}
	}
}


MonsterList::~MonsterList()
{
	if (listfp != NULL)
	{
		fclose(listfp);
	}
}
