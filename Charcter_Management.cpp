#include "Charcter_Management.h"
#include<stdio.h>

void Charcter_Management::Set_Variable()
{
	fp = fopen("./scn/char/char_M.cns", "r");
	fscanf(fp, "%d", &character_max);
	fclose(fp);

}