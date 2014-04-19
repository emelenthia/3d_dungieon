#include "Colors.h"
#include"DxLib.h"

int Colors::red;
int Colors::blue;
int Colors::yellow;
int Colors::white;
int Colors::black;
int Colors::aqua;
int Colors::dark_aqua;
int Colors::green;

Colors::Colors()
{
	red = GetColor(255, 0, 0);
	blue = GetColor(0, 0, 255);
	black = GetColor(0, 0, 0);
	white = GetColor(255, 255, 255);
	yellow = GetColor(255, 255, 0);
	aqua = GetColor(0, 255, 255);
	dark_aqua = GetColor(0, 35, 35);
	green = GetColor(0, 255, 0);
}


Colors::~Colors()
{
}
