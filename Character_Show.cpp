#include"Character_Show.h"
#include"DxLib.h"
#include"Colors.h"

void Character_Show::Draw()
{
	character_show_f->Draw(); 
	DrawString(20, 2, "�L�����N�^�[�̔\�͂̏ڍׂ��m�F�ł��܂��B", Colors::white);

}


int Character_Show::Reaction()
{
	return character_show_f->Reaction();
}