#include "Events.h"
#include"Flags.h"

Events::~Events()
{
}


int Events::ev_act(int number)
{
	switch (number)
	{
	case 1:
		in_battle();
		break;
	}

	return 0;
}


void Events::in_battle()
{
	Flags::nowscene = 0xba771e;
}