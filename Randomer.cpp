#include "Randomer.h"

Randomer* Randomer::instance;

Randomer::Randomer()
{
	time(&timer);
	t_st = localtime(&timer);
	random_mt = new std::mt19937((t_st->tm_mon + 1)*(t_st->tm_mday + 1)*(t_st->tm_hour + 1)*(t_st->tm_sec + 1)*(t_st->tm_min + 1));
}


int Randomer::GetRand()
{
	return abs((int)(*Randomer::random_mt)());
}