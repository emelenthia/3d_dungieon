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
	//���̂܂܂��ƁA�\���̂̓���̕ϐ��ɓ��ꂽ�����Ƃ��ɑΉ����Ȃ��̂łǂ��ɂ�������
	char keep[1024]; //TODO:���̒����ɂ��Ă͋^�₪�c�邯�ǂǂ�����Č��߂�Ηǂ��̂��낤��
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
		if (keep[count] == '\0') //���ꂪ�Ȃ��ƁAc++��2��ǂ�ł邽�߁A\0���΂��Ă��܂�
		{
			break;
		}
	}
	while (i <num) //�ȗ����Ă������ꍇ�͕⊮����
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
