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
int Colors::purple;
int Colors::gray;
int Colors::dark_yellow;
int Colors::fh_half;

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
	purple = GetColor(255, 0, 255);
	gray = GetColor(128, 128, 128);
	dark_yellow = GetColor(35, 35, 0);
	fh_half = CreateFontToHandle(NULL, 12, -1, -1);
}


Colors::~Colors()
{
}
