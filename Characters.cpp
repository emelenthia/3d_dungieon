#include "Characters.h"

Characters* Characters::instance;

Characters::Characters()
{
	//TODO:ƒLƒƒƒ‰‚ğ’Ç‰Á‚µ‚½Û‚É‚Í‚±‚±‚É’Ç‰Á‚·‚é
	Load_Char_n_s("./scn/char/char_DF_01.cns", "./scn/char/char_DS_01.cns",0);
	Load_Char_n_s("./scn/char/char_DF_02.cns", "./scn/char/char_DS_02.cns",1);
	Load_Char_n_s("./scn/char/char_DF_03.cns", "./scn/char/char_DS_03.cns",2);
	Load_Char_n_s("./scn/char/char_DF_04.cns", "./scn/char/char_DS_04.cns",3);
	Load_Char_n_s("./scn/char/char_DF_05.cns", "./scn/char/char_DS_05.cns",4);
	Load_Char_n_s("./scn/char/char_DF_06.cns", "./scn/char/char_DS_06.cns",5);
	Load_Char_n_s("./scn/char/char_DF_07.cns", "./scn/char/char_DS_07.cns",6);
	Load_Char_n_s("./scn/char/char_DF_08.cns", "./scn/char/char_DS_08.cns",7);
	Load_Char_n_s("./scn/char/char_DF_09.cns", "./scn/char/char_DS_09.cns",8);
	Load_Char_n_s("./scn/char/char_DF_10.cns", "./scn/char/char_DS_10.cns",9);
	Load_Char_n_s("./scn/char/char_DF_11.cns", "./scn/char/char_DS_11.cns",10);
	Load_Char_n_s("./scn/char/char_DF_12.cns", "./scn/char/char_DS_12.cns",11);
	Load_Char_n_s("./scn/char/char_DF_13.cns", "./scn/char/char_DS_13.cns",12);
	Load_Char_n_s("./scn/char/char_DF_14.cns", "./scn/char/char_DS_14.cns",13);
	Load_Char_n_s("./scn/char/char_DF_15.cns", "./scn/char/char_DS_15.cns", 14);
}