#include "Ailment.h"
#include"DxLib.h"


Ailment::Ailment()
{
	LoadAilment();
}


Ailment::~Ailment()
{
}


void Ailment::LoadAilment()
{
	FILE* fp;
	fp = fopen("./status_ailment/status_ailment.txt", "r");

	for (int i = 0; i < Defines::AILMENT_MAX; i++)
	{
		fscanf(fp, "%s", m_ailment[i].name);
	}
	fclose(fp);
}


