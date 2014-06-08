#pragma once
#include<random>
#include<time.h>

class Randomer
{
public:
	static Randomer* instance;
	static Randomer* GetInstance()
	{
		if (instance == NULL)
		{
			instance = new Randomer;
		}
		return instance;
	}

	std::random_device rd;
	std::mt19937* random_mt;
	int GetRand();

	time_t timer;
	tm* t_st;

private:
	Randomer();
	~Randomer(){};
	Randomer(const Randomer& rhs);
	Randomer& operator=(const Randomer& rhs);
};

