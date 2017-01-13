#include "Functions_3DD.h"
#include"Defines.h"


Functions_3DD::Functions_3DD()
{
}


Functions_3DD::~Functions_3DD()
{
}

void LoadInts(FILE * fp, int * dest, int num)
{
	//このままだと、構造体の特定の変数に入れたい時とかに対応しないのでどうにかしたい
	char keep[1024]; //TODO:この長さについては疑問が残るけどどうやって決めれば良いのだろうか
	char temp[1024];
	fscanf(fp, "%s", keep);
	int count = 0, i = 0, j = 0;
	for (; keep[count] != '\0'; count++)
	{
		j = 0;
		while (keep[count] != ',' && keep[count] != '\0')
		{
			temp[j] = keep[count];
			count++;
			j++;
		}
		temp[j] = '\0';
		dest[i++] = atoi(temp);
		if (keep[count] == '\0') //これがないと、c++を2回読んでるため、\0を飛ばしてしまう
		{
			break;
		}
	}
	while (i <num) //省略してあった場合は補完する
	{
		dest[i] = dest[0];
		i++;
	}
}


void LoadStrings(FILE* fp, string* dest, char splitter)
{
	string temp_str;

	fscanf(fp, "%s", temp_str);

}
