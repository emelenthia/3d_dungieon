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


void LoadInts(FILE* fp, int* dest, int num = -1); //fp�͊��ɊJ���Ă���K�v������Bdest�̐퓬����A','���o�Ă���܂ł̐��l��int�^�œ����B1�s���B�����w�肷��΁A����Ȃ�����dest[0]�Ŗ��߂邱�Ƃ��o����
void LoadStrings(FILE* fp, string* dest, char splitter); //fp�͊��ɊJ���Ă���K�v������Bdest�̐퓬����A','���o�Ă���܂ł̕����������B1�s���B
