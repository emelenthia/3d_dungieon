#pragma once
#include"DxLib.h"
#include<string>

using namespace std;

class Functions_3DD
{
public:
	Functions_3DD();
	~Functions_3DD();
private:

};


void LoadInts(FILE* fp, int* dest, int num = -1); //fpは既に開いている必要がある。destの戦闘から、','が出てくるまでの数値をint型で入れる。1行文。個数を指定すれば、足りない分はdest[0]で埋めることが出来る
void LoadStrings(FILE* fp, string* dest, char splitter); //fpは既に開いている必要がある。destの戦闘から、','が出てくるまでの文字列を入れる。1行文。
