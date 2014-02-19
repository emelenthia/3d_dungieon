#include "G_F_O_Exit.h"
#include"Players.h"
#include"DxLib.h"


G_F_O_Exit::G_F_O_Exit()
{
	checkhitflag = 0;
}


G_F_O_Exit::~G_F_O_Exit()
{
}


int G_F_O_Exit::Reaction()
{
	int r = 0;
	if ((Players::real_pos_x - Players::pos_x_lu <= pos_x_lu) &&
		(pos_y_lu <= Players::real_pos_y + Players::pos_y_lu && Players::real_pos_y + Players::pos_y_rd <= pos_y_rd)) //このオブジェクトに重なったら
	{
		r = 1;
	}

	return r;
}
