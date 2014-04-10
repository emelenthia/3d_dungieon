#include "SaveData.h"
#include<stdio.h>
#include"DxLib.h"

SaveData* SaveData::instance;

SaveData::SaveData()
{
	fp = fopen("./scn/save/savedata.txt", "r+");
	if (fp == NULL)
	{
		DrawString(0, 0, "Error!", GetColor(255, 0, 0) , TRUE);
		WaitKey();
	}

	fscanf(fp, "%d", &nummap);
	for (int i = 0; i < nummap; i++)
	{
		fscanf(fp, "%d,%d", &z_max[i], &x_max[i]);
		for (int z = 0; z < z_max[i]; z++)
		{
			for (int x = 0; x < x_max[i]; x++)
			{
				fscanf(fp, "%d,", &map_open_flag[i][z][x]);
			}
		}
	}
}


SaveData::~SaveData()
{
	fclose(fp);
}


void SaveData::Save()
{
	DrawString(0, 0, "Saving", GetColor(255, 0, 0));
	WaitKey();
	fclose(fp);
	fp = fopen("./scn/save/savedata.txt", "r+");
	fprintf(fp, "%d\n", nummap);
	for (int i = 0; i < nummap; i++)
	{
		fprintf(fp, "%d,%d\n", z_max[i], x_max[i]);
		for (int z = 0; z < z_max[i]; z++)
		{
			for (int x = 0; x < x_max[i]; x++)
			{
				fprintf(fp, "%d,", map_open_flag[i][z][x]);
			}
			fprintf(fp, "\n");
		}
	}
	fprintf(fp, "OK\n");
	fclose(fp);
	fp = fopen("./scn/save/savedata.txt", "r+");
}