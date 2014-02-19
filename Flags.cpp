#include "Flags.h"

int Flags::talkflag;
int Flags::menuflag;
int Flags::nowscene;
int Flags::guild_now;
int Flags::menu_window_size_x;
int Flags::menu_window_size_y;

Flags::Flags()
{
	talkflag = 0;
	menuflag = 0;
	nowscene = 0x8011d;
	guild_now = 1;
	menu_window_size_x = 160;
	menu_window_size_y = 400;
}


Flags::~Flags()
{
}
